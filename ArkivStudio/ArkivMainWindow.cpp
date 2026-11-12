/**
 * ArkivMainWindow.cpp
 * Copyright (c) 2013 ARKIV Corp. All rights reserved.
 */

#include "stdafx.h"
#include "ArkivMainWindow.h"

// Qt Headers
#include <QNetworkProxyFactory>
#include <QFileOpenEvent>
#include <QDateTime>
#include <QScrollBar>
#include <QFileInfo>
#include <QDesktopServices>
#include <QDir>
#include <QComboBox>
#include <QToolTip>
#include <QFileDialog>
#include <QLineEdit>
#include <QLabel>
#include <QToolBar>
#include <QToolButton>
#include <QCompleter>
#include <QWidgetAction>
#include <QProcess>
#include <QSignalMapper>
#include <QSplashScreen>
#include <QSharedMemory>
#include <QShortcut>
#include <QPrintDialog>
#include <QPrintPreviewDialog>
#include <QPageSetupDialog>
#include <QResource>
#include <QDesktopWidget>
#include <QNetworkProxy>
#include <QtConcurrentRun>

// 3rd Party Headers
#include "boost/filesystem/path.hpp"
#include "boost/iostreams/stream.hpp"
#include "boost/iostreams/device/array.hpp"

// Arkiv Headers
#include "util/standardout.h"
#include "util/ScopedAssign.h"
#include "util/RbxStringTable.h"
#include "util/SoundService.h"
#include "script/ScriptContext.h"
#include "v8datamodel/DebugSettings.h"
#include "v8datamodel/PartInstance.h"	
#include "v8datamodel/ModelInstance.h"
#include "v8datamodel/Explosion.h"
#include "v8datamodel/PluginManager.h"
#include "v8datamodel/GameBasicSettings.h"
#include "v8datamodel/FastLogSettings.h"
#include "v8datamodel/Stats.h"
#include "v8world/Contact.h"
#include "v8kernel/Body.h"
#include "v8kernel/ContactConnector.h"
#include "rbx/BaldPtr.h"
#include "rbx/CEvent.h"
#include "Network/Players.h"
#include "CountersClient.h"
#include "FastLog.h"
#include "SharedLauncher.h"
#include "ArkivStudioVersion.h"
#include "ArkivQuickAccessConfig.h"
#include "RenderSettingsItem.h"
#include "ArkivServicesTools.h"

#include "v8datamodel/CSGMesh.h"
#include "../CSG/CSGKernel.h"

#ifdef _WIN32
	#include "VersionInfo.h"
	#include "WinInet.h"
    #include <atlsync.h>
#else
    #include "BreakpadCrashReporter.h"
    #include <semaphore.h>
#endif

// Arkiv Studio Headers
#include "FunctionMarshaller.h"
#include "ArkivDocManager.h" 
#include "ArkivCustomWidgets.h"
#include "Arkiv.h"
#include "ArkivSettings.h"
#include "ArkivSettingsDialog.h"
#include "ArkivDiagnosticsView.h"
#include "ArkivScriptReview.h"
#include "ArkivTaskScheduler.h"
#include "CommonInsertWidget.h"
#include "ArkivToolBox.h"
#include "StudioUtilities.h"
#include "ArkivTextOutputWidget.h"
#include "QtUtilities.h"
#include "AuthoringSettings.h"
#include "UpdateUIManager.h"
#include "ArkivPluginHost.h"
#include "WebDialog.h"
#include "ArkivApplicationManager.h"
#include "AuthenticationHelper.h"
#include "ArkivIDEDoc.h"
#include "ArkivInputConfigDialog.h"
#include "ArkivKeyboardConfig.h"
#include "ArkivMouseConfig.h"
#include "ArkivStudioVerbs.h"
#include "ArkivScriptDoc.h"
#include "ShortcutHelpDialog.h"
#include "ArkivUser.h"
#include "AutoSaveDialog.h"
#include "InsertServiceDialog.h"
#include "StudioIntellesense.h"
#include "ArkivWebDoc.h"
#include "RbxWorkspace.h"
#include "FindDialog.h"
#include "ScriptTextEditor.h"

#include "Util/ArkivGoogleAnalytics.h"
#include "StudioDeviceEmulator.h"

FASTFLAGVARIABLE(StudioCheckForUpgradeEnabled, false)
FASTFLAGVARIABLE(StudioSeparateActionByActivationMethod, false)
FASTFLAGVARIABLE(StudioFixMacStartPage, false)
FASTFLAGVARIABLE(StudioSplashScreenUntilOpen, false)
FASTFLAGVARIABLE(StudioEarlyCookieConstraintCheckGlobal, false)
FASTSTRINGVARIABLE(StudioCookieConstraintUrlFragment, "fulfillconstraint")

FASTINTVARIABLE(StudioArkivAnalyticsLoad, 100);
FASTINTVARIABLE(StudioBootstrapperVersionNumber, 52886)
FASTINTVARIABLE(StudioInsertDeletionCheckTimeMS, 8000)

FASTFLAGVARIABLE(StudioCustomStatsEnabled, false)
FASTFLAGVARIABLE(StudioSettingsGAEnabled, true)
FASTFLAGVARIABLE(AssertOnConfigurationReportToGA, true)
FASTFLAGVARIABLE(ReportBuildVSEditMode, true)
FASTFLAGVARIABLE(TeamCreateEnableDownloadLocalCopy, true)
FASTFLAGVARIABLE(StudioDoublingOnUploadFixEnabled, true)

FASTFLAG(GoogleAnalyticsTrackingEnabled)
FASTFLAG(StudioInSyncWebKitAuthentication)
FASTFLAG(StudioDataModelIsStudioFix)
FASTFLAG(StudioShowTutorialsByDefault)
FASTFLAG(DontSwallowInputForStudioShortcuts)
FASTFLAG(StudioSettingsGAEnabled)
FASTFLAG(UseBuildGenericGameUrl)

FASTINT(StudioWebDialogMinimumWidth)
FASTINT(StudioWebDialogMinimumHeight)

DYNAMIC_LOGGROUP(GoogleAnalyticsTracking)
LOGGROUP(Network)

FASTFLAGVARIABLE(Dep, true)

static const int MaxLengthFilenameMRU   = 64;                    //!< maximum length of a filename in the MRU list
static const char* sWindow_Title        = "ARKIV Studio";  //!< default main window title when no place selected
static const char* sDialog_Title        = "ARKIV Studio";       //!< default child dialog title
static const int SplashTotalTime        = 3505;                  //!< minimum time to display splashscreen

bool ArkivMainWindow::sIsAppRunning = false;
const QString ArkivMainWindow::NEW_PLACE_FILENAME = "ARKIV_NEW_PLACE";

bool ArkivMainWindow::preventActionCounterSending = false;

QString ArkivMainWindow::sWindowStateKey = "window_state";
QString ArkivMainWindow::sGeometryKey = "window_geometry";

#ifdef _WIN32
	#include "LogManager.h"
	#include "DumpErrorUploader.h"

	static MainLogManager mainLogManager("ArkivStudio", ".ArkivStudio.dmp", ".ArkivStudio.crashevent");
	static boost::scoped_ptr<DumpErrorUploader> dumpErrorUploader;
#endif

#ifdef __APPLE__
	#include "LogProvider.h"
	static LogProvider logProvider;

    #include "StudioMacUtilities.h"
#endif

ArkivMainWindow* ArkivMainWindow::get(QObject* context)
{
	while(context != NULL && dynamic_cast<ArkivMainWindow*>(context) == NULL)
	{
		context = context->parent();
	}

	return static_cast<ArkivMainWindow*>(context);
}

