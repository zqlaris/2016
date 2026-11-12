/**
 * ArkivScriptDoc.cpp
 * Copyright (c) 2013 ARKIV Corp. All Rights Reserved.
 */

#include "stdafx.h"
#include "ArkivScriptDoc.h"

// Qt Headers
#include <QTextStream>
#include <QClipboard>
#include <QFileInfo>

// 3rd Party Headers
#include "boost/iostreams/copy.hpp"

// Arkiv Headers
#include "script/script.h"
#include "Script/ScriptContext.h"
#include "util/ProtectedString.h"
#include "Util/ScopedAssign.h"
#include "v8datamodel/ContentProvider.h"
#include "v8datamodel/DataModel.h"
#include "v8datamodel/Selection.h"
#include "V8Tree/Service.h"

#include "Client.h"
#include "ClientReplicator.h"
#include "Network/Players.h"

// Arkiv Studio Headers
#include "AuthoringSettings.h"
#include "DebuggerClient.h"
#include "DebuggerWidgets.h"
#include "FindDialog.h"
#include "LuaSourceBuffer.h"
#include "QtUtilities.h"
#include "ArkivMainWindow.h"
#include "ArkivDocManager.h"
#include "ArkivIDEDoc.h"
#include "ScriptTextEditor.h"
#include "UpdateUIManager.h"
#include "ScriptAnalysisWidget.h"

FASTFLAG(LuaDebugger)
FASTFLAG(LuaDebuggerBreakOnError)
FASTFLAG(StudioEmbeddedFindDialogEnabled)
FASTFLAG(StudioSeparateActionByActivationMethod)

FASTFLAGVARIABLE(CloudEditRemoveScriptLockOnDocClose, false)

int ArkivScriptDoc::sScriptCount = 1;
int ArkivScriptDoc::slastActivatedRibbonPage = -1;


ArkivScriptDoc::ArkivScriptDoc()
    : m_pMainWindow(NULL)
    , m_pParentDoc(NULL)
    , m_pTextEdit(NULL)
    , m_displayName(QString("Script%1").arg(sScriptCount))
    , m_undoAvailable(false)
    , m_redoAvailable(false)
    , m_copyAvailable(false)
    , m_updatingText(false)
	, m_currentlyAttemptingToGetScriptLock(false)
	, m_haveCloudEditScriptLock(false)
{
    // get a temporarily name that we're going to overwrite when the script changes.
    // the doc manager needs to have some way to refer to this doc while configuring.
    m_keyName = QString::number((int)this);    
}

ArkivScriptDoc::~ArkivScriptDoc()
{
}

void ArkivScriptDoc::init(ArkivMainWindow& mainWindow)
{	
	setMenuVisibility(false);

	if (FFlag::LuaDebugger && (mainWindow.getBuildMode() != BM_BASIC))
		DebuggerViewsManager::Instance();
	
	if (!FFlag::LuaDebuggerBreakOnError || (mainWindow.getBuildMode() == BM_BASIC))
	{
		FFlag::LuaDebuggerBreakOnError = false;
		QMenu* pMenu = UpdateUIManager::Instance().getMainWindow().findChild<QMenu*>("breakErrorsIntoDebuggerMenu");
		if (pMenu)
			delete pMenu;
	}

	qRegisterMetaType<RBX::ScriptAnalyzer::Result>("RBX::ScriptAnalyzer::Result");
}

QString ArkivScriptDoc::fileName() const
{
    if ( m_pParentDoc )
        return m_pParentDoc->fileName();
    return QFileInfo(m_fileName).fileName();
}

bool ArkivScriptDoc::open(ArkivMainWindow *pMainWindow, const QString &fileName)
{
	bool success = true;
	
	try 
	{
		m_pMainWindow = pMainWindow;

        // create an editor
		m_pTextEdit = new ScriptTextEditor(this, m_pMainWindow);
		if (ArkivIDEDoc::getIsCloudEditSession())
		{
			connect(m_pTextEdit, SIGNAL(textChanged()), this, SLOT(editingContents()));
		}

		if (!fileName.isEmpty())
		{
			QFile file(fileName);
			if (!file.open(QFile::ReadOnly | QFile::Text)) 
				return false;
			
			//loading			
			QTextStream in(&file);
			m_pTextEdit->setPlainText(in.readAll());

			m_fileName = fileName;
		}
		else //open a new script file
			sScriptCount++;
	}
	catch (...)
	{
		success = false;
	}

	return success;
}

