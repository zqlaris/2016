/**
 * ArkivNetworkAccessManager.cpp
 * Copyright (c) 2013 ARKIV Corp. All Rights Reserved.
 */

#include "stdafx.h"
#include "ArkivNetworkAccessManager.h"

// Arkiv Headers
#include "QtUtilities.h"
#include "ArkivCookieJar.h"
#include "ArkivWebPage.h"
#include "ArkivSettings.h"
#include "ArkivNetworkReply.h"

ArkivNetworkAccessManager::ArkivNetworkAccessManager()
: QNetworkAccessManager()
{
	// When we enable the Cookie Persistence, logging into mail.arkiv.com stops working, but works fine for www.arkiv.com with persistence
	setCookieJar(new ArkivCookieJar());
}
void ArkivNetworkAccessManager::initUserAgent()
{
	// Set up our useragent
	ArkivWebPage dummy;
	userAgent = dummy.getDefaultUserAgent();
	
	// Only on Mac webkit does not provide the OSX version, add it, will do only for Mac
	QString macOSXVersion = QtUtilities::getMacOSXVersion();
	userAgent = userAgent.replace("Mac OS X", macOSXVersion);
}
QString ArkivNetworkAccessManager::getUserAgent()
{
	if (userAgent.isEmpty())
		initUserAgent();
	return userAgent;
}

ArkivNetworkReply* ArkivNetworkAccessManager::get(const QNetworkRequest& request, bool followRedirection /*= true*/ )
{
	QNetworkReply* reply = QNetworkAccessManager::get(request);
	ArkivNetworkReply* arkivreply = new ArkivNetworkReply(reply, followRedirection);
	return arkivreply;
}

ArkivCookieJar* ArkivNetworkAccessManager::cookieJar() const
{
	return dynamic_cast<ArkivCookieJar*>(QNetworkAccessManager::cookieJar());
}