ArkivMainWindow::ArkivMainWindow(const QMap<QString, QString> argMap)
: ArkivRibbonMainWindow(this)
, m_pSettingsDialog(NULL)
, m_pMinutesPlayedTimer(NULL)
, m_pInsertServiceDlg(NULL)
, m_pShortcutHelpDialog(NULL)
, m_pInputConfigDialog(NULL)
, m_pPluginHost(new ArkivPluginHost(this))
, m_splashScreen(NULL)
, m_publishGameDialog(NULL)
, m_pCounterSenderTimer(NULL)
, m_AutoSaveAccum(0)
, m_IsInitialized(false)
, m_pPublishedProjectsWebDialog(NULL)
, m_isRibbon(false)
, m_fileOpenHandled(false)
, m_BuildMode(BM_ADVANCED)
, m_IgnoreCloudEditDisconnect(false)
, m_editScriptActions("EditScript", &studioAnalytics)
, m_mouseActions("ManipulatePart", &studioAnalytics)
, m_inserts("Inserts", &studioAnalytics)
, m_cookieConstraintChecker(NULL)
, m_cookieConstraintCheckDone(NULL)
{
	try
	{
		QNetworkProxyFactory::setUseSystemConfiguration(true);

		// grab all of our known args from the map (to be used later)
		parseCommandLineOptions(argMap);

        QTime splashTime = QTime::currentTime();
        if ( showEventArg.isEmpty() )
        {
            // can't set window flags in constructor because other ones are appended that we don't want
            m_splashScreen = new QSplashScreen(this,QPixmap(":/images/ArkivStudioSplash.png"));

#ifdef Q_WS_WIN32
            Qt::WindowFlags flags = Qt::SplashScreen | Qt::FramelessWindowHint;
#else
            // Qt::Tool makes the window on top of the Z order on Mac
            Qt::WindowFlags flags = Qt::Tool | Qt::FramelessWindowHint;
#endif

            // now we can set window flags
            m_splashScreen->setWindowFlags(flags);  

            m_splashScreen->raise();
            m_splashScreen->show();
        }

		//start the bootstrapper on Mac, start the Event on Windows
		checkUpdater(true,startEventArg);
		        
		SetBaseURL(ArkivSettings::getBaseURL().toStdString());
		
		// make sure we call this first, this will initialize boost related stuff also 
		// or else we can run into raise condition which doing HTTP init as being mentioned here
		// - https://svn.boost.org/trac/boost/ticket/6320
		boost::filesystem::path::codecvt();

		RBX::Game::globalInit(true);

		// get logging going quickly, so any output is recorded
		setupLogging();
        RBX::Log::current()->writeEntry(RBX::Log::Information,"ArkivMainWindow::ArkivMainWindow - start");

		RBX::HttpFuture settingsFuture = FetchClientSettingsDataAsync(CLIENT_APP_SETTINGS_STRING, CLIENT_SETTINGS_API_KEY);
		try 
		{
			LoadClientSettingsFromString(CLIENT_APP_SETTINGS_STRING, settingsFuture.get(), &RBX::ClientAppSettings::singleton());
		} 
		catch(std::exception&)
		{
			FASTLOG(FLog::Error, "Failed to load settings");
		}

		AuthenticationHelper::Instance().authenticateUserAsync(urlArg, ticketArg);

        //set up ui using the .ui file
        setupUi(this);

		// set up external analytics reporting variables
		QString country = QLocale::countryToString(QLocale::system().country());
#ifdef _WIN32
		RBX::Analytics::setReporter("PC Studio");
#else
		RBX::Analytics::setReporter("Mac Studio");
#endif
		RBX::Analytics::setLocation(country.toStdString());
		RBX::Analytics::setAppVersion(ArkivSettings::getVersionString().toStdString());

		// set up influxdb reporting
		RBX::Analytics::InfluxDb::init();

        //initializing textOutputWidget early to catch any output in globalInit
        m_pTextOutput = new ArkivTextOutputWidget(dockWidgetContents_2);
		
		RBX::Http arkivRequest(AuthenticationHelper::getLoggedInUserUrl().toStdString());
		RBX::Http externalRequest("http://www.google.com");

		QSettings retentionData("Arkiv", "Retention");

		static const char* const kRetentionInstallDateKey = "InstallDate";
		static const char* const kRetentionLastRunDateKey = "LastRunDate";
		QString dateString = QDate::currentDate().toString("yyyyMMdd");
		QString installDate = retentionData.value(kRetentionInstallDateKey, "").toString();

		if (installDate.isEmpty())
		{
			StudioUtilities::setIsFirstTimeOpeningStudio(true);
		}

		// Init our engine - can only use ClientAppSettings AFTER this!!!
		Arkiv::globalInit(urlArg, ticketArg, settingsFuture);
		RBX::Stats::reportGameStatus("AppStarted");	// must be after gloablInit due to http initialization

        Qtitan::RibbonStyle::setStyleVersion(1);
		
		// Disable FRM in studio by default
		CRenderSettingsItem::singleton().setEnableFRM(false);
        
		// Following are the different modes launched from website 
		// (this is required since website conveys 'only' to be launched from Studio but doesn't specify the mode
		// 1) Build mode: BuildArgument == True (default mode set)
		// 2) Edit mode: BuildArgument == True && ScriptArgument has edit.ashx
		// 3) Start Page mode: BuildArgument == True && ScriptArgument is empty
		if (StudioUtilities::containsEditScript(argMap[SharedLauncher::ScriptArgument])
			|| ((argMap[SharedLauncher::BuildArgument]=="TRUE") && argMap[SharedLauncher::ScriptArgument].isEmpty()))
		{
			m_BuildMode = BM_ADVANCED;
			StudioUtilities::setAvatarMode(false);
		}
        
		{
#ifdef __APPLE__
			int useCurlPercentage = RBX::ClientAppSettings::singleton().GetValueHttpUseCurlPercentageMacStudio();
#else
			int useCurlPercentage = RBX::ClientAppSettings::singleton().GetValueHttpUseCurlPercentageWinStudio();
#endif
			bool useCurl = rand() % 100 < useCurlPercentage;
#ifdef _WIN32
			{
				INTERNET_PER_CONN_OPTION_LIST    List;
				INTERNET_PER_CONN_OPTION         Option[1];
				unsigned long                    nSize = sizeof(INTERNET_PER_CONN_OPTION_LIST);

				Option[0].dwOption = INTERNET_PER_CONN_FLAGS;

				List.dwSize = sizeof(INTERNET_PER_CONN_OPTION_LIST);
				List.pszConnection = NULL;
				List.dwOptionCount = 1;
				List.dwOptionError = 0;
				List.pOptions = Option;

				if (InternetQueryOption(NULL, INTERNET_OPTION_PER_CONNECTION_OPTION, &List, &nSize))
				{
					if (Option[0].Value.dwValue & PROXY_TYPE_PROXY)
					{
						// As of when this was added, curl could not handle ssl over proxies
						// so fall back to win inet when proxy is detected
						useCurl = false;
					}
				}
			}
#endif
			FASTLOG1(FLog::Network, "Use CURL = %d", useCurl);
			RBX::Http::SetUseCurl(useCurl);
		}

        RBX::Http::useDefaultTimeouts = false;
		
		// init google analytics
		std::string googleAnalyticsAccountPropId = RBX::ClientAppSettings::singleton().GetValueGoogleAnalyticsAccountPropertyID();
		if (m_BuildMode == BM_BASIC)
		{
			// Set the account property id to either the Build Mode production account or the test account
			// by checking the baseURL for the company domain "arkiv.com".
			QString baseURL(ArkivSettings().getBaseURL());
			if (baseURL.endsWith("arkiv.com", Qt::CaseInsensitive))
				googleAnalyticsAccountPropId = "UA-43420590-4"; // Production
			else
				googleAnalyticsAccountPropId = "UA-43420590-5"; // Test
		}

		RBX::ArkivGoogleAnalytics::lotteryInit(googleAnalyticsAccountPropId, 
			RBX::ClientAppSettings::singleton().GetValueGoogleAnalyticsThreadPoolMaxScheduleSize(), RBX::ClientAppSettings::singleton().GetValueGoogleAnalyticsLoadStudio(), "studio",
			FInt::StudioArkivAnalyticsLoad, "studioSid=");

		if(StudioUtilities::isFirstTimeOpeningStudio())
		{
			installDate = dateString;
			retentionData.setValue(kRetentionInstallDateKey, dateString);
			RBX::ArkivGoogleAnalytics::trackEventWithoutThrottling("Retention-Install",
				dateString.toStdString().c_str(), "none", 1);
		}

		QString lastRun = retentionData.value(kRetentionLastRunDateKey, "").toString();
		if (lastRun != dateString)
		{
			retentionData.setValue(kRetentionLastRunDateKey, dateString);
			RBX::ArkivGoogleAnalytics::trackEventWithoutThrottling("Retention-Run",
				installDate.toStdString().c_str(), dateString.toStdString().c_str(), 1);
		}

		// Send tracking information about the application.
		if (FFlag::GoogleAnalyticsTrackingEnabled)
		{
			QString label = m_BuildMode == BM_BASIC ? "Basic" : "IDE";

			// Extract everything from scriptArg before ".ashx"
			int httpIndex = scriptArg.indexOf("http");
			int ashxIndex = scriptArg.indexOf(".ashx");
			if(httpIndex != -1 && ashxIndex > httpIndex)
				label += " " + scriptArg.mid(httpIndex, ashxIndex - httpIndex + 5);

			RBX::ArkivGoogleAnalytics::trackEvent(GA_CATEGORY_STUDIO, "Start", label.toStdString().c_str());
			RBX::ArkivGoogleAnalytics::trackEvent(GA_CATEGORY_STUDIO, "Version", ArkivSettings::getVersionString().toStdString().c_str());
		}

		QtConcurrent::run(this, &ArkivMainWindow::checkInternetConnectionSendCounter, arkivRequest, externalRequest);

		if (AuthoringSettings::singleton().getUIStyle() == AuthoringSettings::Ribbon)
        {
			m_isRibbon = true;
            RBX::ArkivGoogleAnalytics::trackEvent(GA_CATEGORY_COUNTERS, "RibbonBar", "Launches", 1);
        }

		if (FFlag::StudioSettingsGAEnabled)
		{
			RBX::Reflection::PropertyIterator iter = AuthoringSettings::singleton().properties_begin();
			RBX::Reflection::PropertyIterator end = AuthoringSettings::singleton().properties_end();

			while (iter!=end)
			{
				RBX::Reflection::Property property = *iter;
                std::string valueString;
                if (!FFlag::AssertOnConfigurationReportToGA)
                {
                    valueString = property.getStringValue();
                }
				std::string description = property.getName().str;
				std::transform(description.begin(), description.end(), description.begin(), tolower);

				if (!(description == "parent" || description == "archivable" || description == "classname" || description == "datacost" 
					|| description == "name" || description == "arkivlocked"))
				{
					description += " On Start";
                    
                    if (FFlag::AssertOnConfigurationReportToGA)
                    {
                        valueString = "N/A";
                        if (property.hasStringValue())
                        {
                            valueString = property.getStringValue();
                        }
                    }
					RBX::ArkivGoogleAnalytics::trackEvent(GA_CATEGORY_STUDIO_SETTINGS, description.c_str(), valueString.c_str());
				}
				++iter;
			}

			AuthoringSettings::singleton().setDoSettingsChangedGAEvents(true);
		}

		//check for crash
		ArkivSettings settings;
		if (ArkivApplicationManager::instance().getApplicationCount() == 1 && settings.contains("appClosed") && !settings.value("appClosed").toBool())
		{
			sendCounterEvent("QTStudioCrashRecorded");
			if (FFlag::GoogleAnalyticsTrackingEnabled)
			{
				RBX::ArkivGoogleAnalytics::trackEvent(GA_CATEGORY_ERROR, "Crash");
			}
		}
		settings.setValue("appClosed", false);

#ifdef _WIN32
        if (FFlag::Dep)
        {
            typedef BOOL (WINAPI *SetProcessDEPPolicyPfn)(DWORD);
            SetProcessDEPPolicyPfn pfn= reinterpret_cast<SetProcessDEPPolicyPfn>(GetProcAddress(GetModuleHandle("Kernel32"), "SetProcessDEPPolicy"));
            if (pfn)
            {
                static const DWORD kEnable = 1;
                pfn(kEnable);
            }
        }
#endif

		if (FFlag::StudioCheckForUpgradeEnabled)
		{
			ArkivSettings settings;
			if(settings.value("studioVersion").toString() != ArkivSettings::getVersionString())
			{
				settings.setValue("studioVersion", ArkivSettings::getVersionString());
				sendCounterEvent("StudioUpgradedCounter", false);
                if (FFlag::GoogleAnalyticsTrackingEnabled)
				{
					RBX::ArkivGoogleAnalytics::trackEvent(GA_CATEGORY_STUDIO, "Upgrade", ArkivSettings::getVersionString().toStdString().c_str());
				}
			}
		}
		
        // Set the CSGMesh Factory to use sgCore.
        RBX::CSGMeshFactory::set(new RBX::CSGMeshFactorySgCore());

        initializeUI();

		//setup WikiSearch in scripts
		ScriptTextEditor::setupWikiLookup();

		// reset the position of the toolbars. so they are identical to the old studio.
		setToolbarPosition();

		//set up command toolbar
		setupCommandToolBar();

		//create material and color tool button
		setupCustomToolButton();

		//sends out slow counters every X seconds
		setupCounterSender();
		       
		//set default commands
		UpdateUIManager::Instance().setDefaultApplicationState();

		sIsAppRunning = true;

		// Set Security context Identity
		RBX::Security::Impersonator impersonate(RBX::Security::LocalGUI_);

		//setup statusbar and docks
		UpdateUIManager::Instance().init(this);
		
		ArkivScriptDoc::init(*this);
		
		if (isRibbonStyle())
		{
			setupRibbonBar();
		}
		else
		{
			setupViewMenu();
		}

		//set up slots
		setupSlots();
		
		 // set up shortcut key sequences
		assignAccelerators();

		updateRecentFilesUI();

        // Idempotent function - and if there is no open tab, we need to update actions (disable ones that need to be)
		UpdateUIManager::Instance().updateToolBars();

        setBuildMode(m_BuildMode);

		// save current state as default state
		saveDefaultApplicationState();

		// load the application states from memory
		loadApplicationStates();
				
        m_PropertyChangedConnection = AuthoringSettings::singleton().propertyChangedSignal.connect(
            boost::bind(&ArkivMainWindow::onPropertyChanged,this,_1));
        onPropertyChanged(NULL);

        if (FFlag::StudioEarlyCookieConstraintCheckGlobal ||
			ArkivSettings::getBaseURL().contains("arkivlabs", Qt::CaseInsensitive))
		{
			m_cookieConstraintChecker = new QWebView(NULL);
			m_cookieConstraintCheckDone = new QEventLoop(this);
			m_cookieConstraintChecker->setAttribute(Qt::WA_DeleteOnClose);
			m_cookieConstraintChecker->page()->setNetworkAccessManager(&ArkivNetworkAccessManager::Instance());
			connect(m_cookieConstraintChecker->page(), SIGNAL(loadStarted()), m_cookieConstraintChecker, SLOT(hide()));
			connect(m_cookieConstraintChecker, SIGNAL(loadFinished(bool)), this, SLOT(cookieConstraintCheckerLoadFinished(bool)));
			connect(m_cookieConstraintChecker, SIGNAL(destroyed(QObject*)), m_cookieConstraintCheckDone, SLOT(quit()));
			m_cookieConstraintChecker->load(ArkivSettings::getBaseURL());
			m_cookieConstraintCheckDone->exec();
			m_cookieConstraintCheckDone->deleteLater();
			m_cookieConstraintCheckDone = NULL;
			// if the window is destroyed from close we want to null it out here.
			m_cookieConstraintChecker = NULL;
		}
        
#ifdef _WIN32
        if ( showEventArg.isEmpty() ) 
            show();
#else
        show();
        
        // bootstrapper will wait for this event to exit
        sem_t *sem = sem_open("/arkivStudioStartedEvent", 0);
        if (sem != SEM_FAILED)
        {
            sem_post(sem);
            sem_close(sem);
        }
#endif
		
        // take the args that were passed in and act upon them
		// has to be at the very end of the constructor, or else the menu bar will behave weird.

		handleCommandLineOptions();
    	m_fileOpenHandled = false;

        //Mac will open file through finder event; need to handle open start page this way
        IArkivDoc* currentPlayDoc = ArkivDocManager::Instance().getPlayDoc();
        if (!currentPlayDoc)
        {
            // if nothing else opened, open a start web page
            actionStartPage->setChecked(true);
        }

#ifdef _WIN32
        if ( !showEventArg.isEmpty() ) 
        {
            // Application waits for this event before showing to the user
	        ATL::CEvent showEvent;
	        if ( showEvent.Open(EVENT_MODIFY_STATE, FALSE, qPrintable(showEventArg)) )
                ::WaitForSingleObject(showEvent,30 * 1000);
        }

        show();

		if ( !readyEventArg.isEmpty() ) 
		{
			// Bootstrapper will wait for this event, to make sure that app is loaded and ready
			ATL::CEvent readyEvent;
			if ( readyEvent.Open(EVENT_MODIFY_STATE, FALSE, qPrintable(readyEventArg)) )
				::WaitForSingleObject(readyEvent,30 * 1000);
		}
#endif

		// Unfortunately has to be called after show due to windowState not loading until then.
		UpdateUIManager::Instance().updateDockActionsCheckedStates();

		viewCommandBarAction->setChecked(commandToolBar->isVisible());

		//set window layout setting according to application states.
		//it has to be after loadApplicationStates. or else full screen button will not be initialized correctly.
		setWindowLayout();

        if ( AutoSaveDialog::checkForAutoSaveFiles() )
        {
            AutoSaveDialog dialog(this);
            while ( dialog.exec() == QDialog::Rejected )
            {
                /* nothing */
            }
        }

		if ( m_splashScreen )
        {
            // show splash screen for a minimum amount of time
            int waitTime = 0;
            if ( ArkivApplicationManager::instance().getApplicationCount() == 1 )
                waitTime = qMax(0,SplashTotalTime - splashTime.elapsed());
            QTimer::singleShot(waitTime,this,SLOT(onDeleteSplashScreen()));
		}

        setupActionCounters();

        ArkivKeyboardConfig::singleton().storeDefaults(*this);
        ArkivKeyboardConfig::singleton().loadKeyboardConfig(*this);
        ArkivMouseConfig::singleton().loadMouseConfig();

		m_IsInitialized = true;
	}
	catch (std::runtime_error const& exp)
	{
		// must make sure the splash screen is hidden before popping up any errors
        try
        {
            if ( m_splashScreen )
				onDeleteSplashScreen();
        }
        catch (...)
        {
			// ignore errors
        }

		QtUtilities::RBXMessageBox msgBox;
		msgBox.setIcon(QMessageBox::Critical);
		msgBox.setText(exp.what());
		msgBox.setStandardButtons(QMessageBox::Ok);
		msgBox.setDefaultButton(QMessageBox::Ok); 
		msgBox.exec();
		throw;
	}
    catch (...)
    {
        // must make sure the splash screen is hidden before popping up any errors
        try
        {
            if ( m_splashScreen )
                onDeleteSplashScreen();
        }
        catch (...)
        {
			// ignore errors
        } 
        throw;
    }

    if (FFlag::StudioSplashScreenUntilOpen && m_splashScreen)
    {
        m_splashScreen->raise();
        m_splashScreen->show();
    }

    RBX::Log::current()->writeEntry(RBX::Log::Information,"ArkivMainWindow::ArkivMainWindow - end");
}

ArkivMainWindow::~ArkivMainWindow()
{
    RBX::Log::current()->writeEntry(RBX::Log::Information,"ArkivMainWindow::~ArkivMainWindow");
    StudioUtilities::stopMobileDevelopmentDeployer();

    m_PropertyChangedConnection.disconnect();

    //remove all documents
	ArkivDocManager::Instance().shutDown();

	//stop UI update
	UpdateUIManager::Instance().shutDown();

	//do a global shut down
	Arkiv::globalShutdown();

	//Set appClosed true before shutdown
	if (ArkivApplicationManager::instance().getApplicationCount() == 1)
	{
		ArkivSettings settings;
		settings.setValue("appClosed", true);
	}
}

void ArkivMainWindow::setupLogging()
{
#ifdef _WIN32
	RBX::Log::setLogProvider(&mainLogManager);
	mainLogManager.WriteCrashDump();

	dumpErrorUploader.reset(new DumpErrorUploader(true, "Studio"));
	std::string dmpHandlerUrl =  GetDmpUrl(::GetBaseURL(), true);
	dumpErrorUploader->InitCrashEvent(dmpHandlerUrl, mainLogManager.getCrashEventName());
	dumpErrorUploader->Upload(dmpHandlerUrl);
#endif

#ifdef __APPLE__
	RBX::Log::setLogProvider(&logProvider);
#endif
}

void ArkivMainWindow::causeCrash()
{
	RBXCRASH();
}