static void receiveStateAndSetEvent(bool value, shared_ptr<RBX::LuaSourceContainer> lsc, bool* state,
	std::string* ownerOfLock, RBX::CEvent* event)
{
	*state = value;
	if (RBX::Instance* currentEditor = lsc->getCurrentEditor())
	{
		*ownerOfLock = currentEditor->getName();
	}

	event->Set();
}

static void disconnected(bool* state, RBX::CEvent* event)
{
	*state = false;
	event->Set();
}

static void attemptToLockScript(shared_ptr<RBX::DataModel> dm, LuaSourceBuffer lsb,
		bool* weHaveTheLock, std::string* nameOfPlayerWhoOwnsTheLock, std::string* oldSource)
{
	using namespace RBX;

	CEvent cevent(true);
	shared_ptr<LuaSourceContainer> lsc;
	rbx::signals::scoped_connection conn1, conn2;

	{
		DataModel::LegacyLock l(dm, DataModelJob::Write);
		*oldSource = lsb.getScriptText();

		lsc = lsb.toInstance();
		if (!lsc) // Linked source
		{
			*weHaveTheLock = true;
			return;
		}

		Instance* localPlayer = Network::Players::findLocalPlayer(dm.get());
		if (!localPlayer)
		{
			StandardOut::singleton()->print(MESSAGE_ERROR,
				"Unable to find local player when trying to lock script for editing");
			*weHaveTheLock = false;
			return;
		}

		Instance* currentEditor = lsc->getCurrentEditor();
		if (currentEditor != NULL)
		{
			*weHaveTheLock = currentEditor == localPlayer;
			*nameOfPlayerWhoOwnsTheLock = currentEditor->getName();
			return;
		}

		// handle disconnect		
		Network::Client* client = Network::Client::findClient(dm.get());
		if (!client)
		{
			*weHaveTheLock = false;
			return;
		}

		Network::ClientReplicator* rep = client->findFirstChildOfType<Network::ClientReplicator>();		
		if (!rep)
		{
			*weHaveTheLock = false;
			return;
		}

		conn1 = rep->disconnectionSignal.connect(boost::bind(&disconnected, weHaveTheLock, &cevent));
		conn2 = lsc->lockGrantedOrNot.connect(boost::bind(&receiveStateAndSetEvent, _1, lsc,
			weHaveTheLock, nameOfPlayerWhoOwnsTheLock, &cevent));
		LuaSourceContainer::event_requestLock.replicateEvent(lsc.get());
	}

	cevent.Wait();
}

void ArkivScriptDoc::editingContents()
{
	ArkivIDEDoc* ideDoc = ArkivDocManager::Instance().getPlayDoc();
	RBXASSERT(ideDoc && ideDoc->isCloudEditSession());
	if (m_updatingText || m_currentlyAttemptingToGetScriptLock || ideDoc == NULL)
	{
		return;
	}

	bool isOverlaySimulation = ideDoc->getDataModel() != ideDoc->getEditDataModel().get();
	if (isOverlaySimulation)
	{
		QtUtilities::RBXMessageBox warningBox;
		warningBox.setText("WARNING: You are in testing mode, any changes you make will be lost when you press the stop button");
		warningBox.exec();
	}
	else if (!m_haveCloudEditScriptLock)
	{
		RBX::ScopedAssign<bool> sa(m_currentlyAttemptingToGetScriptLock, true);
		std::string nameOfPlayerWhoOwnsTheLock;
		std::string oldSource;
		UpdateUIManager::Instance().waitForLongProcess(QString("Locking script..."),
			boost::bind(&attemptToLockScript, m_dataModel, m_script,
			&m_haveCloudEditScriptLock, &nameOfPlayerWhoOwnsTheLock, &oldSource));
		if (!m_haveCloudEditScriptLock)
		{
			// restore old script
			onScriptSourcePropertyChanged(QString::fromStdString(oldSource));

			// notify user
			QtUtilities::RBXMessageBox messageBox;
			messageBox.setStandardButtons(QMessageBox::Ok);
			if (nameOfPlayerWhoOwnsTheLock.empty())
			{
				messageBox.setText("Cannot gain write access to script, reverting your change");
			}
			else
			{
				messageBox.setText(QString::fromStdString(nameOfPlayerWhoOwnsTheLock +
					" is currently modifying this script, your changes will be reverted"));
			}
			messageBox.exec();
		}
	}
}

IArkivDoc::RBXCloseRequest ArkivScriptDoc::requestClose()
{
	return IArkivDoc::NO_SAVE_NEEDED;
}

