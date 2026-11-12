/**
 * ArkivFollowRedirectionNetworkRequest.cpp
 * Copyright (c) 2013 ARKIV Corp. All Rights Reserved.
 */

#include "stdafx.h"
#include "ArkivNetworkReply.h"

// Qt headers
#include <QTime>
#include <QCoreApplication>
#include <QEventLoop>

// Arkiv headers
#include "Rbx/debug.h"

// Arkiv Studio headers
#include "ArkivNetworkAccessManager.h"

ArkivNetworkReply::ArkivNetworkReply(QNetworkReply* pReply, bool followRedirections)
	: m_pReply(pReply)
	, m_childReply(NULL)
	, m_followRedirections(followRedirections)
{
	// Set up the new network reply to follow redirection or signal if it's done
	connect(pReply, SIGNAL(finished()), this, SLOT(handleRedirection()));
}
ArkivNetworkReply::~ArkivNetworkReply()
{
	RBXASSERT(m_pReply->isFinished()); // Catch weird cases where request was aborted
	delete m_pReply;
}
void ArkivNetworkReply::onChildFinished()
{
	Q_EMIT finished();
}
void ArkivNetworkReply::handleRedirection()
{
	RBXASSERT(m_pReply);
	
	if (!m_pReply) // TODO: What should we do here?
		return;

	QString redirectUrl = m_pReply->attribute(QNetworkRequest::RedirectionTargetAttribute).toString();
	if (!redirectUrl.isEmpty() 
		&& m_followRedirections 
		&& !m_redirectUrls.contains(redirectUrl)) // Prevent infinite loops
		// TODO: Detect cycles
	{
		QNetworkRequest request(redirectUrl);
		ArkivNetworkReply* networkReply = ArkivNetworkAccessManager::Instance().get(request, true);
		networkReply->setParent(this);
		networkReply->m_redirectUrls.insert(redirectUrl);
		m_childReply = networkReply;
		
		// When it signals it is done, we need to trigger this network reply to signal (fire all the way up)
		connect(networkReply, SIGNAL(finished()), this, SLOT(onChildFinished()));
	}
	else
		onChildFinished(); // Trigger our final finished
}

QNetworkReply* ArkivNetworkReply::getLastNetworkReply() const
{
	if (m_childReply)
	{
		RBXASSERT(m_followRedirections);  // will only have a m_childReply if followRedirections is true
		return m_childReply->getLastNetworkReply();	 // Go to the last child reply
	}
	else
		return m_pReply;
}

/*
*  Returns true if the reply finished in time.  False if it timed out.
*/
bool ArkivNetworkReply::waitForFinished(int timeOutTime, int waitIntervalTime) const
{
	QNetworkReply* finalNetworkReply = getLastNetworkReply();
	
	RBXASSERT(finalNetworkReply);

	if (!finalNetworkReply) // TODO: what to do here?
		return true;

	QTime time;
	time.start();
	while(!finalNetworkReply->isFinished()) // wait until we get all of the response
	{
		QCoreApplication::processEvents(QEventLoop::AllEvents, waitIntervalTime); 
		if (time.elapsed() >= timeOutTime)
		{
			return false;
		}
		// Check to see if there have been any redirects since, and if so, start waiting for them
		finalNetworkReply = getLastNetworkReply();
	}
	return true;
}

QByteArray ArkivNetworkReply::readAll()
{
	return getLastNetworkReply()->readAll();	
}

QNetworkReply::NetworkError ArkivNetworkReply::error() const
{
	return getLastNetworkReply()->error();
}

int ArkivNetworkReply::statusCode() const
{
	return getLastNetworkReply()->attribute(QNetworkRequest::HttpStatusCodeAttribute).toInt();
}
