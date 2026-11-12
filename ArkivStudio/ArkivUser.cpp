/**
 * ArkivUser.cpp
 * Copyright (c) 2013 ARKIV Corp. All Rights Reserved.
 */

#include "stdafx.h"
#include "ArkivUser.h"

// Arkiv headers
#include "Rbx/debug.h"

// Arkiv Studio headers
#include "ArkivCookieJar.h"
#include "ArkivNetworkAccessManager.h"
#include "ArkivNetworkReply.h"
#include "ArkivSettings.h"
#include "AuthenticationHelper.h"

#include "Util/ArkivGoogleAnalytics.h"
#include "V8DataModel/Stats.h"

ArkivUser& ArkivUser::singleton()
{
    static ArkivUser user;
	return user;
}

ArkivUser::ArkivUser()
	: m_webKitUserId(-1)
{
    connect(&AuthenticationHelper::Instance(), SIGNAL(authenticationChanged(bool)), this, SLOT(onAuthenticationChanged(bool)));
}

ArkivUser::~ArkivUser()
{
	m_webKitUserIDQuery.get();
}

void ArkivUser::init()
{
	if (m_webKitUserId == -1)
		getWebkitUserId();
}

// Keep this user up to sync on auth changes
void ArkivUser::onAuthenticationChanged(bool)
{
	m_webKitUserId = -1;
	getWebkitUserId();
}

void ArkivUser::currentUserReplied(RBX::HttpFuture future)
{
	try {
		QString webKitUserIDStr(QString::fromStdString(future.get()));
		m_webKitUserId = webKitUserIDStr.toInt();
		RBX::Analytics::setUserId(m_webKitUserId);

		// TODO: remove
		RBX::ArkivGoogleAnalytics::setUserID(m_webKitUserId);
	}
	catch(std::exception&)
	{
		m_webKitUserId = 0;
	}
}

void ArkivUser::getWebkitUserId()
{
	std::string url(AuthenticationHelper::getLoggedInUserUrl().toStdString());
    m_webKitUserIDQuery = RBX::HttpAsync::get(url).then(boost::bind(&ArkivUser::currentUserReplied, this, _1));
}

int ArkivUser::getUserId()
{
	if(m_webKitUserId == -1)
	{
		// make sure we are authenticated before querying user id		
		AuthenticationHelper::Instance().waitForHttpAuthentication();
		if (!m_webKitUserIDQuery.valid())
			getWebkitUserId();		

		m_webKitUserIDQuery.get();
	}

	return m_webKitUserId;
}