bool ArkivScriptDoc::doClose()
{
	deActivate();

	FindReplaceProvider::instance().setFindListener(NULL);
	
	if (FFlag::StudioEmbeddedFindDialogEnabled)
	{
		FindReplaceProvider::instance().getEmbeddedFindDialog()->hide();
	}
	else
	{
		FindReplaceProvider::instance().getFindDialog()->hide();
		FindReplaceProvider::instance().getReplaceDialog()->hide();
	}

	//this will get deleted once the data model gets removed
	if (DebuggerClient *pLuaDebuggerClient = DebuggerClientManager::Instance().getDebuggerClient(m_script.toInstance()))
		pLuaDebuggerClient->setDocument(NULL);
	
	m_pTextEdit->deleteLater();

	setScript(shared_ptr<RBX::DataModel>(), LuaSourceBuffer());
	
	//self deletion (maybe we must use reference counting!)
	deleteLater();

    if ( m_pParentDoc )
        ArkivDocManager::Instance().setCurrentDoc(m_pParentDoc);

	return true;
}

bool ArkivScriptDoc::isModified()
{
	if (m_pParentDoc)
		return false;

	return m_pTextEdit->document()->isModified();
}

const QIcon& ArkivScriptDoc::titleIcon() const
{
	static QIcon empty;
	static QIcon cloud;
	
    if (cloud.isNull())
        cloud.addFile(QString::fromUtf8(":/images/onlinePlaceIcon.png"), QSize(), QIcon::Normal, QIcon::Off);
	
	if (m_script.empty() || m_script.toInstance())
	{
		return empty;
	}
	else
	{
		return cloud;
	}
}

bool ArkivScriptDoc::save()
{
	if (m_pParentDoc)
	{
		applyEditChanges();		
		return m_pParentDoc->save();
	}

	return saveAs(m_fileName);
}

bool ArkivScriptDoc::saveAs(const QString &fileName)
{
	if (fileName.isEmpty())
		return false;

	if (m_pParentDoc)
	{
		applyEditChanges();		
		m_pParentDoc->saveAs(fileName);
		return false;//intentional
	}

	QString _fileName(fileName);
	if (!_fileName.endsWith(".lua", Qt::CaseInsensitive))
	    _fileName.append(".lua");

	//doSave
	QFile file(_fileName);
	if (!file.open(QFile::WriteOnly | QFile::Text)) 
		return false;

	try
	{
		QTextStream out(&file);

		out << m_pTextEdit->toPlainText();

		m_fileName = _fileName;
		RBX::StandardOut::singleton()->printf(RBX::MESSAGE_INFO, "Successfully saved at %s", qPrintable(_fileName));
	}	
	catch (...)
	{
		RBX::StandardOut::singleton()->printf(RBX::MESSAGE_INFO, "Error in saving document at %s", qPrintable(_fileName));
		return false;
	}
	return true;
}

QString ArkivScriptDoc::saveFileFilters()
{ 
	if (m_pParentDoc)
		return m_pParentDoc->saveFileFilters();

	return "Lua Script Files (*.lua)"; 
}

QWidget* ArkivScriptDoc::getViewer() 
{ 
    return static_cast<QWidget*>(m_pTextEdit); 
}

void ArkivScriptDoc::activate()
{
	if (m_bActive)
		return;

    m_bActive = true;
	
	if (DebuggerClient *pLuaDebuggerClient = DebuggerClientManager::Instance().getDebuggerClient(m_script.toInstance()))
		pLuaDebuggerClient->activate();

	// Init Find Replace dialogs
	FindReplaceProvider::instance().setFindListener(m_pTextEdit);

	//update toolbars
	UpdateUIManager::Instance().updateToolBars();
	
	this->setupScriptConnection();

	m_pTextEdit->setFocus();
}

void ArkivScriptDoc::deActivate()
{
	if (!m_bActive)
		return;

    m_bActive = false;

	applyEditChanges();

	this->disconnectScriptConnection();

	if (DebuggerClient *pLuaDebuggerClient = DebuggerClientManager::Instance().getDebuggerClient(m_script.toInstance()))
		pLuaDebuggerClient->deActivate();
}

void ArkivScriptDoc::updateUI(bool state)
{
	setMenuVisibility(state);
}

bool ArkivScriptDoc::handleDrop(const QString &fileName)
{
	if(fileName.isEmpty())
		return false;

	if(!m_pParentDoc)
		return false;

	return m_pParentDoc->handleDrop(fileName);
}