bool ArkivMainWindow::checkUpdater(bool showUpdateOptionsDialog, const QString& initDoneEventName) const
{
#ifdef Q_WS_MAC
	QString bootstrapper = QCoreApplication::applicationFilePath(); 
	if(bootstrapper.lastIndexOf("ArkivStudio") > -1)
		bootstrapper = bootstrapper.replace(bootstrapper.lastIndexOf("ArkivStudio"), 12, "ArkivStudio.app/Contents/MacOS/ArkivStudio");
	else
		return false; //can't find proper path
	
	RBX::StandardOut::singleton()->printf(RBX::MESSAGE_INFO, "boostrapper path: %s", qPrintable(bootstrapper));
	
	QStringList args;
	pid_t processID = getpid();
	QString ppid;
	ppid.setNum(processID);
	QString showUpdate = QString(showUpdateOptionsDialog ? "true" : "false");
	args << "-check" << "true" << "-ppid" << ppid << "-updateUI" << showUpdate;
	QProcess::startDetached(bootstrapper, args);
#else
    if ( !initDoneEventName.isEmpty() )
    {
	    // Bootstrapper will wait for this event, to make sure that app was started
	    ATL::CEvent arkivQtStudioStartedEvent;
	    if ( arkivQtStudioStartedEvent.Open(EVENT_MODIFY_STATE, FALSE, qPrintable(initDoneEventName)) )
		    arkivQtStudioStartedEvent.Set();
    }
#endif
	return true;
}

void ArkivMainWindow::parseCommandLineOptions(const QMap<QString, QString> argMap)
{
	fileLocationArg	= argMap[SharedLauncher::FileLocationArgument];
	urlArg 			= argMap[SharedLauncher::AuthUrlArgument];
	ticketArg 		= argMap[SharedLauncher::AuthTicketArgument];
    startEventArg   = argMap[SharedLauncher::StartEventArgument];
    readyEventArg   = argMap[SharedLauncher::ReadyEventArgument];
	showEventArg    = argMap[SharedLauncher::ShowEventArgument];
	scriptArg 		= argMap[SharedLauncher::ScriptArgument];
	QString sBrowserTrackerId = argMap[SharedLauncher::BrowserTrackerId];

	QString sWidth	= argMap[StudioUtilities::StudioWidthArgument];
	QString sHeight	= argMap[StudioUtilities::StudioHeightArgument];

	// convert loadfile('http://www.arkiv.com/game/join.ashx')() to just the url
	if (StudioUtilities::containsJoinScript(scriptArg) && scriptArg.contains("loadfile("))
	{
		int urlBegin = scriptArg.indexOf("(")+2; // skip over the qoute
		int urlEnd = scriptArg.indexOf(")")-1;
		scriptArg = scriptArg.mid(urlBegin, urlEnd - urlBegin);
	}

    if ( argMap[SharedLauncher::BuildArgument] == "TRUE" )
        m_BuildMode = BM_BASIC;
    else if ( argMap[SharedLauncher::IDEArgument] == "TRUE" )
        m_BuildMode = BM_ADVANCED;

    if ( argMap[SharedLauncher::TestModeArgument] == "TRUE" )
        StudioUtilities::setTestMode(true);
    if ( argMap[SharedLauncher::AvatarModeArgument] == "TRUE" )
        StudioUtilities::setAvatarMode(true);

	if ( argMap[StudioUtilities::EmulateTouchArgument] == "TRUE" )
		StudioDeviceEmulator::Instance().setIsEmulatingTouch(true);

	if ( !sWidth.isEmpty())
		StudioDeviceEmulator::Instance().setCurrentDeviceWidth(sWidth.toInt());

	if ( !sHeight.isEmpty())
		StudioDeviceEmulator::Instance().setCurrentDeviceHeight(sHeight.toInt());

	if ( !sBrowserTrackerId.isEmpty())
		RBX::Stats::setBrowserTrackerId(sBrowserTrackerId.toStdString());
}

void ArkivMainWindow::handleCommandLineOptions()
{    
	// make sure sound is disabled if it should be before we create datamodel 
	if (StudioUtilities::isTestMode() && !StudioUtilities::isAvatarMode() && StudioUtilities::containsGameServerScript(scriptArg))
	{
		if (AuthoringSettings::singleton().getTestServerAudioBehavior() == AuthoringSettings::OnlineGame)
		{
			RBX::Soundscape::SoundService::soundDisabled = true;
		}
	}

    // check if fileOpen has already been handled
    if (m_fileOpenHandled)
        return;

    bool openedPlace = handleFileOpen(fileLocationArg,IArkivDoc::IDE,scriptArg);
    if(!openedPlace)
    {
        // if nothing else opened, open a start web page
        actionStartPage->setChecked(true);
    }
#ifdef __APPLE__
    // if Studio is opening in sever/client mode then diable App Nap on Mac (DE13936)
    else if (StudioUtilities::containsGameServerScript(scriptArg) || StudioUtilities::containsJoinScript(scriptArg))
    {
        StudioMacUtilities::disableAppNap("Server/Client Mode");
    }
#endif

	if (openedPlace && isRibbonStyle() && StudioUtilities::isTestMode() && !StudioUtilities::isAvatarMode() && StudioUtilities::containsGameServerScript(scriptArg))
	{
		// start local server, so we can cleanup processes started by 'server'
		ArkivApplicationManager::instance().startLocalServer();
		// this is required to update client server related actions
		UpdateUIManager::Instance().updateToolBars();

		ArkivIDEDoc* pIDEDoc = ArkivDocManager::Instance().getPlayDoc();

		int numPlayers = ArkivSettings().value("rbxRibbonNumPlayer").toInt();
		if (numPlayers > 0)
		{
			if (pIDEDoc && pIDEDoc->getDataModel())
			{
				StartServerAndPlayerVerb* pVerb = dynamic_cast<StartServerAndPlayerVerb*>(pIDEDoc->getDataModel()->getVerb("StartServerAndPlayerVerb"));
				if (pVerb)
					pVerb->launchPlayers(numPlayers);
			}			
		}
		StudioUtilities::startMobileDevelopmentDeployer();

		if (pIDEDoc && pIDEDoc->getDataModel())
		{
			pIDEDoc->initServerAudioBehavior();
		}
	}

    if (!openedPlace)
    {
        if (m_splashScreen)
            onDeleteSplashScreen();
    }
}

void ArkivMainWindow::moveEvent(QMoveEvent * event)
{
	ArkivRibbonMainWindow::moveEvent(event);
	updateEmbeddedFindPosition();
}

bool ArkivMainWindow::eventFilter(QObject* watched,QEvent* evt)
{
	if (FFlag::StudioSeparateActionByActivationMethod && evt->type() == QEvent::Shortcut)
	{
		if (QAction* action = dynamic_cast<QAction*>(watched))
		{
			if (commonSlotShortcut(action, !action->isChecked()))
			{
				evt->accept();
				return true;
			}
		}
	}

#ifdef Q_WS_MAC
	// handle special file open command on Mac coming from Finder
	if ( evt->type() == QEvent::FileOpen && watched == qApp )
	{
		if (FFlag::StudioFixMacStartPage)
    	{
        	// Make sure the start page is the first thing opened.
        	actionStartPage->setChecked(true);
		}

		m_fileOpenHandled = handleFileOpen(static_cast<QFileOpenEvent*>(evt)->file(), IArkivDoc::IDE);
		return true;
	}
    else if (isRibbonStyle() && (evt->type() == QEvent::Polish) && watched->inherits("QMenu"))
    {
        static_cast<QMenu*>(watched)->setFont(QApplication::font());
    }
    else
#endif
    if (evt->type() == QEvent::KeyPress || evt->type() == QEvent::ShortcutOverride)
    {
        // ignore shortcut events during busy state
        if ( UpdateUIManager::Instance().isBusy() )
        {
            evt->accept();
            return true;
        }
    }

    if (evt->type() == QEvent::NonClientAreaMouseButtonPress)
        Studio::Intellesense::singleton().deactivate();

 	if (evt->type() == QEvent::MouseMove ||
 		evt->type() == QEvent::KeyPress)
 	{
 		keepAliveAnalyticsSession();
 	}

	if ( (evt->type() == QEvent::FocusIn || evt->type() == QEvent::FocusOut) &&
		 AuthoringSettings::singleton().onlyPlayFocusWindowAudio )
	{
		if (IArkivDoc* playDoc = ArkivDocManager::Instance().getPlayDoc())
		{
			if (ArkivIDEDoc* ide = dynamic_cast<ArkivIDEDoc*>(playDoc))
			{
				ide->setMuteAllSounds(!QApplication::activeWindow());
				if (QAction* audioToggleWidget = findChild<QAction*>("audioToggleAction"))
				{
					audioToggleWidget->setChecked(!QApplication::activeWindow());
				}
			}
		}
	}
	
	if ( watched == qApp )
		return qApp->eventFilter(watched,evt);
	else
		return QMainWindow::eventFilter(watched,evt);
}

void ArkivMainWindow::setWindowLayout()
{
	actionFullScreen->setChecked(isFullScreen());
}

void ArkivMainWindow::setupViewMenu()
{
	menuView->insertAction(menuView->actions().value(1), resetViewAction);
	menuView->insertSeparator(resetViewAction);		

	// Add dock widgets to view menu
    //  Insert after Start Page.  Start Page is first (index 0).
	UpdateUIManager::Instance().setupDockWidgetsViewMenu(*menuView->actions().value(1));    

	// Set up the toolbar
	menuToolBars->addAction(standardToolBar->toggleViewAction());
	menuToolBars->addAction(advToolsToolBar->toggleViewAction());
	menuToolBars->addAction(editCameraToolBar->toggleViewAction());
	menuToolBars->addAction(commandToolBar->toggleViewAction());
	menuToolBars->addAction(runToolBar->toggleViewAction());
	menuToolBars->addAction(viewToolsToolBar->toggleViewAction());
	if (!RBX::MouseCommand::isAdvArrowToolEnabled()) // Remove this, this flag is true
		menuToolBars->addAction(oldToolsToolBar->toggleViewAction());
}

void ArkivMainWindow::toggleFullScreen(bool state)
{
	if (isFullScreen() == state)
		return;
	
	// Toggle
	setWindowState(windowState() ^ Qt::WindowFullScreen);

    // Toggle fullscreen glitches with layout on Mac for Ribbon Bar (send event to update layout)
#ifdef Q_WS_MAC
	if (isRibbonStyle())
	{
        Qtitan::RibbonPage* pPage = ribbonBar()->getPage(ribbonBar()->currentIndexPage());
        if (pPage)
        {
            QEvent evt(QEvent::LayoutRequest);
            QApplication::sendEvent(pPage, &evt);
        }
    }
#endif

	// if we have an IDE, we need to lock the datamodel
    IArkivDoc* playDoc = ArkivDocManager::Instance().getPlayDoc();
    if ( playDoc )
    {
        ArkivIDEDoc* ide = dynamic_cast<ArkivIDEDoc*>(playDoc);
        if ( ide )
        {
            RBX::DataModel::LegacyLock lock(ide->getDataModel(),RBX::DataModelJob::Write);
	        RBX::GameBasicSettings::singleton().setFullScreen(state);
            return;
        }
    }

    RBX::GameBasicSettings::singleton().setFullScreen(state);
}

bool ArkivMainWindow::commonSlotHelper(const QString& objectName, bool isChecked)
{
	bool handled = false;

	//action to be handled by the relevant document
	if (ArkivDocManager::Instance().getCurrentDoc())
		handled = ArkivDocManager::Instance().getCurrentDoc()->handleAction(objectName, isChecked);

	// Otherwise handle it ourselves
	if (!handled)
	{

		// Handle global dock actions here
		if (UpdateUIManager::Instance().getDockActionNames().contains(objectName))
		{
			handled = UpdateUIManager::Instance().toggleDockView(objectName);
		}
		else
		{
			// Check if IDE Doc can handle the action
			IArkivDoc* pPlayDoc = ArkivDocManager::Instance().getPlayDoc(); 
			if (pPlayDoc)
				handled = pPlayDoc->handleAction(objectName, isChecked);
		}
	}

	//update toolbar status
	UpdateUIManager::Instance().updateToolBars();

	return handled;
}

void ArkivMainWindow::commonSlot(bool isChecked)
{
	const QObject *pSender = sender();
	if (!pSender || dynamic_cast<QuickAccessBarProxyAction*>(sender()))
		return;

	if (!preventActionCounterSending || !FFlag::StudioSeparateActionByActivationMethod)
		sendActionCounterEvent(pSender->objectName());

	commonSlotHelper(pSender->objectName(), isChecked);
}

bool ArkivMainWindow::commonSlotShortcut(QAction* action, bool isChecked)
{
	if (!preventActionCounterSending)
		sendActionCounterEvent(action->objectName() + "Shortcut");

	return commonSlotHelper(action->objectName(), isChecked);
}

bool ArkivMainWindow::commonSlotQuickAccess(QAction* action)
{
	if (!preventActionCounterSending)
		sendActionCounterEvent(action->objectName() + "QuickAccess");

	return commonSlotHelper(action->objectName(), !action->isChecked());
}

void ArkivMainWindow::processAppEvent(void* pClosure)
{
	// Handle the event
	if (sIsAppRunning)
		RBX::FunctionMarshaller::handleAppEvent(pClosure);
	else	
		RBX::FunctionMarshaller::freeAppEvent(pClosure); // control flow comes here means application is closed
}

