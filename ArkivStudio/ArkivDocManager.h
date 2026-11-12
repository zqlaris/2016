/**
 * ArkivDocManager.h
 * Copyright (c) 2013 ARKIV Corp. All Rights Reserved.
 */

#pragma once

// Qt Headers
#include <QObject>
#include <QMap>
#include <QIcon>

// 3rd Party Headers
#include "boost/shared_ptr.hpp"

// Arkiv Headers
#include "rbx/BaldPtr.h"
#include "V8DataModel/DataModel.h"

// Arkiv Studio Headers
#include "IArkivDoc.h"
#include "LuaSourceBuffer.h"

class QPoint;

class ArkivMainWindow;
class ArkivObjectBrowserDoc;
class ArkivWebDoc;
class ArkivScriptDoc;
class DocTabManager;
class DocDockManager;
class ArkivIDEDoc;

namespace RBX
{
	class Instance;
    class DataModel;
}

typedef QMap< QString,RBX::BaldPtr<IArkivDoc> > tKeyDocMap;
typedef QList< RBX::BaldPtr<ArkivScriptDoc> > tScriptDocs;
typedef QList<boost::shared_ptr<RBX::Instance> > tPlayModifiedScriptList;

class ArkivDocManager : public QObject
{
    Q_OBJECT

public:
	
	static ArkivDocManager& Instance();

	void initialize(ArkivMainWindow& mainWindow);
	void shutDown();

    bool requestCloseAllDocs();
    bool requestCloseAndSaveAllDocs();
    void closeAllDocs();

    void registerOpenedScriptDoc(ArkivScriptDoc& doc, LuaSourceBuffer script);
	void deregisterScriptDoc(ArkivScriptDoc& doc);
    void closeDoc(const LuaSourceBuffer& script);
	ArkivObjectBrowserDoc* getObjectBrowserDoc();

    const tScriptDocs& getOpenScriptDocs() { return m_OpenScriptDocs; }
	ArkivScriptDoc* findOpenScriptDoc(LuaSourceBuffer script);
    
    tPlayModifiedScriptList& getPlayModifiedScriptList() { return m_PlayModifiedScriptList; }

	IArkivDoc* getOrCreateDoc(IArkivDoc::RBXDocType docType);
	ArkivScriptDoc* openDoc(LuaSourceBuffer script);
	
    void removeDoc(IArkivDoc& doc);

	void configureDocWidget(IArkivDoc& doc);
	
	void setCurrentDoc(IArkivDoc* doc);
    IArkivDoc* getCurrentDoc() const       { return m_pCurrentDoc; }
    ArkivIDEDoc* getPlayDoc() const        { return m_pPlayDoc; }
	ArkivWebDoc* getStartPageDoc() const   { return m_pWebDoc; }

    int getDocCount() const                 { return m_KeyDocMap.size(); }

	void updateWindowMenu();
    void setDocTitle(IArkivDoc& doc,const QString& displayName,const QString& fileName,const QIcon& icon = QIcon());

    void detachDoc(IArkivDoc& doc,bool dragging);
    void attachDoc(IArkivDoc& doc, int index = -1);

    void setDockHoverOverPos(const QPoint& globalPos);
    bool attemptAttach(IArkivDoc& doc,const QPoint& globalPos);

    void setPlayDocCentralWidget();
    void restoreCentralWidget();

Q_SIGNALS:
	void currentDocChanged();

public Q_SLOTS:

	void openDoc(shared_ptr<RBX::Instance> script, int lineNumber);
	
    void onActivateWindow();

private:

	ArkivDocManager();
	virtual ~ArkivDocManager();

    void activateDoc(int index);
    RBX::BaldPtr<ArkivMainWindow>          m_pMainWindow;
	tKeyDocMap			                    m_KeyDocMap;
	RBX::BaldPtr<IArkivDoc>                m_pCurrentDoc;
	RBX::BaldPtr<ArkivIDEDoc>              m_pPlayDoc;
	RBX::BaldPtr<ArkivObjectBrowserDoc>    m_pObjectBrowser;
	RBX::BaldPtr<ArkivWebDoc>              m_pWebDoc;
	tScriptDocs				                m_OpenScriptDocs;
    RBX::BaldPtr<DocTabManager>             m_DocTabManager;
    RBX::BaldPtr<DocDockManager>            m_DocDockManager;
    tPlayModifiedScriptList                 m_PlayModifiedScriptList;
};