bool ArkivScriptDoc::doHandleAction(const QString& actionID, bool isChecked)
{
	bool handled = false;

    const QString zoomActions = "zoomInAction zoomOutAction";

    // let script text editor have a chance first to handle the action
    if ((m_bActive || zoomActions.contains(actionID)) && m_pTextEdit->doHandleAction(actionID) )
        return true;

    // All Actions that we do not want to be handled by the Parent ArkivIDEDoc when we are in Script Doc 

	QKeySequence keySequence;

	if (QAction* action = UpdateUIManager::Instance().getMainWindow().getActionByName(actionID))
		keySequence = action->shortcut();

	if (keySequence.matches(QKeySequence::MoveToNextPage) == QKeySequence::ExactMatch)
	{
		if (m_pTextEdit)
			m_pTextEdit->keyPressEvent(new QKeyEvent(QEvent::KeyPress, Qt::Key_PageDown, 0));

		handled = true;
	}
	if (keySequence.matches(QKeySequence::MoveToPreviousPage) == QKeySequence::ExactMatch)
	{
		if (m_pTextEdit)
			m_pTextEdit->keyPressEvent(new QKeyEvent(QEvent::KeyPress, Qt::Key_PageUp, 0));

		handled = true;
	}
	
    if (actionID == "reloadScriptAction")
    {
        reloadLiveScript();
        handled = true;
    }
    else if ( actionID == "actionCustomContextMenuHide" )
	{
		if ( m_pMainWindow->treeWidgetStack().currentWidget()->hasFocus() )
			setupScriptConnection();
		handled = true;		
	}
    else if ( actionID == "actionCustomContextMenuShow" )
	{
		if ( m_pMainWindow->treeWidgetStack().currentWidget()->hasFocus() )
		{
			QTextCursor textCursor = m_pTextEdit->textCursor();
			textCursor.clearSelection();
			m_pTextEdit->setTextCursor(textCursor);

			disconnectScriptConnection();
			m_pMainWindow->copyAction->setEnabled(true);
			m_pMainWindow->cutAction->setEnabled(true);
			m_pMainWindow->undoAction->setEnabled(true);
			m_pMainWindow->redoAction->setEnabled(true);

			QClipboard* pClipboard = QApplication::clipboard();
			const QMimeData* pMimeData = pClipboard->mimeData();
			if ( pMimeData && pMimeData->hasFormat("application/x-arkiv-studio") )
				m_pMainWindow->pasteIntoAction->setEnabled(true);
		}

		handled = true;
	}
    
	if (m_pParentDoc && !handled)
    {
        // Delegate all script enabled actions to parent ArkivIDEDoc & give parent the chance to handle
		handled = m_pParentDoc->doHandleAction(actionID,isChecked);
    }

	if (FFlag::LuaDebugger && !handled)
	{
		DebuggerClient *pLuaDebuggerClient = DebuggerClientManager::Instance().getDebuggerClient(m_script.toInstance());
		if (pLuaDebuggerClient)
			handled = pLuaDebuggerClient->handleAction(actionID,isChecked);
	}

	return handled;
}

void ArkivScriptDoc::handleScriptCommand(const QString &execCommand)
{
	if(m_pParentDoc)
	{
		m_pParentDoc->handleScriptCommand(execCommand);
	}
}