bool ArkivMainWindow::requestDocClose(IArkivDoc& doc, bool closeIfLastDoc)
{
    if ( !doc.getViewer() )
    {
		ArkivDocManager::Instance().removeDoc(doc);
        return true;
    }

	if ( StudioUtilities::isVideoUploading() || StudioUtilities::isScreenShotUploading())
	{
		QtUtilities::RBXMessageBox msgBox;
		msgBox.setIcon(QMessageBox::Question);
		msgBox.setText(QString("ARKIV is uploading %1. Quit anyway?").arg(StudioUtilities::isVideoUploading() ? "a video" : "an image"));
		msgBox.setStandardButtons(QMessageBox::Yes | QMessageBox::No);
		msgBox.setDefaultButton(QMessageBox::No);

		//user has pressed NO or close button, do not close the document
		if ( msgBox.exec() != QMessageBox::Yes )
			return false;	

		// user has pressed YES, modifying the uploading status to make sure 
		//  we don't show the message multiple times
		StudioUtilities::setVideoUploading(false);
		StudioUtilities::setScreenShotUploading(false);
	}

	if ( doc.isModified() )
	{
		IArkivDoc::RBXCloseRequest closeMode = doc.requestClose();

		if ( closeMode == IArkivDoc::CLOSE_CANCELED )
		{
			if ( &doc != ArkivDocManager::Instance().getCurrentDoc() )
                ArkivDocManager::Instance().setCurrentDoc(&doc);
			return false;
		}
        else if ( closeMode == IArkivDoc::REQUEST_HANDLED )
		{
            // LUA will handle it from here on out
			return false;
		}
		else if ( closeMode != IArkivDoc::NO_SAVE_NEEDED )
		{
            // ask the user if they want to save before close
		
			QtUtilities::RBXMessageBox msgBox;
			msgBox.setIcon(QMessageBox::Question);
			msgBox.setText("Save changes to " + doc.displayName() + " ?");
			msgBox.setStandardButtons(QMessageBox::Yes | QMessageBox::No | QMessageBox::Cancel);
			msgBox.setDefaultButton(QMessageBox::Yes);
			int ret = msgBox.exec();

			//if the user wants to save
			if ( ret == QMessageBox::Yes && !fileSave(&doc) )
            {
				// User hit the Yes to Save in the Yes No Cancel MsgBox,
				// but then did a Cancel on Save Dialog, change the state to Cancel
				ret = QMessageBox::Cancel;
            }
			
			//if the user want to cancel close
			if ( ret == QMessageBox::Cancel )
			{
				if ( &doc != ArkivDocManager::Instance().getCurrentDoc() )
                    ArkivDocManager::Instance().setCurrentDoc(&doc);
				return false;
			}
		}
    }

    // special case Start Page since it can be toggled in the View menu
	if ( doc.keyName() == "StartPage" && doc.docType() == IArkivDoc::BROWSER )
	    actionStartPage->setChecked(false);
	else if ( doc.docType() == IArkivDoc::OBJECTBROWSER )
	    objectBrowserAction->setChecked(false);
#ifdef Q_WS_MAC
    // On Mac, if we do not make the IDE document current then it results in DE7073
    // Combination of QWidget and ViewBase creation coupled with deletion of IDE document
    // without making it current results in non responding keyboard (?)
    else if ((doc.docType() == IArkivDoc::IDE) && (&doc != ArkivDocManager::Instance().getCurrentDoc()))
        ArkivDocManager::Instance().setCurrentDoc(&doc);
#endif

	// WARNING: Do not use doc to call any function after this (it will get deleted)
    ArkivDocManager::Instance().removeDoc(doc);

    updateWindowTitle();

	if ( ArkivDocManager::Instance().getDocCount() == 0 && closeIfLastDoc &&
        (ArkivApplicationManager::instance().getApplicationCount() > 1 || getBuildMode() == BM_BASIC))
	{
		// If there are no tabs remaining and this is another instance of Studio open, close this one
		close();
	}

    return true;
}

void ArkivMainWindow::fileNew()
{
	handleFileOpen(NEW_PLACE_FILENAME, IArkivDoc::IDE);
}

void ArkivMainWindow::openStartPage(bool checked, QString optionalQueryParams /* = "" */)
{
	if(checked)
	{
		QString fileToOpen;

		const char* startPageUrl = RBX::ClientAppSettings::singleton().GetValueStartPageUrl();
		if (startPageUrl && startPageUrl[0] != '\0')
		{
			// Generate start page url from our recent files -- these files are put into the query string
			fileToOpen = QString::fromStdString(GetBaseURL()).append(startPageUrl).append("?");
			ArkivSettings settings;
			QStringList recentFiles = settings.value("rbxRecentFiles").toStringList();
			for(int i = 0; i < qMin(recentFiles.length(), (int)MAX_RECENT_FILES); i++)
			{
				QFileInfo info(recentFiles.at(i));
				fileToOpen.append("&filepath=" + QUrl::toPercentEncoding(info.filePath()) + "&filename=" + QUrl::toPercentEncoding(info.fileName()));	
			}				
		}
		else
			fileToOpen = QString::fromStdString(GetBaseURL() + "/My/Places.aspx");

		if (!optionalQueryParams.isEmpty())
			fileToOpen.append("&").append(optionalQueryParams);

		// make sure we are authenticated (if there's any authentication happening) before we open the browser
		AuthenticationHelper::Instance().waitForQtWebkitAuthentication();

		handleFileOpen(fileToOpen, IArkivDoc::BROWSER);
	}
	else
	{
		IArkivDoc* pDoc = ArkivDocManager::Instance().getOrCreateDoc(IArkivDoc::BROWSER);
        requestDocClose(*pDoc, false);
	}
}

void ArkivMainWindow::fileOpen()
{
    QString fileName;
	
	fileName = QFileDialog::getOpenFileName(
		this, 
		tr("Open Arkiv File"), 
		m_LastDirectory, 
		tr(ArkivIDEDoc::getOpenFileFilters()));

	if (fileName.isEmpty())
		return;

    setCurrentDirectory(fileName);
	handleFileOpen(fileName, IArkivDoc::IDE);
}

void ArkivMainWindow::fileOpenRecentSaves()
{
	QString fileName;
	
	fileName = QFileDialog::getOpenFileName(
		this, 
		tr("Open Arkiv File"), 
		AuthoringSettings::singleton().recentSavesDir.absolutePath(), 
		tr(ArkivIDEDoc::getOpenFileFilters()));

	if (fileName.isEmpty())
		return;

    setCurrentDirectory(fileName);
	handleFileOpen(fileName, IArkivDoc::IDE);
}

void ArkivMainWindow::fileClose()
{
    IArkivDoc* doc = ArkivDocManager::Instance().getCurrentDoc();
	if ( doc )
        requestDocClose(*doc);
}

bool ArkivMainWindow::verifyFilePermissions(const QString &fileName)
{
	bool retVal = false;

	if (!fileName.isEmpty())
	{
		QFileInfo fileInfo(fileName);
		if (fileInfo.exists() && !fileInfo.isWritable()) 
		{
			QtUtilities::RBXMessageBox msgBox;
			msgBox.setIcon(QMessageBox::Warning);
			msgBox.setText(fileName + "\nThis file is set to read-only.\nTry again with a different name");
			msgBox.setStandardButtons(QMessageBox::Ok);
			msgBox.setDefaultButton(QMessageBox::Ok);
			msgBox.exec();
		}
		else 
		{
			retVal = true;
		}
	}
	else /// In case of Empty File return it as True as the file is not present and new file should be created
	{
		retVal = true;
	}
	return retVal;
}

bool ArkivMainWindow::fileSave(IArkivDoc *pDoc)
{
	bool retVal = false;
	
	//if no document is provided then get the play document. 
	if (!pDoc)
		pDoc = ArkivDocManager::Instance().getPlayDoc();
	
    if (pDoc && pDoc->isModified())
    {
        if (verifyFilePermissions(pDoc->fileName()))
        {
            if ( pDoc->fileName().isEmpty() || !pDoc->save() )
                retVal = fileSaveAs(pDoc);
            else
                retVal = true;
        }
    }
	return retVal;
}

bool ArkivMainWindow::fileSaveAs(IArkivDoc *pDoc)
{
	bool retVal = false;
	
	//if no document is provided then get the play document
	if (!pDoc)
		pDoc = ArkivDocManager::Instance().getPlayDoc();
	
	if (pDoc)
	{
		QString fileName(pDoc->fileName());
		if ( fileName.isEmpty() &&
				boost::filesystem::portable_file_name(pDoc->displayName().toStdString()) )
			fileName = m_LastDirectory + "/" + pDoc->displayName();

		fileName = QFileDialog::getSaveFileName(this,tr("Save As"),fileName,pDoc->saveFileFilters());
			
		if( !fileName.isEmpty() && verifyFilePermissions(fileName) && pDoc->saveAs(fileName))
		{
            setCurrentDirectory(fileName);
            ArkivDocManager::Instance().setDocTitle(*pDoc,pDoc->displayName(),pDoc->titleTooltip(),pDoc->titleIcon());
            updateRecentFile(fileName);

            m_AutoSaveAccum = 0;
			retVal = true;
		}
	}

	return retVal;
}

bool ArkivMainWindow::filePublishedProjects()
{
	QString url = QString(RBX::ClientAppSettings::singleton().GetValuePublishedProjectsPageUrl());
	if (url.isEmpty())
		return false;

	if (!StudioUtilities::checkNetworkAndUserAuthentication())
		return false;
	
	WebDialog dlg(
        this, 
        url.prepend(ArkivSettings::getBaseURL()),
        NULL, 
		RBX::ClientAppSettings::singleton().GetValuePublishedProjectsPageWidth(), 
		RBX::ClientAppSettings::singleton().GetValuePublishedProjectsPageHeight() );
    dlg.setMinimumSize( FInt::StudioWebDialogMinimumWidth, FInt::StudioWebDialogMinimumHeight);
	dlg.exec();
	
	return true;
}

bool ArkivMainWindow::openRecentFile(const QString &fileName)
{
	if(!fileName.isEmpty())
    {
		QFileInfo fileInfo(fileName);
		if(!fileInfo.exists())
        {
            updateRecentFile(fileName);

            QtUtilities::RBXMessageBox msgBox;
			msgBox.setIcon(QMessageBox::Warning);
			msgBox.setText(fileName + "\nThis file doesn't exist.");
			msgBox.setStandardButtons(QMessageBox::Ok);
			msgBox.setDefaultButton(QMessageBox::Ok);
	        msgBox.exec();
            return false;
        }
    }

	return handleFileOpen(fileName, IArkivDoc::IDE);
}

bool ArkivMainWindow::openRecentFile()
{
	QAction *action = qobject_cast<QAction *>(sender());
	QString fileName = action->data().toString();
	if (action)
	{
		return openRecentFile(fileName);
	}
	else
		return false;
}

void ArkivMainWindow::publishGame()
{
	if (!StudioUtilities::checkNetworkAndUserAuthentication())
		return;

	QString initialUrl = QString("%1/IDE/publishgameas").arg(ArkivSettings::getBaseURL());

	if (!m_publishGameDialog) 
    {
		m_publishGameDialog = new WebDialog(this, initialUrl, NULL);
        m_publishGameDialog->setMinimumSize( FInt::StudioWebDialogMinimumWidth, FInt::StudioWebDialogMinimumHeight);
    }
	else
	{
		m_publishGameDialog->load(initialUrl);
	}

	m_publishGameDialog->show();
	m_publishGameDialog->raise();
	m_publishGameDialog->activateWindow();
}

void ArkivMainWindow::closePublishGameWindow()
{
	RBXASSERT(m_publishGameDialog);
	if (m_publishGameDialog)
	{
		m_publishGameDialog->close();
	}
}

void ArkivMainWindow::updateRecentFilesUI()
{
	if (isRibbonStyle())
	{
		RibbonPageSystemRecentFileList* pRecentFileList = findChild<RibbonPageSystemRecentFileList*>("recentFileList");
		if (pRecentFileList)
			pRecentFileList->updateRecentFileActions(getRecentFiles());
	}
	else
	{
		updateRecentFilesList(getRecentFiles());
	}
}

void ArkivMainWindow::updateRecentFilesList(const QStringList& files)
{
	int numRecentFiles = qMin(files.size(), (int)MAX_RECENT_FILES_SHOWN);

	for (int i = 0; i < numRecentFiles; ++i) 
    {
        QFileInfo fileInfo(files[i]);
        QString fullFilename = fileInfo.absoluteFilePath();
		QString filename = fullFilename;

        if ( filename.startsWith(m_LastDirectory) )
            filename = filename.right(filename.length() - 1 - m_LastDirectory.length());

		bool isTextModified = false;
		if ( filename.length() > MaxLengthFilenameMRU )
		{
			QFontMetrics fm = fontMetrics();
			filename = fm.elidedText(filename,Qt::ElideMiddle,MaxLengthFilenameMRU * fm.width('0'));
		    isTextModified = true;
		}

		recentOpenedFiles[i]->setText(QString("&%1 %2").arg(i + 1).arg(filename));

		if(isTextModified)
			recentOpenedFiles[i]->setToolTip(fullFilename);

		recentOpenedFiles[i]->setData(fullFilename);
		recentOpenedFiles[i]->setStatusTip(fullFilename);
		recentOpenedFiles[i]->setVisible(true);
	}

	for (int j = numRecentFiles; j < (int)MAX_RECENT_FILES_SHOWN; ++j)
		recentOpenedFiles[j]->setVisible(false);

	separator->setVisible(numRecentFiles > 0);
}

void ArkivMainWindow::updateInternalWidgetsState(QAction* pAction, bool enabledState,bool checkedState)
{
	if (isRibbonStyle())
		ArkivRibbonMainWindow::updateInternalWidgetsState(pAction, enabledState, checkedState);
}

#define COPYRIGHT_PREFIX 0xA9

void ArkivMainWindow::about()
{
	QString aboutMsg(tr("<div style=\"text-align: center\">"));
	aboutMsg.append(tr("<p style=\"font-weight: bold\">"));
    aboutMsg.append(tr("ARKIV Studio "));
	aboutMsg.append(tr("Version %1</p>"));

#if defined(_NOOPT) || defined(_DEBUG) 
    aboutMsg.append(tr("<br><hr><br><br>DEBUG ONLY<br><hr>"));

    QString build_type;

#ifdef _NOOPT
    build_type = "NoOpt";
#else
    build_type = "Debug";
#endif

    aboutMsg.append("Build Type: " + build_type);
    aboutMsg.append("<br>Path: ");

    const int threshold = 50;
    QString full_path = QCoreApplication::applicationFilePath();
    while ( !full_path.isEmpty() )
    {
        aboutMsg.append(full_path.left(threshold) + "<br>");
        if ( full_path.length() >= threshold )
        {
            full_path = full_path.right(full_path.length() - threshold);
            if ( !full_path.isEmpty() )
                aboutMsg.append("&nbsp;&nbsp;&nbsp;&nbsp;");
        }
        else
        {
            full_path = "";
        }
    }

    aboutMsg.append("Qt Version: ");
    aboutMsg.append(qVersion());

	// display command line argument
    aboutMsg.append("<br><br>");
    aboutMsg.append("Arguments:<br>");
    
    QStringList args = QApplication::arguments();
    for ( int i = 1 ; i < args.size() ; ++i )
        aboutMsg.append(QString::number(i) + ") '" + args[i] + "'<br>");

    aboutMsg.append("<hr><br>");
#endif

	aboutMsg = aboutMsg.arg(ArkivSettings::getVersionString());
    aboutMsg.append(tr("<p>ARKIV, \"Online Building Toy\", characters, logos, names, and all related indicia "));
	
	QString copyrightString;
	copyrightString.sprintf("are trademarks of ARKIV Corporation %c2014. ", COPYRIGHT_PREFIX);
							
    aboutMsg.append(copyrightString);
	aboutMsg.append(tr("US Patents 7,874,921. Patents pending.</p>"));
					   
	aboutMsg.append(tr("<p>Contact us at info@arkiv.com.</p></div>"));
	
	QMessageBox::about(this, tr("Welcome to ARKIV!"), aboutMsg);
}

void ArkivMainWindow::onlineHelp()
{
	QUrl helpUrl("http://wiki.arkiv.com/index.php/Studio", QUrl::TolerantMode);
	QDesktopServices::openUrl(helpUrl);
}

