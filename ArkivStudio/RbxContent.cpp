/**
 * RbxContent.cpp
 * Copyright (c) 2013 ARKIV Corp. All Rights Reserved.
 */

#include "stdafx.h"
#include "RbxContent.h"

// Arkiv Headers
#include "util/Http.h"
#include "util/standardout.h"

#include "ArkivGameExplorer.h"
#include "UpdateUIManager.h"

FASTFLAG(StudioEnableGameAnimationsTab)

RbxContent::RbxContent( QObject *parent) 
: QObject(parent)
{
}

// Publish Selection To Arkiv
QString RbxContent::Upload(const QString &urlQStr)
{
	QByteArray ba = urlQStr.toLocal8Bit();
	const char *url = ba.data();
	
	bool success = RBX::Http::trustCheck(url);
	std::string response;
	if(success)
	{
		try 
		{			
			RBX::Http http(url);
			http.post(data, RBX::Http::kContentTypeApplicationXml, true, response);
		}
		catch (std::exception &e) 
		{
			RBX::StandardOut::singleton()->print(RBX::MESSAGE_ERROR, e.what());
			return QString("");
		}
	}

	// if we are creating 'new' animation game asset then we will need to reload game explorer 
	if (FFlag::StudioEnableGameAnimationsTab && !response.empty() && 
		urlQStr.contains("uploadnewanimation?assetTypeName=Animation") && urlQStr.contains("isGamesAsset=True"))
	{
		ArkivGameExplorer& gameExplorer = UpdateUIManager::Instance().getViewWidget<ArkivGameExplorer>(eDW_GAME_EXPLORER);		
		QMetaObject::invokeMethod(&gameExplorer, "reloadDataFromWeb", Qt::QueuedConnection);
	}

	return QString::fromStdString(response);
}