bool ArkivScriptDoc::actionState(const QString &actionID, bool &enableState, bool &checkedState)
{
    static QString disabledActions = "rotateSelectionAction";
    if (disabledActions.contains(actionID))
	{
		enableState = false;
		return true;
	}

	if (!m_bActive && actionID == "goToLineAction")
	{
		enableState = false;
		return true;
	}
    
    const QString zoomActions = "zoomInAction zoomOutAction";
    
    // let script text editor handle first
    if ((m_bActive || zoomActions.contains(actionID)) && m_pTextEdit->actionState(actionID,enableState,checkedState) )
        return true;
    
	static QString scriptActiveActions =
        "fileSaveAction fileSaveAsAction fileCloseAction toggleCommentAction goToLineAction "
        "findAction replaceAction expandAllFoldsAction collapseAllFoldsAction resetScriptZoomAction actionFindMenu actionSelectMenu ";
	if ( scriptActiveActions.contains(actionID) )
	{
		enableState = true;
		checkedState = false;
		return true;
	}

    if (actionID == "reloadScriptAction")
    {
        if ((ArkivDocManager::Instance().getPlayDoc() && ArkivDocManager::Instance().getPlayDoc()->isSimulating()) ||
			m_script.isModuleScript())
        {
            enableState = true;
            checkedState = false;
            return true;
        }
    }

	if (UpdateUIManager::Instance().getDockActionNames().contains(actionID))
	{
		enableState = true;
		checkedState = UpdateUIManager::Instance().getAction(actionID)->isChecked();
		return true;
	}

	/// Anything that needs to be handled by ArkivIDEDoc goes in here, the enabled/checked state is all delegated to parent.
	static QString delegateToParentActions(
        "saveToArkivAction insertIntoFileAction selectionSaveToFileAction playSoloAction "
        "startServerAction startPlayerAction publishToArkivAction publishToArkivAsAction "
		"publishAsPluginAction createNewLinkedSourceAction startServerAndPlayersAction startServerCB playersMode findInScriptsAction explorerFilterAction");

	static QString explorerActionsEnabledInScriptView("copyAction cutAction pasteAction undoAction redoAction "
		"deleteSelectedAction groupSelectionAction ungroupSelectionAction duplicateSelectionAction "
		"selectAllAction selectChildrenAction pasteIntoAction renameObjectAction launchHelpForSelectionAction");

	if(m_pParentDoc && (delegateToParentActions.contains(actionID) || explorerActionsEnabledInScriptView.contains(actionID)))
		return m_pParentDoc->actionState(actionID, enableState, checkedState);

	//once we remove the fast flag, move the following actions to delegateToParentActions
	if (FFlag::LuaDebugger)
	{
		static QString simulationActions("simulationRunAction simulationPlayAction simulationStopAction simulationResetAction " 
			                             "simulationRunSelectorSim simulationRunSelectorDebug simulationRunSelectorTest" );
		if(m_pParentDoc && simulationActions.contains(actionID))
			return m_pParentDoc->actionState(actionID, enableState, checkedState);

		DebuggerClient *pLuaDebuggerClient = DebuggerClientManager::Instance().getDebuggerClient(m_script.toInstance());
		if (pLuaDebuggerClient && pLuaDebuggerClient->actionState(actionID, enableState, checkedState))
			return true;
	}

	enableState = false;
	checkedState = false;
	return true;	
}

void ArkivScriptDoc::setupScriptConnection()
{
	m_pTextEdit->setUndoRedoEnabled(true);

	m_pMainWindow->copyAction->setEnabled(m_copyAvailable);
	m_pMainWindow->cutAction->setEnabled(m_copyAvailable);
	m_pMainWindow->undoAction->setEnabled(m_undoAvailable);
	m_pMainWindow->redoAction->setEnabled(m_redoAvailable);

	//set copy and cut to be available when texts are selected
	connect(m_pTextEdit, SIGNAL(copyAvailable(bool)), m_pMainWindow->cutAction, SLOT(setEnabled(bool)));
	connect(m_pTextEdit, SIGNAL(copyAvailable(bool)), m_pMainWindow->copyAction, SLOT(setEnabled(bool)));

	//set undo/redo to be available when there are changes.
	connect(m_pTextEdit, SIGNAL(undoAvailable(bool)), m_pMainWindow->undoAction, SLOT(setEnabled(bool)));
	connect(m_pTextEdit, SIGNAL(redoAvailable(bool)), m_pMainWindow->redoAction, SLOT(setEnabled(bool)));

	connect(m_pTextEdit, SIGNAL(selectionChanged()), this, SLOT(onSelectionChanged()));

	this->activateConnection();
}