void ArkivMainWindow::shortcutHelp()
{
    if ( !m_pInputConfigDialog )
        m_pInputConfigDialog = new ArkivInputConfigDialog(*this);

    if ( m_pInputConfigDialog->isVisible() )
        m_pInputConfigDialog->hide();
    else
    {
        m_pInputConfigDialog->show();
        m_pInputConfigDialog->raise();
    }
}

void ArkivMainWindow::fastLogDump()
{
	RBX::StandardOut::singleton()->printf(RBX::MESSAGE_INFO, "Log Dumps");
#ifdef _WIN32
	mainLogManager.CreateFakeCrashDump();
#else
	CrashReporter::CreateLogDump();
#endif
}

void ArkivMainWindow::instanceDump()
{
}

void ArkivMainWindow::openPluginsFolder()
{	
	QString userPluginPath = ArkivPluginHost::userPluginPath();
	QDir pluginDir(userPluginPath);

	if (!pluginDir.exists())
		pluginDir.mkpath(userPluginPath);

	QDesktopServices::openUrl(QUrl::fromLocalFile(userPluginPath));
}

void ArkivMainWindow::managePlugins()
{
	if (!StudioUtilities::checkNetworkAndUserAuthentication())
		return;
	
	if (!m_managePluginsDoc)
	{
		m_managePluginsDoc.reset(new ArkivWebDoc(tr("Plugin Management"), "PluginManagement"));
		ArkivWebDoc* webDoc = dynamic_cast<ArkivWebDoc*>(
			ArkivDocManager::Instance().getOrCreateDoc(IArkivDoc::BROWSER));
		connect(webDoc->getWorkspace().get(), SIGNAL(PluginInstallComplete(bool, int)),
				m_managePluginsDoc.get(),       SLOT(          refreshPage()));
	}
	m_managePluginsDoc->open(this,
		QString("%1/studio/plugins/manage").arg(ArkivSettings::getBaseURL()));
	QWidget *widgetToAddInTab = m_managePluginsDoc->getViewer();
	if (widgetToAddInTab)
	{
        ArkivDocManager::Instance().configureDocWidget(*m_managePluginsDoc);
	}
}

ArkivWebDoc* ArkivMainWindow::getConfigureWebDoc()
{
	if (!m_configureGameDoc)
	{
		m_configureGameDoc.reset(new ArkivWebDoc(tr("Configure"), "GameEntityConfigure"));
        ArkivDocManager::Instance().getOrCreateDoc(IArkivDoc::BROWSER);
	}
	// The widget doesn't show up in the tabs unless open() has been called at least once.
    m_configureGameDoc->open(this, "");
	QWidget *widgetToAddInTab = m_configureGameDoc->getViewer();
	if (widgetToAddInTab)
	{
        ArkivDocManager::Instance().configureDocWidget(*m_configureGameDoc);
	}

	return m_configureGameDoc.get();
}

void ArkivMainWindow::closeConfigureWebDoc()
{
	if (m_configureGameDoc)
	{
		requestDocClose(m_configureGameDoc.get());
	}
}

void ArkivMainWindow::openObjectBrowser(bool checked)
{
	if ( checked )
    {
        handleFileOpen(QString(""), IArkivDoc::OBJECTBROWSER);
    }
    else
    {
		IArkivDoc* pDoc = ArkivDocManager::Instance().getOrCreateDoc(IArkivDoc::OBJECTBROWSER);
        requestDocClose(*pDoc);
	}
}

void ArkivMainWindow::openSettingsDialog()
{
	if ( !m_pSettingsDialog )
	    m_pSettingsDialog = new ArkivSettingsDialog(this);
	m_pSettingsDialog->exec();

    // perform any fixup if settings changed
    assignAccelerators();
}

void ArkivMainWindow::executeScriptFile()
{
	RBXASSERT(ArkivDocManager::Instance().getCurrentDoc());
	RBXASSERT(ArkivDocManager::Instance().getCurrentDoc() == ArkivDocManager::Instance().getPlayDoc());

	//check is there's no current document then create one
	if (!ArkivDocManager::Instance().getCurrentDoc())
		fileNew();

	//still no document? can't do anything!
	if (!ArkivDocManager::Instance().getCurrentDoc())
		return;

	//open the script file
    QString fileName;
	
	fileName = QFileDialog::getOpenFileName(
		this,
		tr("Open Script File"),
		AuthoringSettings::singleton().defaultScriptFileDir.absolutePath(),
		tr("Scripts (*.rbxs *.lua *.txt);;All Files (*.*)"));

	if (fileName.isEmpty())
		return;

    QFileInfo info(fileName);
	AuthoringSettings::singleton().defaultScriptFileDir = info.dir();

	QFile file(fileName);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
        return;

	//read file
	QTextStream inStream(&file);
	QString toExecute = inStream.readAll();
	
	if (!toExecute.isEmpty())
    {
		if (ArkivIDEDoc* ideDoc = ArkivDocManager::Instance().getPlayDoc())
			ideDoc->handleScriptCommand(toExecute);
    }
}

void ArkivMainWindow::onCustomToolButton(const QString& selectedItem)
{
	const QObject *pSender = sender();
	if (!pSender)
		return;

	//action to be handled by the relevant document
	if (!ArkivDocManager::Instance().getCurrentDoc())
		return;
	
	QString modifiedActionName(pSender->objectName());
	modifiedActionName.append("_"); 
    modifiedActionName.append(selectedItem);

	ArkivDocManager::Instance().getCurrentDoc()->handleAction(modifiedActionName);

	//update toolbar status
	UpdateUIManager::Instance().updateToolBars();
}

void ArkivMainWindow::onMenuActionHovered(QAction* action)
{
	if(!action)
		return;

    for (int i = 0; i < MAX_RECENT_FILES_SHOWN; ++i) 
    {
		if(action == recentOpenedFiles[i])
		{
			QString tip = action->toolTip();
			if(tip != action->text().remove(0,1))
				QToolTip::showText(QCursor::pos(), tip);
			else
				QToolTip::hideText();
			break;
		}		
	}	
}

void ArkivMainWindow::closeEvent(QCloseEvent* evt)
{
    RBX::Log::current()->writeEntry(RBX::Log::Information,"ArkivMainWindow::closeEvent");

    if ( !m_IsInitialized || UpdateUIManager::Instance().isBusy() )
    {
        evt->ignore();
        return;
    }

	if (FFlag::StudioSettingsGAEnabled)
		AuthoringSettings::singleton().setDoSettingsChangedGAEvents(false);

    Studio::Intellesense::singleton().deactivate();

	// cleanup Wiki search lookup table
	ScriptTextEditor::cleanupWikiLookup();


	// first save and close out the play doc if we're in build mode
    if ( m_BuildMode == BM_BASIC )
    {
        IArkivDoc* playDoc = ArkivDocManager::Instance().getPlayDoc();       
        if ( playDoc && !requestDocClose(*playDoc) )
        {
            evt->ignore();
			return;
        }
    }

    // save and close the rest of the docs
    if ( !ArkivDocManager::Instance().requestCloseAllDocs() )
    {
        evt->ignore();
        return;
    }
	
	//before close the application, save its states.
	saveApplicationStates();
	// remove event filter
	if (FFlag::StudioInSyncWebKitAuthentication)
		qApp->removeEventFilter(&AuthenticationHelper::Instance());

    hide();

	studioAnalytics.savePersistentVariables();
	studioAnalytics.reportPersistentVariables();

    QMainWindow::closeEvent(evt);
}

/**
 * Close all documents and save locally.
 */
void ArkivMainWindow::saveAndClose()
{
    if ( ArkivDocManager::Instance().requestCloseAndSaveAllDocs() )
        close();
}

/**
 * Closes all documents but doesn't save.
 */
void ArkivMainWindow::forceClose()
{
    ArkivDocManager::Instance().closeAllDocs();
    close();
}

void ArkivMainWindow::contextMenuEvent(QContextMenuEvent* evt)
{
	// don't show the main window context menu if in basic mode
    if ( m_BuildMode != BM_BASIC )
        QMainWindow::contextMenuEvent(evt);
}

void ArkivMainWindow::dragEnterEvent(QDragEnterEvent *evt)
{
	const QMimeData *pMimeData = evt->mimeData();
	if (!pMimeData || !pMimeData->hasUrls()) 
		return QMainWindow::dragEnterEvent(evt);

	bool isValidFileList = false;

	QList<QUrl> urlList = pMimeData->urls();
	for (int i = 0; i < urlList.size() && i < 6; ++i) 
	{
		QString filePath = urlList.at(i).toLocalFile();
		isValidFileList =
            !filePath.isEmpty() &&
                (filePath.endsWith(".rbxl", Qt::CaseInsensitive) ||
                 filePath.endsWith(".rbxlx", Qt::CaseInsensitive) ||
                 filePath.endsWith(".rbxm", Qt::CaseInsensitive) ||
                 filePath.endsWith(".rbxmx", Qt::CaseInsensitive));

		if (!isValidFileList)
			break;
	}

	if (!isValidFileList)
		return QMainWindow::dragEnterEvent(evt);
	
	evt->acceptProposedAction();
}

void ArkivMainWindow::dragMoveEvent(QDragMoveEvent *evt)
{
	evt->acceptProposedAction();
}

void ArkivMainWindow::dropEvent(QDropEvent *evt)
{
	const QMimeData *pMimeData = evt->mimeData();

	if (!pMimeData || !pMimeData->hasUrls())
		return QMainWindow::dropEvent(evt);
	
	QList<QUrl> urlList = pMimeData->urls();
	for (int i = 0; i < urlList.size() && i < 6; ++i) 
	{
		QString fileName = urlList.at(i).toLocalFile();
		if (!fileName.isEmpty())
		{
			if(fileName.endsWith(".rbxl", Qt::CaseInsensitive) || fileName.endsWith(".rbxlx", Qt::CaseInsensitive))
				handleFileOpen(fileName, IArkivDoc::IDE);
			else 
			{
				if(ArkivDocManager::Instance().getCurrentDoc())
					ArkivDocManager::Instance().getCurrentDoc()->handleDrop(fileName);
			}
		}
	}

	evt->acceptProposedAction();
}

void ArkivMainWindow::dragLeaveEvent(QDragLeaveEvent *evt)
{
	evt->accept();
}

void ArkivMainWindow::initializeUI()
{

    // Apply the global Arkiv Studio style sheet to the entire application.
    // ArkivStudio.css is where we can tweak and tune the look-and-feel
    // of the Studio UI.  All style overrides that are application-wide
    // should be put there.
    setStyleSheet(QtUtilities::getResourceFileText(":/ArkivStudio.css"));
    
    // force height so we don't get any resizing when adding and removing controls to the status bar
    statusBar()->setFixedHeight(32);
	 // Apply the global Arkiv Studio style sheet to the entire application.

	QString css;

    if ( isRibbonStyle() )
	{
        //css = QtUtilities::getResourceFileText(":/ArkivStudioRibbon.css");
	}
	else
	{
        //css = QtUtilities::getResourceFileText(":/ArkivStudio.css");

		//TODO: Move all these customizations to .ui file
		menuTools->insertAction(openPluginsFolderAction, screenShotAction);
#ifdef _WIN32
		menuTools->insertAction(openPluginsFolderAction, toggleVideoRecordAction);
#endif

		menuTools->insertSeparator(openPluginsFolderAction);

		advToolsToolBar->insertAction(advanceJointCreationManualAction, toggleCollisionCheckAction);
		advToolsToolBar->insertSeparator(advanceJointCreationManualAction);

		if (RBX::MouseCommand::isAdvArrowToolEnabled())
			removeToolBar(oldToolsToolBar);

		// Added so that we can dump Crash for Breakpad as needed
		// To enable crashing add following to AppSettings.xml
		//   <CrashMenu>1</CrashMenu>
		if(ArkivSettings::showCrashMenu())
		{
			QAction *crashAction = new QAction("&Crash", this);
			connect(crashAction, SIGNAL(triggered()), this, SLOT(causeCrash()));
			QMenu* debugMenu = menuBar()->addMenu("&Debug");
			debugMenu->addAction(crashAction);
		}

		advToolsToolBar->insertAction(glueSurfaceAction, smoothNoOutlinesAction);
	}

	//setStyleSheet(css);
    Studio::Intellesense::singleton().setStyleSheet(css);

    //support drag drop
    setAcceptDrops(true);

	// fix focus issues in Mac
	setFocusPolicy(Qt::StrongFocus);
    
    //default is max screen
    setWindowState(Qt::WindowMaximized);
    
    QTimer* minute_timer = new QTimer(this);
    connect(minute_timer,SIGNAL(timeout()),this,SLOT(onMinuteTimer()));
    minute_timer->start(60 * 1000);
    
    m_AnalyticTrackedConnection = RBX::ArkivGoogleAnalytics::analyticTrackedSignal().connect(boost::bind(&ArkivMainWindow::onAnalyticTracked, this));
    
    qApp->installEventFilter(this);

	// Initialize the doc manager
	ArkivDocManager::Instance().initialize(*this);
}

