/**
 * ArkivSettings.cpp
 * Copyright (c) 2013 ARKIV Corp. All Rights Reserved.
 */

#include "stdafx.h"
#include "ArkivSettings.h"

// Qt Headers
#include <QDomDocument>
#include <QFile>
#include <QDir>
#include <QApplication>
#include <QDesktopServices>

// Arkiv Headers
#include "v8datamodel/ContentProvider.h"
#include "v8datamodel/DebugSettings.h"
#include "script/script.h"
#include "util/Statistics.h"

// Arkiv Studio Headers
#include "RbxWorkspace.h"

#ifdef _WIN32
    #include "ArkivStudioVersion.h"
#endif

AppSettings& AppSettings::instance()
{			
	static AppSettings singleton;
	return singleton;
}

AppSettings::AppSettings()
: m_bIsScriptAssetUploadEnabled(false)
, m_bIsAnimationAssetUploadEnabled(false)
, m_bIsImageModelAssetUploadEnabled(false)
{
	QString executableFolder = QApplication::applicationDirPath();
	QFile file(executableFolder + "/AppSettings.xml");
	if (file.open(QIODevice::ReadOnly))
	{
		QDomDocument doc("appSettings");
		if (doc.setContent(&file)) 
		{
			QDomElement docElem = doc.documentElement();
			if(docElem.tagName() == "Settings")
			{
				QDomElement content = docElem.firstChildElement("ContentFolder");
				QString dummy = content.text();
				m_contentFolder = executableFolder + "/" + dummy;

				dummy.replace("content", "BuiltInPlugins");
				m_builtInPluginsFolder = executableFolder + "/" + dummy;

				content = docElem.firstChildElement("BaseUrl");				
				m_baseURL = content.text();

				content = docElem.firstChildElement("IsScriptAssetUploadEnabled");				
				m_bIsScriptAssetUploadEnabled = content.text() == "1";
				
				content = docElem.firstChildElement("IsAnimationAssetUploadEnabled");				
				m_bIsAnimationAssetUploadEnabled = content.text() == "1";

				content = docElem.firstChildElement("IsImageModelAssetUploadEnabled");				
				m_bIsImageModelAssetUploadEnabled = content.text() == "1";

				content = docElem.firstChildElement("CrashMenu");				
				m_bShowStudioCrashMenu = content.text() == "1";
#ifdef STUDIO_ADMIN_BUILD
				content = docElem.firstChildElement("AdminKey");				
				m_adminKey = content.text();
#endif
			}
		}
		file.close();
	}

#ifdef _WIN32
	m_tempLocation = QDir::homePath() + "/AppData/Local/Arkiv";
#else
	m_tempLocation = QDesktopServices::storageLocation(QDesktopServices::DocumentsLocation) + "/Arkiv";
#endif
	if(!QFile::exists(m_tempLocation))
		QDir().mkpath(m_tempLocation);
}

ArkivSettings::ArkivSettings()
:QSettings()
{
}

void ArkivSettings::saveAssets()
{
	ArkivSettings settings;
	settings.setValue("BaseUrl", QString(::GetBaseURL().c_str()));
	settings.setValue("ContentFolder", QString(RBX::ContentProvider::assetFolder().c_str()));
}

void ArkivSettings::recoverAssets()
{
	QString baseUrl = AppSettings::instance().baseURL();
	::SetBaseURL(baseUrl.toStdString());

	QString assetFolder = AppSettings::instance().contentFolder();
	QByteArray assetFolderUtf8 = assetFolder.toUtf8();

	RBX::ContentProvider::setAssetFolder(std::string(assetFolderUtf8.data(), assetFolderUtf8.size()).c_str());
}

QString ArkivSettings::getAssetFolder()
{
	return AppSettings::instance().contentFolder();
}

QString ArkivSettings::getBuiltInPluginsFolder()
{
	return AppSettings::instance().builtInPluginsFolder();
}

QString ArkivSettings::getBaseURL()
{
	return AppSettings::instance().baseURL();
}

QString ArkivSettings::getApiBaseURL()
{
	return QString::fromStdString(RBX::ContentProvider::getUnsecureApiBaseUrl(getBaseURL().toStdString()));
}

#ifdef STUDIO_ADMIN_BUILD
QString ArkivSettings::getAdminKey()
{
	return AppSettings::instance().adminKey();
}
#endif

QString ArkivSettings::getVersionString()
{
	QString version;
#ifdef _WIN32
	version = VER_FILEVERSION_STR;
	version.replace(',','.');
#else
	QString plistPath = QApplication::applicationDirPath() + "/../info.plist";
	QSettings settings(plistPath, QSettings::NativeFormat);
	version = settings.value("CFBundleShortVersionString").toString();
#endif
	RBX::DebugSettings::arkivVersion = version.toStdString();
	return version;

}

QString ArkivSettings::getTempLocation()
{
	return AppSettings::instance().tempLocation();
}

QString ArkivSettings::getResourcesFolder()
{
	QString resourcesFolder = QApplication::applicationDirPath();
#ifdef Q_WS_MAC
	resourcesFolder += "/../Resources";
#endif
	return resourcesFolder;
}

void ArkivSettings::initWorkspaceSettings()
{
	RbxWorkspace::isScriptAssetUploadEnabled = AppSettings::instance().isScriptAssetUploadEnabled();
	RbxWorkspace::isAnimationAssetUploadEnabled = AppSettings::instance().isAnimationAssetUploadEnabled();
	RbxWorkspace::isImageModelAssetUploadEnabled = AppSettings::instance().isImageModelAssetUploadEnabled();
	
}

bool ArkivSettings::showCrashMenu()
{
	return AppSettings::instance().showCrashMenu();
}