void ArkivScriptDoc::setScript(shared_ptr<RBX::DataModel> dm, LuaSourceBuffer script)
{
	if (m_script == script)
		return;

	if (!m_script.empty())
	{
		m_ancestryChangedConnection.disconnect();
		m_propertyChangedConnection.disconnect();
		disconnect(m_pTextEdit.get(), SIGNAL(toggleBreakpoint(int)),
			this, SLOT(explainBreakpointsDisabled()));

		if (m_haveCloudEditScriptLock && m_dataModel && script.empty())
		{
			if (!FFlag::CloudEditRemoveScriptLockOnDocClose)
			{
				RBX::DataModel::LegacyLock lock(m_dataModel, RBX::DataModelJob::Write);
				if (shared_ptr<RBX::LuaSourceContainer> lsc = m_script.toInstance())
				{
					RBX::Network::Player* localPlayer = RBX::Network::Players::findLocalPlayer(m_dataModel.get());
					if (localPlayer && lsc->getCurrentEditor() == localPlayer)
					{
						lsc->setCurrentEditor(NULL);
						lsc->fireSourceChanged();
						m_haveCloudEditScriptLock = false;
					}
				}				
			}
			else
			{
				removeScriptLock();
			}
		}

		m_script = LuaSourceBuffer();
		m_dataModel.reset();

		m_pParentDoc = NULL;

        ArkivDocManager::Instance().deregisterScriptDoc(*this);
	}

	if (!script.empty()) // adding an associated script instance
	{
		m_script = script;
		m_pParentDoc = ArkivDocManager::Instance().getPlayDoc();
		m_dataModel = dm;
		if (script.toInstance() == NULL)
		{
			connect(m_pTextEdit.get(), SIGNAL(toggleBreakpoint(int)),
				this, SLOT(explainBreakpointsDisabled()));
		}

		RBX::DataModel::LegacyLock lock(m_dataModel, RBX::DataModelJob::Write);

		if (shared_ptr<RBX::Instance> inst = script.toInstance())
		{
			m_ancestryChangedConnection = inst->ancestryChangedSignal.connect(boost::bind(&ArkivScriptDoc::onAncestryChanged, this, _2));
			m_propertyChangedConnection = inst->propertyChangedSignal.connect(boost::bind(&ArkivScriptDoc::onPropertyChanged, this, _1));
		}

		onScriptNamePropertyChanged(buildTabTitle());
		onScriptSourcePropertyChanged(QString::fromStdString(m_script.getScriptText()));

        ArkivDocManager::Instance().registerOpenedScriptDoc(*this,m_script);  

		if (FFlag::LuaDebugger && m_pMainWindow->getBuildMode() != BM_BASIC)
		{
			//create 
			if (DebuggerClient *pLuaDebuggerClient = DebuggerClientManager::Instance().getOrCreateDebuggerClient(m_script.toInstance()))
			{
				pLuaDebuggerClient->setDocument(this);
				if (pLuaDebuggerClient && m_bActive)
					pLuaDebuggerClient->activate();
			}
		}

		// need to update actions once we set the script pointer
		UpdateUIManager::Instance().updateToolBars();

		// title icon can change based on the value of m_script, so update doc title
		ArkivDocManager::Instance().setDocTitle(*this, displayName(), titleTooltip(), titleIcon());
	}
}

void ArkivScriptDoc::onAncestryChanged(shared_ptr<RBX::Instance> newParent)
{
	if (newParent==NULL)
	{
		if (this->thread() == QThread::currentThread())
			requestScriptDeletion();
		else
			QTimer::singleShot(0, this, SLOT(requestScriptDeletion()));
	}
}

void ArkivScriptDoc::requestScriptDeletion()
{	
	if (!m_script.empty())
		ArkivDocManager::Instance().closeDoc(m_script);

	// Set script to NULL because it is no longer valid
	setScript(shared_ptr<RBX::DataModel>(), LuaSourceBuffer());
}

void ArkivScriptDoc::onPropertyChanged(const RBX::Reflection::PropertyDescriptor* desc)
{
	RBXASSERT(!m_dataModel || m_dataModel->currentThreadHasWriteLock());

	if (m_script.empty() || !m_pTextEdit)
	{
		return;
	}

	if (*desc==RBX::Instance::desc_Name || desc->name == "CurrentEditor")
	{
		QMetaObject::invokeMethod(this, "onScriptNamePropertyChanged", Qt::QueuedConnection,
			Q_ARG(QString, buildTabTitle()));
	}
	else if ((*desc==RBX::Script::prop_EmbeddedSourceCode) || (*desc==RBX::ModuleScript::prop_Source))
	{
		QMetaObject::invokeMethod(this, "onScriptSourcePropertyChanged", Qt::QueuedConnection,
			Q_ARG(QString, QString::fromStdString(m_script.getScriptText())));
	}
	else if (desc->name == "LinkedSource")
	{
		QTimer::singleShot(0, this, SLOT(requestScriptDeletion()));
	}
}

void ArkivScriptDoc::onScriptNamePropertyChanged(const QString& newName)
{
	m_displayName = newName;
	ArkivDocManager::Instance().setDocTitle(*this, displayName(), titleTooltip(), titleIcon());
}

void ArkivScriptDoc::onScriptSourcePropertyChanged(const QString& newSource)
{
	RBX::ScopedAssign<bool> sa(m_updatingText, true);
	maybeUpdateText(newSource);
}

void ArkivScriptDoc::maybeUpdateText(const QString& code)
{
	if (m_script.empty() || !m_pTextEdit)
		return;

	QString currentText = m_pTextEdit->toPlainText();
	if (code != currentText)
		m_pTextEdit->setPlainText(code);
}