void ArkivMainWindow::setupSlots()
{
	//file menu
	connect(menuFile, SIGNAL(hovered(QAction*)), this, SLOT(onMenuActionHovered(QAction*)));
	connect(fileNewAction,    SIGNAL(triggered()), this, SLOT(fileNew()));
	connect(fileOpenAction,   SIGNAL(triggered()), this, SLOT(fileOpen()));
	connect(fileCloseAction,  SIGNAL(triggered()), this, SLOT(fileClose()));
	connect(fileSaveAction,   SIGNAL(triggered()), this, SLOT(fileSave()));
	connect(fileSaveAsAction, SIGNAL(triggered()), this, SLOT(fileSaveAs()));
	connect(fileExitAction,   SIGNAL(triggered()), this, SLOT(close()));
	connect(publishGameAction, SIGNAL(triggered()), this, SLOT(publishGame()));
	publishGameAction->setEnabled(false);

	connect(fileOpenRecentSavesAction, SIGNAL(triggered()), this, SLOT(fileOpenRecentSaves()));
    
    // create global shortcuts that should always work even if actions are disabled

    QShortcut* shortcut = new QShortcut(fileExitAction->shortcut(),this);
    connect(shortcut,SIGNAL(activated()),this,SLOT(close()));

    shortcut = new QShortcut(toggleBuildModeAction->shortcut(),this);
    connect(shortcut,SIGNAL(activated()),this,SLOT(toggleBuildMode()));
	
    addAction(zoomExtentsAction);
    addAction(toggleLocalSpaceAction);
    addAction(quickInsertAction);
	addAction(explorerFilterAction);

	pairRbxDeviceAction->setEnabled(true);
	playRbxDeviceAction->setEnabled(true);
	
	if (RBX::ClientAppSettings::singleton().GetValuePublishedProjectsPageUrl() && RBX::ClientAppSettings::singleton().GetValuePublishedProjectsPageUrl()[0] != '\0')
	{			
		connect(filePublishedProjectsAction, SIGNAL(triggered()), this, SLOT(filePublishedProjects()));
	}
	else
	{
		filePublishedProjectsAction->setEnabled(false);
		filePublishedProjectsAction->setVisible(false);
	}

	//set up recent open files slots
    for (int i = 0; i < MAX_RECENT_FILES_SHOWN; ++i) 
    {
		if (!isRibbonStyle())
		{
			recentOpenedFiles[i] = new QAction(this);
			menuFile->insertAction(fileExitAction, recentOpenedFiles[i]);
			recentOpenedFiles[i]->setVisible(false);
			connect(recentOpenedFiles[i], SIGNAL(triggered()), this, SLOT(openRecentFile()));
		}
		else
		{
			recentOpenedFiles[i] = NULL;
		}
	}

	QMenu* pMenu = isRibbonStyle() ? findChild<QMenu*>("switchWindowsMenu") : menuWindow;

	//for window menu open tabs slots
    for ( int i = 0 ; i < MAX_DOC_WINDOWS ; ++i ) 
    {
		currentOpenedfiles[i] = new QAction(this);

		if (pMenu)
			pMenu->addAction(currentOpenedfiles[i]);

		currentOpenedfiles[i]->setVisible(false);
        connect(
            currentOpenedfiles[i],SIGNAL(triggered()), 
            &ArkivDocManager::Instance(),SLOT(onActivateWindow()) );
		currentOpenedfiles[i]->setCheckable(true);
	}
		
	separator = menuFile->insertSeparator(fileExitAction);
	
	//reset view
	connect(resetViewAction, SIGNAL(triggered()), this, SLOT(loadDefaultApplicationState()));
	
	//execute script
	connect(executeScriptAction, SIGNAL(triggered()), this, SLOT(executeScriptFile()));

	// Tools->Settings....
	connect(settingsAction, SIGNAL(triggered()), this, SLOT(openSettingsDialog()));

	// Tools Menu
	instanceDumpAction->setVisible(false);

	connect(openPluginsFolderAction, SIGNAL(triggered()), this, SLOT(openPluginsFolder()));
	connect(managePluginsAction, SIGNAL(triggered()), this, SLOT(managePlugins()));	
	
	// Help Menu
	connect(aboutArkivAction, SIGNAL(triggered()), this, SLOT(about()));
	connect(onlineHelpAction, SIGNAL(triggered()), this, SLOT(onlineHelp()));
    connect(shortcutHelpAction, SIGNAL(triggered()), this, SLOT(shortcutHelp()));
    connect(objectBrowserAction, SIGNAL(toggled(bool)), this, SLOT(openObjectBrowser(bool)));
	connect(fastLogDumpAction, SIGNAL(triggered()), this, SLOT(fastLogDump()));

	connect(viewCommandBarAction, SIGNAL(toggled(bool)), commandToolBar, SLOT(setVisible(bool)));

    //Insert Object
	if (FFlag::StudioSeparateActionByActivationMethod)
    	connect(quickInsertAction, SIGNAL(triggered()), &UpdateUIManager::Instance(), SLOT(commonSlot()));
	else
		connect(quickInsertAction, SIGNAL(triggered()), &UpdateUIManager::Instance(), SLOT(onQuickInsertFocus()));
    
	connect(explorerFilterAction, SIGNAL(triggered()), &UpdateUIManager::Instance(), SLOT(filterExplorer()));

	//Cleaup players and servers
	connect(cleanupServersAndPlayersAction, SIGNAL(triggered()), this, SLOT(cleanupPlayersAndServers()));
    
	// Insert Service
	if (!m_pInsertServiceDlg)
		m_pInsertServiceDlg = new InsertServiceDialog(this);
	connect(insertServiceAction, SIGNAL(triggered()), m_pInsertServiceDlg, SLOT(show()));

	connect(findInScriptsAction, SIGNAL(triggered()), this, SLOT(showFindAllDialog()));

	emulateDeviceAction->setEnabled(true);
	manageEmulationDeviceAction->setEnabled(true);
	
	viewCommandBarAction->setEnabled(true);
	testCustomStatsAction->setEnabled(FFlag::StudioCustomStatsEnabled);

    QAction* commonActions[] =
    {
        rotateSelectionAction, tiltSelectionAction, groupSelectionAction, ungroupSelectionAction,
		selectChildrenAction, moveUpBrickAction, moveDownBrickAction, deleteSelectedAction, 
		selectAllAction, lockAction, glueSurfaceAction,

        // stats menu
        testStatsAction, testRenderStatsAction, testPhysicsStatsAction, testNetworkStatsAction, 
        testSummaryStatsAction, testCustomStatsAction, testClearStatsAction,

		smoothSurfaceAction, weldSurfaceAction, studsAction, inletAction, universalsAction, 
		hingeAction, anchorAction, motorRightAction, smoothNoOutlinesAction,
		dropperAction, simulationRunAction, simulationPlayAction, simulationStopAction, simulationResetAction, 
        zoomInAction, zoomOutAction, tiltUpAction, tiltDownAction,
		zoomExtentsAction, panRightAction, panLeftAction, advanceJointCreationManualAction, 
		gridToOneAction,gridToOneFifthAction, gridToOffAction, 
        actionFillColor, actionMaterial, advTranslateAction, advRotateAction, resizeAction,
		cutAction, copyAction, pasteAction, duplicateSelectionAction, 
		pasteIntoAction, undoAction, redoAction, playSoloAction, startServerAction, 
		startPlayerAction, pairRbxDeviceAction, insertModelAction, insertIntoFileAction, 
		selectionSaveToFileAction, publishToArkivAction, publishToArkivAsAction, publishGameAction, publishSelectionToArkivAction, 
		saveToArkivAction, publishAsPluginAction, createNewLinkedSourceAction, advArrowToolAction, toggleAxisWidgetAction, toggle3DGridAction,
		toggleVideoRecordAction, viewDiagnosticsAction, viewTaskSchedulerAction, viewToolboxAction,
		viewBasicObjectsAction, viewScriptPerformanceAction, viewObjectExplorerAction,
		viewPropertiesAction, viewOutputWindowAction, viewContextualHelpAction, viewFindResultsWindowAction, viewScriptAnalysisAction,
        gameExplorerAction, toggleCollisionCheckAction,
		renameObjectAction, unlockAllAction, openPluginsFolderAction, screenShotAction, toggleLocalSpaceAction,
        quickInsertAction, explorerFilterAction, exportSelectionAction, exportPlaceAction,
        unionSelectionAction, negateSelectionAction, separateSelectionAction, viewTutorialsAction, viewTeamCreateAction,

        // script actions
        goToScriptErrorAction, commentSelectionAction, uncommentSelectionAction, toggleCommentAction,
        expandAllFoldsAction, collapseAllFoldsAction, findAction, replaceAction, findNextAction, goToLineAction, 
        findPreviousAction, resetScriptZoomAction, reloadScriptAction, neverBreakOnScriptErrorsAction, breakOnAllScriptErrorsAction,
		breakOnUnhandledScriptErrorsAction, manageEmulationDeviceAction, 

		gridSizeToTwoAction, gridSizeToFourAction, gridSizeToSixteenAction, launchHelpForSelectionAction, downloadPlaceCopyAction
	};
	
	viewTutorialsAction->setVisible(FFlag::StudioShowTutorialsByDefault);
	downloadPlaceCopyAction->setVisible(false);

	int numActions = sizeof(commonActions) / sizeof(QAction*);
    for ( int i = 0; i < numActions; ++i )
    {
        RBX::BaldPtr<QAction> action = commonActions[i];
		if (!FFlag::StudioSeparateActionByActivationMethod)
       		connect(action,SIGNAL(triggered(bool)),this,SLOT(commonSlot(bool)));

        QList<QKeySequence> shortcuts = action->shortcuts();
        if ( !shortcuts.isEmpty() )
        {
			// add the shortcuts to the tooltip
            QtUtilities::setActionShortcuts(*action,shortcuts);
        }
        else
        {
            // set status tip
            if ( action->statusTip().isEmpty() )
                action->setStatusTip(action->toolTip());
        }
    }
	
	connect(&Arkiv::Instance(),SIGNAL(marshallAppEvent(void*,bool)), this,SLOT(processAppEvent(void*)));
	connect(actionStartPage, SIGNAL(toggled(bool)), this, SLOT(openStartPage(bool)));
	connect(actionFullScreen, SIGNAL(toggled(bool)), this, SLOT(toggleFullScreen(bool)));

	updateShortcutSet();
}

void ArkivMainWindow::updateShortcutSet()
{
	if (FFlag::DontSwallowInputForStudioShortcuts)
	{
		shortcutSet.clear();
		QObjectList objects = UpdateUIManager::Instance().getMainWindow().children();
		for (QObjectList::iterator iter = objects.begin(); iter != objects.end() ; ++iter )
		{
			RBX::BaldPtr<QAction> action = dynamic_cast<QAction*>(*iter);
			if (action && !action->text().isEmpty() &&!action->text().startsWith("&"))
			{
				shortcutSet.insert(action->shortcut().toString());
			}
		}
	}
}

bool ArkivMainWindow::isShortcut(const QKeySequence& keySequence)
{
	return (shortcutSet.find(keySequence.toString()) != shortcutSet.end());
}

/**
 * Configure the shortcuts for the actions that are platform specific.
 *  Common actions have different shortcuts on different platforms.  This
 *  function will reconfigure the common action shortcuts for the platform.
 */
void ArkivMainWindow::assignAccelerators()
{
	// file menu
    QtUtilities::setActionShortcuts(*fileNewAction,QKeySequence::keyBindings(QKeySequence::New));
	QtUtilities::setActionShortcuts(*fileOpenAction,QKeySequence::keyBindings(QKeySequence::Open));
	QtUtilities::setActionShortcuts(*fileSaveAction,QKeySequence::keyBindings(QKeySequence::Save));
	QtUtilities::setActionShortcuts(*fileSaveAsAction,QKeySequence::keyBindings(QKeySequence::SaveAs));
	QtUtilities::setActionShortcuts(*fileCloseAction,QKeySequence::keyBindings(QKeySequence::Close));
	QtUtilities::setActionShortcuts(*fileExitAction,QKeySequence::keyBindings(QKeySequence::Quit));

	// edit menu
	QtUtilities::setActionShortcuts(*copyAction,QKeySequence::keyBindings(QKeySequence::Copy));
	QtUtilities::setActionShortcuts(*cutAction,QKeySequence::keyBindings(QKeySequence::Cut));
	QtUtilities::setActionShortcuts(*pasteAction,QKeySequence::keyBindings(QKeySequence::Paste));
	QtUtilities::setActionShortcuts(*redoAction,QKeySequence::keyBindings(QKeySequence::Redo));
	QtUtilities::setActionShortcuts(*undoAction,QKeySequence::keyBindings(QKeySequence::Undo));
	QtUtilities::setActionShortcuts(*selectAllAction,QKeySequence::keyBindings(QKeySequence::SelectAll));

    // set up delete action
	QList<QKeySequence> shortcuts = QKeySequence::keyBindings(QKeySequence::Delete);
    shortcuts.append(QKeySequence(Qt::Key_Backspace));
    QtUtilities::setActionShortcuts(*deleteSelectedAction,shortcuts);
    
	// script menu
	QtUtilities::setActionShortcuts(*findAction,QKeySequence::keyBindings(QKeySequence::Find));
    QtUtilities::setActionShortcuts(*replaceAction,QKeySequence::keyBindings(QKeySequence::Replace));

    shortcuts.clear();
    shortcuts.append(QKeySequence("F3"));
	QtUtilities::setActionShortcuts(*findNextAction,shortcuts);
    
    shortcuts.clear();
    shortcuts.append(QKeySequence("Shift+F3"));
    QtUtilities::setActionShortcuts(*findPreviousAction,shortcuts);
	
    // tools menu
    QtUtilities::setActionShortcuts(*settingsAction,QKeySequence::keyBindings(QKeySequence::Preferences));

	// help menu
    shortcuts.clear();
    shortcuts.append(QKeySequence("F1"));
	QtUtilities::setActionShortcuts(*onlineHelpAction, shortcuts);

    // camera toolbar
    QtUtilities::setActionShortcuts(*zoomInAction, QList<QKeySequence>() << QKeySequence(QKeySequence::ZoomIn) << QKeySequence("Ctrl+="));
    QtUtilities::setActionShortcuts(*zoomOutAction, QList<QKeySequence>() << QKeySequence(QKeySequence::ZoomOut) << QKeySequence("Ctrl+_"));

    shortcuts.clear();
#ifndef Q_WS_MAC
	// TODO: remove shortcut collision for debugger action - stepinto
	QtUtilities::setActionShortcuts(*stepIntoAction,shortcuts);
    // F11 works differently on Mac
    shortcuts.append(QKeySequence("F11"));
#endif
    QtUtilities::setActionShortcuts(*actionFullScreen,shortcuts);

	if (isRibbonStyle())
	{
		// remove shortcut set for startServerAction
		shortcuts.clear();
		QtUtilities::setActionShortcuts(*startServerAction,shortcuts);

		// add shortcut F7 for startServerAndPlayersAction
		QAction* pAction = findChild<QAction*>("startServerAndPlayersAction");
		if (pAction)
		{
			shortcuts.append(QKeySequence("F7"));
			QtUtilities::setActionShortcuts(*pAction,shortcuts);
		}
	}
}

void ArkivMainWindow::showInsertServiceDialog()
{
	if (!m_pInsertServiceDlg)
		m_pInsertServiceDlg = new InsertServiceDialog(this);
	
	if(ArkivDocManager::Instance().getCurrentDoc())
		ArkivDocManager::Instance().getCurrentDoc()->handleAction("actionUpdateInsertServiceDialog");
	
	m_pInsertServiceDlg->setVisible(true);
}

void ArkivMainWindow::showFindAllDialog()
{
	FindReplaceProvider::instance().getFindAllDialog()->show();
	FindReplaceProvider::instance().getFindAllDialog()->activateWindow();
	FindReplaceProvider::instance().getFindAllDialog()->setFocus();
}

