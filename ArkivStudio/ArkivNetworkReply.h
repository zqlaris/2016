/**
 * ArkivFollowRedirectionNetworkRequest.h
 * Copyright (c) 2013 ARKIV Corp. All Rights Reserved.
 */

#pragma once

// Qt headers
#include <QNetworkReply>
#include <QSet>

class ArkivNetworkReply : public QObject
{
	Q_OBJECT

public:
	ArkivNetworkReply(QNetworkReply* pReply, bool followRedirections);
	~ArkivNetworkReply();
	
	bool waitForFinished(int timeOutTime, int waitIntervalTime) const;
	QByteArray readAll();
	QNetworkReply::NetworkError error() const;
	int statusCode() const;

Q_SIGNALS:
	void finished();

private Q_SLOTS:
	void onChildFinished();
	void handleRedirection();

private:
public: QNetworkReply* m_pReply;
	ArkivNetworkReply* m_childReply; // If we're following redirections, this was the last reply (used for signal chaining)
	QSet<QString> m_redirectUrls; // Used to prevent infinite loops
	bool m_followRedirections;

	QNetworkReply* getLastNetworkReply() const;

};