void ArkivScriptDoc::refreshEditorFromSourceBuffer()
{
	QString source;
	{
		RBX::DataModel::LegacyLock l(m_dataModel, RBX::DataModelJob::Write);
		source = QString::fromStdString(m_script.getScriptText());
	}
	onScriptSourcePropertyChanged(source);
}

void ArkivScriptDoc::applyEditChanges()
{
	if (m_script.empty() || !m_dataModel)
		return;

	if (ArkivIDEDoc::getIsCloudEditSession() && !m_haveCloudEditScriptLock)
	{
		return;
	}

	if (m_pTextEdit->document()->isModified() && !m_updatingText)
	{
		m_pTextEdit->document()->setModified(false);
        
        if (ArkivDocManager::Instance().getPlayDoc() &&
            ArkivDocManager::Instance().getPlayDoc()->isSimulating())
        {
            ArkivDocManager::Instance().getPlayDoc()->notifyScriptEdited(getCurrentScript().toInstance());
        }

		RBX::DataModel::LegacyLock lock(m_dataModel, RBX::DataModelJob::Write);
		QString currentText = m_pTextEdit->toPlainText();

		m_script.setScriptText(currentText.toStdString());

		m_pMainWindow->m_editScriptActions.increment();
	}
}

LuaSourceBuffer ArkivScriptDoc::getCurrentScript()
{
	return m_script;
}

void ArkivScriptDoc::disconnectScriptConnection()
{
	m_copyAvailable = m_pMainWindow->copyAction->isEnabled();
	m_undoAvailable = m_pMainWindow->undoAction->isEnabled();
	m_redoAvailable = m_pMainWindow->redoAction->isEnabled();
	disconnect(m_pTextEdit, SIGNAL(copyAvailable(bool)), m_pMainWindow->cutAction, SLOT(setEnabled(bool)));
	disconnect(m_pTextEdit, SIGNAL(copyAvailable(bool)), m_pMainWindow->copyAction, SLOT(setEnabled(bool)));
	disconnect(m_pTextEdit, SIGNAL(undoAvailable(bool)), m_pMainWindow->undoAction, SLOT(setEnabled(bool)));
	disconnect(m_pTextEdit, SIGNAL(redoAvailable(bool)), m_pMainWindow->redoAction, SLOT(setEnabled(bool)));
	disconnect(m_pTextEdit, SIGNAL(selectionChanged()), this, SLOT(onSelectionChanged()));


	this->deactivateConnection();
}

void ArkivScriptDoc::deactivateConnection()
{
	//connect the edit tools for script editor with QTextEdit public slots.
	if (!FFlag::StudioSeparateActionByActivationMethod)
	{
		disconnect(m_pMainWindow->cutAction, SIGNAL(triggered()), m_pTextEdit, SLOT(cut()));
		disconnect(m_pMainWindow->copyAction, SIGNAL(triggered()), m_pTextEdit, SLOT(copy()));
		disconnect(m_pMainWindow->pasteAction, SIGNAL(triggered()), m_pTextEdit, SLOT(paste()));
		disconnect(m_pMainWindow->undoAction, SIGNAL(triggered()), m_pTextEdit, SLOT(undo()));
		disconnect(m_pMainWindow->redoAction, SIGNAL(triggered()), m_pTextEdit, SLOT(redo()));
	}
	disconnect(UpdateUIManager::Instance().getExplorerWidget(), SIGNAL(focusGained()), this, SLOT(deActivate()));
}

void ArkivScriptDoc::activateConnection()
{
	//connect the edit tools for script editor with QTextEdit public slots.
	if (!FFlag::StudioSeparateActionByActivationMethod)
	{
		connect(m_pMainWindow->cutAction, SIGNAL(triggered()), m_pTextEdit, SLOT(cut()));
		connect(m_pMainWindow->copyAction, SIGNAL(triggered()), m_pTextEdit, SLOT(copy()));
		connect(m_pMainWindow->pasteAction, SIGNAL(triggered()), m_pTextEdit, SLOT(paste()));
		connect(m_pMainWindow->undoAction, SIGNAL(triggered()), m_pTextEdit, SLOT(undo()));
		connect(m_pMainWindow->redoAction, SIGNAL(triggered()), m_pTextEdit, SLOT(redo()));
	}
	connect(UpdateUIManager::Instance().getExplorerWidget(), SIGNAL(focusGained()), this, SLOT(deActivate()));
}

QString ArkivScriptDoc::buildTabTitle()
{
	QString tabTitle = QString::fromStdString(m_script.getScriptName());
	if (shared_ptr<RBX::LuaSourceContainer> lsc = m_script.toInstance())
	{
		if (RBX::Instance* editor = lsc->getCurrentEditor())
		{
			tabTitle += QString(" (%1 Editing)").arg(QString::fromStdString(editor->getName()));
		}
	}
	return tabTitle;
}