void ArkivMainWindow::updateEmbeddedFindPosition()
{
	if (IArkivDoc* doc = ArkivDocManager::Instance().getCurrentDoc())
	{
		if (ArkivScriptDoc* scriptDoc = dynamic_cast<ArkivScriptDoc*>(doc))
		{
			if (ScriptTextEditor* textEditor = scriptDoc->getTextEditor())
			{
				textEditor->updateEmbeddedFindPosition();
			}
		}
	}
}

void ArkivMainWindow::setupCommandToolBar()
{
    m_pScriptComboBox = new ScriptComboBox(commandToolBar);
    commandToolBar->setAllowedAreas(Qt::TopToolBarArea | Qt::BottomToolBarArea);
    commandToolBar->addWidget(m_pScriptComboBox);

    connect(
        commandToolBar,SIGNAL(topLevelChanged(bool)),
        this,SLOT(onCommandToolBarTopLevelChanged(bool)) );
}

void ArkivMainWindow::sendCounterEvent(std::string counterName, bool fireImmediately)
{
	if (!RBX::ClientAppSettings::singleton().GetValueCaptureQTStudioCountersEnabled())
		return;

#ifdef _WIN32
	// Can't initialize in global init so must do lazy init
	static boost::scoped_ptr<CountersClient> m_pCountersClient;

	if (!m_pCountersClient)
		m_pCountersClient.reset(new CountersClient(GetBaseURL().c_str(), "76E5A40C-3AE1-4028-9F10-7C62520BD94F", NULL));

	// TODO - change project settings to not have wchar as a native type.  Qt can't do wide string operations.
	std::wstring wstringCounterName = convert_s2w(counterName);
	m_pCountersClient->registerEvent(wstringCounterName, fireImmediately);
#endif
}

void ArkivMainWindow::setupCounterSender()
{
#ifdef _WIN32
	int interval = RBX::ClientAppSettings::singleton().GetValueCaptureSlowCountersIntervalInSeconds();
	m_pCounterSenderTimer = new QTimer(this);
	connect(m_pCounterSenderTimer, SIGNAL(timeout()), this, SLOT(sendOffCounters()));
	m_pCounterSenderTimer->start(interval * 1000);
#endif
}

void ArkivMainWindow::sendOffCounters()
{
#ifdef _WIN32
	boost::scoped_ptr<CountersClient> countersClient;

	if (!countersClient)
		countersClient.reset(new CountersClient(GetBaseURL().c_str(), "76E5A40C-3AE1-4028-9F10-7C62520BD94F", NULL));

	countersClient->reportEvents();
#endif
}

void ArkivMainWindow::logIntervalCounter()
{
	int interval = RBX::ClientAppSettings::singleton().GetValueCaptureCountersIntervalInMinutes();

	sendCounterEvent(QString("QTStudio_%1MinCounter").arg(interval).toStdString(), false);
}

void ArkivMainWindow::handleFileOpenSendCounter(const QString& fileName)
{
	// This person is a builder, set up a timer that starts recording every minute they're using our app
	if (!m_pMinutesPlayedTimer && RBX::ClientAppSettings::singleton().GetValueCaptureQTStudioCountersEnabled())
	{
		// Record counters every XX minutes (based on config)
		int interval = RBX::ClientAppSettings::singleton().GetValueCaptureCountersIntervalInMinutes();
		m_pMinutesPlayedTimer = new QTimer(this);
		connect(m_pMinutesPlayedTimer, SIGNAL(timeout()), this, SLOT(logIntervalCounter()));
		m_pMinutesPlayedTimer->start(interval * 60 * 1000);
	} 
	sendCounterEvent(fileName.isEmpty() ? "QTStudio_FileNew" : "QTStudio_FileOpen", false);
}
	
void ArkivMainWindow::checkInternetConnectionSendCounter(RBX::Http& arkivRequest, RBX::Http& externalRequest)
{
	bool arkivAccessible;
	std::string result;
	ArkivSettings settings;

	int unconnectedRuns = settings.value("appNoInternet", 0).toInt();

	try
	{
		arkivRequest.get(result);
		arkivAccessible = true;
	}
	catch(...)
	{
		arkivAccessible = false;
	}

	if (arkivAccessible)
	{
		if (unconnectedRuns)
			RBX::ArkivGoogleAnalytics::trackEvent(GA_CATEGORY_ERROR, "StudioInternetReconnection", "none", unconnectedRuns);
		
		RBX::ArkivGoogleAnalytics::trackEvent(GA_CATEGORY_ERROR, "StudioInternetConnection");

		settings.setValue("appNoInternet", 0);
	}
	else
	{
		bool googleAccessible;
		try
		{
			externalRequest.get(result, true);
			googleAccessible = true;
		}
		catch(...)
		{
			googleAccessible = false;
		}

		if (googleAccessible)
			RBX::ArkivGoogleAnalytics::trackEvent(GA_CATEGORY_ERROR, "ArkivDomainBlocked");
		else
			settings.setValue("appNoInternet", unconnectedRuns + 1);
	}
	
}

bool ArkivMainWindow::handleFileOpen(const QString &fileName, IArkivDoc::RBXDocType type, const QString &script)
{
    RBX::Log::current()->writeEntry(RBX::Log::Information, RBX::format("ArkivMainWindow::handleFileOpen %s", script.toStdString().c_str()).c_str());

	QString fileToOpen = fileName;

	if (type == IArkivDoc::IDE)
	{
		// we aren't specifying a file to open or a script to open, we aren't opening anything
		if(fileName.isEmpty() && script.isEmpty())
			return false;

        if (fileName == NEW_PLACE_FILENAME)
        {
            fileToOpen = "";
        }

		// Gross, if it's a build button click, add the avatar (and guis)
		StudioUtilities::setAvatarMode(false);
       
		if (StudioUtilities::containsVisitScript(script) ||
			StudioUtilities::containsJoinScript(script))
			StudioUtilities::setAvatarMode(true);

		handleFileOpenSendCounter(fileToOpen);
	
		// We already have an IDE doc open, launch a new version of Studio (SDI)
		IArkivDoc* currentPlayDoc = ArkivDocManager::Instance().getPlayDoc();
		if (currentPlayDoc)
		{
			// If we're opening a branch new place in our new process, send over the new place file name so it can differentiate
			QString fileNameToOpen = fileName.isEmpty() ? NEW_PLACE_FILENAME : fileName;
			ArkivApplicationManager::instance().createNewStudioInstance(script, fileNameToOpen);
			return true;
		}
	}

	IArkivDoc* newDoc = ArkivDocManager::Instance().getOrCreateDoc(type);

    if ( type == IArkivDoc::IDE )
    {
        // static cast ok because we know we made a IDEDoc due to type
        // only ideDoc needs a script, set it here before we open file
        ArkivIDEDoc* ideDoc = static_cast<ArkivIDEDoc*>(newDoc);
        ideDoc->setInitializationScript(script);

        m_AutoSaveAccum = 0;
    }
        
    if (!newDoc->open(this, fileToOpen))
    {
        QString text = tr("Error in opening file - %1").arg(fileToOpen);
        if (RBX::StandardOut::singleton() && (!fileToOpen.isEmpty()) && type == IArkivDoc::IDE)
            RBX::StandardOut::singleton()->print(RBX::MESSAGE_ERROR,qPrintable(text));

        requestDocClose(*newDoc);
        
        if ( type == IArkivDoc::IDE )
            QMessageBox::critical(this,"Open File Failure",text);
        return false;
    }
    else
    {
        if (RBX::StandardOut::singleton() && (!fileToOpen.isEmpty()) && type == IArkivDoc::IDE)
            RBX::StandardOut::singleton()->printf(RBX::MESSAGE_INFO, "Successfully opened file - %s", qPrintable(fileToOpen));
    }

    if ( fileToOpen.isEmpty() && type == IArkivDoc::IDE && script.isEmpty())
    {
		ArkivIDEDoc* idedoc = static_cast<ArkivIDEDoc*>(newDoc);
		idedoc->initializeNewPlace();
    }


	QWidget *widgetToAddInTab = newDoc->getViewer();
	if (widgetToAddInTab)
	{
        ArkivDocManager::Instance().configureDocWidget(*newDoc);

        // update build mode with new doc information
        //saveApplicationStates(); // save state in case update reloads it
        UpdateUIManager::Instance().updateBuildMode();
	}

    if ( type == IArkivDoc::IDE && !fileToOpen.isEmpty() )
        updateRecentFile(fileToOpen);

    if (FFlag::ReportBuildVSEditMode)
    {
        RBX::ArkivGoogleAnalytics::trackEvent(GA_CATEGORY_STUDIO, "EditMode", script.contains("visit.ashx") ? "Build" : "Edit");
    }

	return true;
}

//for making the position of toolbar identical to old studio.
void ArkivMainWindow::setToolbarPosition()
{
	insertToolBar(runToolBar, advToolsToolBar);
	
	if (RBX::MouseCommand::isAdvArrowToolEnabled())
	{
		insertToolBar(advToolsToolBar, runToolBar);
	}
    else
	{
		insertToolBar(advToolsToolBar, oldToolsToolBar);
		insertToolBar(oldToolsToolBar, runToolBar);
	}

	insertToolBar(runToolBar, editCameraToolBar);
	insertToolBar(editCameraToolBar, viewToolsToolBar);
}

QAction* ArkivMainWindow::getActionByName(const QString& actionName)
{
	QList<QAction*> actionList = actions();
	for (QList<QAction*>::const_iterator iter = actionList.begin(); iter != actionList.end(); ++iter)
		if ((*iter)->objectName() == actionName)
			return *iter;

	return NULL;
}

void ArkivMainWindow::saveDefaultApplicationState()
{
	ArkivSettings settings;

	//save all the positions and sizes for all dockWidgets and toolbars.
	settings.setValue("default_window_state", saveState());
	settings.setValue("default_geometry_state", saveGeometry());
}

void ArkivMainWindow::saveApplicationStates()
{
    // don't save anything in basic mode
    if ( m_BuildMode == BM_BASIC )
        return;

    if ( !isVisible() )
        return;

	UpdateUIManager::Instance().saveDocksGeometry();

	ArkivSettings settings;
	// Clear legacy values
	settings.remove("geometry");
	settings.remove("windowState");
	
	//save all the positions and sizes for all dockWidgets and toolbars.	
	settings.setValue(sGeometryKey, saveGeometry());
	settings.setValue(sWindowStateKey, saveState());
	
	// Save command history from output window
	settings.setValue("rbxCommandHistory", m_pScriptComboBox->commandHistory());

	//TODO: Move this to ArkivRibbonMainWindow.cpp
	if (isRibbonStyle())
		ArkivQuickAccessConfig::singleton().saveQuickAccessConfig();
}

void ArkivMainWindow::loadDefaultApplicationState()
{
	ArkivSettings settings;
	restoreState(settings.value("default_window_state").toByteArray());
	restoreGeometry(settings.value("default_geometry_state").toByteArray());

	// since players dockwidget and chat dockwidget gets created only after saving application default state so it doesn't get restored
	QDockWidget* playersDockWidget = findChild<QDockWidget*>("playersDockWidget");
	if (playersDockWidget)
		playersDockWidget->setVisible(false);
	QDockWidget* chatDockWidget = findChild<QDockWidget*>("chatDockWidget");
	if (chatDockWidget)
		chatDockWidget->setVisible(false);

	UpdateUIManager::Instance().setDockVisibility(eDW_OBJECT_EXPLORER, true);

	saveApplicationStates();
}

void ArkivMainWindow::loadApplicationStates()
{
	if (isRibbonStyle()) // Ribbon mode saves to its own settings
	{
		sGeometryKey = sGeometryKey.append("_ribbon");
		sWindowStateKey = sWindowStateKey.append("_ribbon");
	}

	//load all the positions and sizes for all dockWidgets and toolbars from memory.
	ArkivSettings settings;
	restoreState(settings.value(sWindowStateKey).toByteArray());
	restoreGeometry(settings.value(sGeometryKey).toByteArray());

    m_pScriptComboBox->setCommandHistory(settings.value("rbxCommandHistory").toStringList());
	
	UpdateUIManager::Instance().loadDocksGeometry();

    setCurrentDirectory(settings.value("rbxl_last_directory").toString());
}

/**
 * Update the window title to show the current doc name.
 *  If a doc is not selected, show the default.
 *  
 * @see getDialogTitle
 */
void ArkivMainWindow::updateWindowTitle()
{
    IArkivDoc* pDoc = ArkivDocManager::Instance().getCurrentDoc();

	// if no document or we're in basic build mode just use the simple title
    if ( !pDoc || m_BuildMode == BM_BASIC )
        setWindowTitle(sWindow_Title);
    else
    {
		setWindowTitle(pDoc->windowTitle() + " - " + QString(sWindow_Title));
    }
}

/**
 * Get the title string to be used for child dialogs.
 *  This is different than the main window's title because the main one can
 *  have the current file opened and [*] in the name.
 * 
 * @see updateWindowTitle()
 * @return default child dialog title
 */
QString ArkivMainWindow::getDialogTitle() const
{
    return sDialog_Title;
}

/**
 * Callback every minute.
 */
void ArkivMainWindow::onMinuteTimer()
{
	// prevent re-entrancy
    static bool processing = false;
    if ( processing )
        return;
    processing = true;

    // periodically save state in case we crash and lose all the layout changes
    saveApplicationStates();

	// auto-save
    if ( AuthoringSettings::singleton().autoSaveEnabled )
    {
        ++m_AutoSaveAccum;

        // correct for bad values
        const int autoSaveMinutes = qMax(AuthoringSettings::singleton().autoSaveMinutesInterval,1);
        AuthoringSettings::singleton().autoSaveMinutesInterval = autoSaveMinutes;

        if ( m_AutoSaveAccum >= autoSaveMinutes )
        {
            m_AutoSaveAccum = 0;
            ArkivIDEDoc* playDoc = ArkivDocManager::Instance().getPlayDoc();
            if ( playDoc && !playDoc->autoSave(false) )
            {
                const int result = QMessageBox::question(
                    this,
                    tr("Failed to AutoSave"),
                    tr("Failed to AutoSave.  Do you want to temporarily disable AutoSave?"),
                    QMessageBox::Yes | QMessageBox::No );
                if ( result == QMessageBox::Yes )
                    AuthoringSettings::singleton().autoSaveEnabled = false;
            }
        }
    }

    trackUserActive();

    processing = false;
}

/**
 * Deletes the splash screen.
 *  After deleting, shows the tip of the day dialog.
 */
void ArkivMainWindow::onDeleteSplashScreen()
{
    if ( m_splashScreen )
    {
        delete m_splashScreen;
        m_splashScreen = NULL;
    }
}

void ArkivMainWindow::toggleBuildMode()
{
    if ( m_BuildMode == BM_ADVANCED )
        setBuildMode(BM_BASIC);
    else if ( m_BuildMode == BM_BASIC )
        setBuildMode(BM_ADVANCED);

	UpdateUIManager::Instance().updateBuildMode();

    // TODO - handle other build modes
}

/**
 * Sets the current mode for building.
 *  Basic mode disables all dock widgets and toolbars.
 *  Advanced mode shows everything. 
 */
void ArkivMainWindow::setBuildMode(eBuildMode buildMode)
{
    //saveApplicationStates();

    QSettings settings;

    // if using the default, set it from the settings
    if ( buildMode == BM_LASTMODE )
        buildMode = (eBuildMode)settings.value("BuildMode",BM_ADVANCED).toInt();
    
    m_BuildMode = buildMode;
    settings.setValue("BuildMode",m_BuildMode);
}

void ArkivMainWindow::closePlayDoc()
{
	IArkivDoc* playDoc = ArkivDocManager::Instance().getPlayDoc();       
	if (playDoc)
		requestDocClose(playDoc);
}

/**
 * Callback for the command toolbar changing floating/docking state.
 *  Handles setting the maximum size of the script input combobox so it works as expected.
 */
void ArkivMainWindow::onCommandToolBarTopLevelChanged(bool topLevel)
{
    if ( topLevel )
        m_pScriptComboBox->setFixedWidth(800);
    else
    {
        m_pScriptComboBox->setMinimumWidth(300);
        m_pScriptComboBox->setMaximumWidth(QWIDGETSIZE_MAX);
    }

    commandToolBar->layout()->invalidate();
}

void ArkivMainWindow::onPropertyChanged(const RBX::Reflection::PropertyDescriptor* pDescriptor)
{
    if (AuthoringSettings::singleton().getOutputLayoutMode() == AuthoringSettings::OutputLayoutHorizontal)
    {
        setCorner(Qt::TopLeftCorner, Qt::TopDockWidgetArea);
        setCorner(Qt::TopRightCorner, Qt::TopDockWidgetArea);
        setCorner(Qt::BottomLeftCorner, Qt::BottomDockWidgetArea);
        setCorner(Qt::BottomRightCorner, Qt::BottomDockWidgetArea);
    }
    else
    {
        setCorner(Qt::TopLeftCorner, Qt::LeftDockWidgetArea);
        setCorner(Qt::TopRightCorner, Qt::RightDockWidgetArea);
        setCorner(Qt::BottomLeftCorner, Qt::LeftDockWidgetArea);
        setCorner(Qt::BottomRightCorner, Qt::RightDockWidgetArea);
    }

    if (AuthoringSettings::singleton().diagnosticsBarEnabled) 
    {
        UpdateUIManager::Instance().updateStatusBar();
    }
}

void ArkivMainWindow::setupActionCounters()
{
    if (!FFlag::GoogleAnalyticsTrackingEnabled)
        return;

    QString ignoreActions("renameObjectAction");

	QList<QAction*> actionList = findChildren<QAction*>();

	if (FFlag::StudioSeparateActionByActivationMethod)
	{
		//We should eventually subclass QAction for this
		static QString noSlotActions("startServerCB fileNewAction fileOpenAction fileCloseAction "
			"fileSaveAction fileSaveAsAction fileExitAction"); 

		for(QList<QAction*>::const_iterator iter = actionList.begin(); iter != actionList.end(); iter++)
		{
			if (noSlotActions.contains((*iter)->objectName()))
				continue;

			QAction* currentAction = *iter;
			connect(currentAction, SIGNAL(triggered(bool)), this, SLOT(commonSlot(bool)));
			currentAction->installEventFilter(this);
		}
	}
	else
	{
		QSignalMapper* signalMapper = new QSignalMapper(this);
		for(QList<QAction*>::const_iterator iter = actionList.begin(); iter != actionList.end(); iter++)
		{
			QAction* currentAction = *iter;
			if(!currentAction->objectName().isEmpty() && !ignoreActions.contains(currentAction->objectName()))
			{
				connect(currentAction, SIGNAL(triggered()), signalMapper, SLOT(map()));
				signalMapper->setMapping(currentAction, currentAction->objectName());
			}
		}
		connect(signalMapper, SIGNAL(mapped(QString)), this, SLOT(sendActionCounterEvent(QString)));
	}
}

void ArkivMainWindow::trackToolboxInserts(RBX::ContentId contentId, const RBX::Instances& instances)
{
	std::vector<weak_ptr<RBX::Instance> > weakInstances;

	for (RBX::Instances::const_iterator iter = instances.begin(); iter != instances.end(); ++iter)
		weakInstances.push_back(weak_from(iter->get()));

	m_insertObjectItems.push(InsertObjectItem(contentId.getAssetId(), weakInstances));

	QTimer::singleShot(FInt::StudioInsertDeletionCheckTimeMS, this, SLOT(checkInsertedObjects()));
}

void ArkivMainWindow::checkInsertedObjects()
{
	if (m_insertObjectItems.size() == 0)
		return;

	InsertObjectItem insertedInstance = m_insertObjectItems.front();
	m_insertObjectItems.pop();

	bool objectsStillExist = true;

	for (std::vector<weak_ptr<RBX::Instance> >::const_iterator iter = insertedInstance.weakInstances.begin(); iter != insertedInstance.weakInstances.end(); ++iter)
	{
		if (shared_ptr<RBX::Instance> sharedInstance = iter->lock())
		{
			if (!RBX::DataModel::get(sharedInstance.get()))
			{
				objectsStillExist = false;
				break;
			}
		}
		else
		{
			objectsStillExist = false;
			break;
		}
	}

	RBX::ArkivGoogleAnalytics::trackEvent(GA_CATEGORY_STUDIO, objectsStillExist ? "StudioInsertRemains" : "StudioInsertDeleted", insertedInstance.contentId.c_str());
}

void ArkivMainWindow::sendActionCounterEvent(const QString& action)
{
    if (FFlag::GoogleAnalyticsTrackingEnabled)
		RBX::ArkivGoogleAnalytics::trackEvent(GA_CATEGORY_ACTION, "StudioUserAction", action.toStdString().c_str());
}

void ArkivMainWindow::notifyCloudEditConnectionClosed()
{
	if (m_cloudEditAwaitingShutdown)
	{
		m_cloudEditAwaitingShutdown->Set();
		return;
	}

	ArkivIDEDoc* ideDoc = ArkivDocManager::Instance().getPlayDoc();
	if (ideDoc && !m_IgnoreCloudEditDisconnect)
	{
		QString script = ideDoc->initializationScript();
		QtUtilities::RBXMessageBox notificationDialog;
		notificationDialog.setIcon(QMessageBox::Warning);
		if (FFlag::TeamCreateEnableDownloadLocalCopy)
		{
			notificationDialog.setText("You have lost connection to the server. "
				"Do you want to reconnect or save a copy of the place to a new file?");
		}
		else
		{
			notificationDialog.setText("You have lost connection to the server. "
				"Do you want to reconnect or work locally (you have to save local work to a new file)?");
		}
		notificationDialog.addButton("Reconnect", QMessageBox::ResetRole);
		if (FFlag::TeamCreateEnableDownloadLocalCopy)
			notificationDialog.addButton("Save Local Copy", QMessageBox::ActionRole);
		else
			notificationDialog.addButton("Work Offline", QMessageBox::DestructiveRole);
		notificationDialog.exec();
		QMessageBox::ButtonRole role = notificationDialog.buttonRole(notificationDialog.clickedButton());
		if (role == QMessageBox::ResetRole)
		{
			// close the play doc if it is still open
			if (IArkivDoc* playDoc = ArkivDocManager::Instance().getPlayDoc())
			{
				requestDocClose(*playDoc, false /*closeiflastdoc*/);
			}
			handleFileOpen(fileLocationArg, IArkivDoc::IDE, script);
		}
		else if (FFlag::TeamCreateEnableDownloadLocalCopy && (role == QMessageBox::ActionRole))
		{
			if (ArkivIDEDoc* playDoc = ArkivDocManager::Instance().getPlayDoc())
			{
				// let users save a local copy
				QString fileName = playDoc->downloadPlaceCopy();
				// close the online document
				requestDocClose(*playDoc, false /*closeiflastdoc*/);
				if (!fileName.isEmpty())
					handleFileOpen(fileName, IArkivDoc::IDE);
			}
		}
	}
}

void ArkivMainWindow::cloudEditStatusChanged(int placeId, int universeId)
{
	RBX::ScopedAssign<bool> ignoreDocActivate(m_IgnoreCloudEditDisconnect, true);

	if (IArkivDoc* playDoc = ArkivDocManager::Instance().getPlayDoc())
	{
		requestDocClose(*playDoc, false /*closeiflastdoc*/);
	}

	QString initScript;
	if (FFlag::UseBuildGenericGameUrl)
	{
		QString pathStr = QString("Game/edit.ashx?PlaceID=%1&upload=%1&testmode=false&universeId=%2").arg(placeId).arg(universeId);
		initScript = QString::fromStdString(BuildGenericGameUrl(ArkivSettings::getBaseURL().toStdString(), pathStr.toStdString()));
	}
	else
	{
		initScript = QString("%1/Game/edit.ashx?PlaceID=%2&upload=%2&testmode=false&universeId=%3").arg(ArkivSettings::getBaseURL()).arg(placeId).arg(universeId);
	}

	handleFileOpen(FFlag::StudioDoublingOnUploadFixEnabled ? "" : fileLocationArg,
		IArkivDoc::IDE, initScript);
}

void ArkivMainWindow::shutDownCloudEditServer()
{
	using namespace RBX;
	using namespace Network;

	RBXASSERT(QThread::currentThread() == qApp->thread());

	ArkivIDEDoc* playDoc = ArkivDocManager::Instance().getPlayDoc();
	RBXASSERT(playDoc);
	if (!playDoc) return;

	RBXASSERT(playDoc->isCloudEditSession());
	if (!playDoc->isCloudEditSession()) return;

	shared_ptr<DataModel> dm = playDoc->getEditDataModel();
	RBXASSERT(dm);
	if (!dm) return;

	long placeId, universeId;
	{
		{
			DataModel::LegacyLock lock(dm.get(), DataModelJob::Write);

			placeId = dm->getPlaceID();
			universeId = dm->getUniverseId();

			Players* players = dm->find<Players>();
			RBXASSERT(players);
			if (players)
			{
				RBXASSERT(!m_cloudEditAwaitingShutdown);
				m_cloudEditAwaitingShutdown.reset(new RBX::CEvent(true /* manual reset */));
				Players::event_requestCloudEditShutdown.replicateEvent(players);
			}
		}
		
		if (m_cloudEditAwaitingShutdown)
		{
			UpdateUIManager::Instance().waitForLongProcess("Waiting for Shutdown", boost::bind(&RBX::CEvent::Wait, m_cloudEditAwaitingShutdown.get()));
			m_cloudEditAwaitingShutdown.reset();
		}
	}

	QMetaObject::invokeMethod(this, "cloudEditStatusChanged", Qt::QueuedConnection, Q_ARG(int, placeId), Q_ARG(int, universeId));
}

void ArkivMainWindow::setupCustomToolButton()
{	
	m_pFillColorToolButton = new FillColorPickerToolButton(this);
	m_pFillColorToolButton->setObjectName("actionFillColor");
	m_pFillColorToolButton->setDefaultAction(actionFillColor);
	connect(m_pFillColorToolButton, SIGNAL(changed(const QString &)), this, SLOT(onCustomToolButton(const QString &)));

	m_pMaterialToolButton = new MaterialPickerToolButton(this);
	m_pMaterialToolButton->setObjectName("actionMaterial");
	m_pMaterialToolButton->setDefaultAction(actionMaterial);
	connect(m_pMaterialToolButton, SIGNAL(changed(const QString &)), this, SLOT(onCustomToolButton(const QString &)));

	//add tool buttons into toolbar
	QAction *fillAction = advToolsToolBar->insertWidget(dropperAction, m_pFillColorToolButton);
	fillAction->setObjectName("actionFillColor_WidgetAction");

	QAction *materialAction = advToolsToolBar->insertWidget(smoothSurfaceAction, m_pMaterialToolButton);
	materialAction->setObjectName("actionMaterial_WidgetAction");

	advToolsToolBar->insertSeparator(materialAction);
	advToolsToolBar->insertSeparator(smoothSurfaceAction);
}

void ArkivMainWindow::trackUserActive()
{
	// We want an accurate session length so we send up a special event
	// if there is any user interaction with app that is not tracked
	// by other metrics.
    
	const int eventIdleTime = 60 * 1000; // in milliseconds
	const int stillAliveTime = 20 * 1000; // in milliseconds
    
	// If it has been some time (eventIdleTime) since the last event tracked.
	if (m_lastAnalyticTrackedTime.elapsed() > eventIdleTime
        
        // And the user is not completely idle and some system is posting
        // a keep alive.
	    && m_lastAnalyticKeepAliveTime.elapsed() < stillAliveTime)
	{
        // Send an empty timing event.
        RBX::ArkivGoogleAnalytics::trackUserTiming("", "", 0);
	}
}

void ArkivMainWindow::onAnalyticTracked()
{
	m_lastAnalyticTrackedTime = QTime::currentTime();
}


void ArkivMainWindow::keepAliveAnalyticsSession()
{
	m_lastAnalyticKeepAliveTime = QTime::currentTime();
}

void ArkivMainWindow::cleanupPlayersAndServers()
{
	ArkivApplicationManager::instance().cleanupChildProcesses();
	cleanupServersAndPlayersAction->setEnabled(false);
}

void ArkivMainWindow::onIDEDocViewInitialized()
{
    if ( m_splashScreen )
        onDeleteSplashScreen();
}

void ArkivMainWindow::cookieConstraintCheckerLoadFinished(bool ok)
{
	RBXASSERT(m_cookieConstraintChecker);
	if (!m_cookieConstraintChecker)
		return;

	if (ok && m_cookieConstraintChecker->url().toString().contains(
		FString::StudioCookieConstraintUrlFragment.c_str(), Qt::CaseInsensitive))
	{
		m_cookieConstraintChecker->raise();
		m_cookieConstraintChecker->show();
	}
	else
	{
		m_cookieConstraintChecker->hide();
		disconnect(
			m_cookieConstraintChecker, SIGNAL(                     loadFinished(bool)),
			this,                      SLOT(cookieConstraintCheckerLoadFinished(bool)));
		m_cookieConstraintChecker->deleteLater();
		m_cookieConstraintChecker = NULL;
		m_cookieConstraintCheckDone->exit();
	}
}