void ArkivScriptDoc::setMenuVisibility(bool visible)
{
	if (!visible)
	{
		FindReplaceProvider::instance().setFindListener(NULL);
		
		if (FFlag::StudioEmbeddedFindDialogEnabled)
		{
			FindReplaceProvider::instance().getEmbeddedFindDialog()->hide();
		}
		else
		{
			FindReplaceProvider::instance().getFindDialog()->hide();
			FindReplaceProvider::instance().getReplaceDialog()->hide();
		}
	}

	ArkivMainWindow& mainWindow = UpdateUIManager::Instance().getMainWindow();
	QWidget* scriptMenu = mainWindow.findChild<QWidget*>("scriptMenu");
	if (scriptMenu)
	{
		if (mainWindow.isRibbonStyle())
		{
			scriptMenu->setVisible(visible);
			ArkivRibbonMainWindow& ribbonMainWindow = static_cast<ArkivRibbonMainWindow&>(mainWindow);
			if (visible)
			{
				slastActivatedRibbonPage = ribbonMainWindow.ribbonBar()->currentIndexPage();

                ribbonMainWindow.ribbonBar()->setAllowPopups(false);
                ribbonMainWindow.ribbonBar()->setCurrentPage(scriptMenu->property("index").toInt());
                ribbonMainWindow.ribbonBar()->setAllowPopups(true);
            }
			else if (slastActivatedRibbonPage >= 0)
			{
                ribbonMainWindow.ribbonBar()->setAllowPopups(false);
                ribbonMainWindow.ribbonBar()->setCurrentPage(slastActivatedRibbonPage);
                ribbonMainWindow.ribbonBar()->setAllowPopups(true);
			}
		}
		else
		{
			QMenu* pMenu = dynamic_cast<QMenu*>(scriptMenu);
			RBXASSERT(pMenu);
			if (pMenu)
				pMenu->menuAction()->setVisible(visible);
		}
	}
}

void ArkivScriptDoc::onSelectionChanged()
{
    // update actions modified on selection change
    UpdateUIManager&  updateUIManager = UpdateUIManager::Instance();
    ArkivMainWindow& rbxMainWindow = updateUIManager.getMainWindow();
    if (rbxMainWindow.isRibbonStyle())
    {
        updateUIManager.updateAction(*(rbxMainWindow.commentSelectionAction));
        updateUIManager.updateAction(*(rbxMainWindow.uncommentSelectionAction));
    }
}

void ArkivScriptDoc::reloadLiveScript()
{
    if (!m_pParentDoc || (!m_pParentDoc->isSimulating() && !m_script.isModuleScript()))
        return;
    
    applyEditChanges();
    
	try
	{
        RBX::DataModel::LegacyLock lock(m_dataModel, RBX::DataModelJob::Write);
		m_script.reloadLiveScript();
 	}
	catch (std::exception& e)
	{
		RBX::StandardOut::singleton()->print(RBX::MESSAGE_ERROR, e.what());
	}
}

void ArkivScriptDoc::explainBreakpointsDisabled()
{
	QMessageBox mb;
	mb.setText("Breakpoints are currently disabled for LinkedSource.");
	mb.exec();
}

void ArkivScriptDoc::removeScriptLock()
{
	ArkivIDEDoc* ideDoc = ArkivDocManager::Instance().getPlayDoc();
	RBXASSERT(ideDoc && ideDoc->isCloudEditSession());

	boost::shared_ptr<RBX::DataModel> dataModel = ideDoc->getEditDataModel();
	// if edit mode use the current script  else for play solo get the corresponding script in Edit datamodel 
	boost::shared_ptr<RBX::LuaSourceContainer> lsc = ideDoc->isPlaySolo() ? RBX::Instance::fastSharedDynamicCast<RBX::LuaSourceContainer>(ideDoc->getEditScriptByPlayInstance(m_script.toInstance().get()))
																		  : m_script.toInstance();
	if (lsc)
	{
		RBX::DataModel::LegacyLock lock(dataModel, RBX::DataModelJob::Write);
		RBX::Network::Player* localPlayer = RBX::Network::Players::findLocalPlayer(dataModel.get());
		if (localPlayer && lsc->getCurrentEditor() == localPlayer)
		{
			lsc->setCurrentEditor(NULL);
			lsc->fireSourceChanged();
			m_haveCloudEditScriptLock = false;
		}
	}
}