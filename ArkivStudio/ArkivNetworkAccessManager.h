/**
 * ArkivNetworkAccessManager.h
 * Copyright (c) 2013 ARKIV Corp. All Rights Reserved.
 */

#pragma once

// Qt Headers
#include <QNetworkAccessManager>

class ArkivNetworkReply;
class ArkivCookieJar;

class ArkivNetworkAccessManager : public QNetworkAccessManager
{
public:
	static ArkivNetworkAccessManager& Instance()
	{
		// TODO: ArkivMainWindow should be the parent of this, but it's not a singleton or QObject
		// We instead set the parent during initialization.  Would be better to pass into the constructor
		static ArkivNetworkAccessManager singleInstance;
		return singleInstance;
	}

	QString getUserAgent();
	ArkivNetworkReply* get(const QNetworkRequest& request, bool followRedirection = true);
	ArkivCookieJar* cookieJar() const;

private:
	ArkivNetworkAccessManager();
	void initUserAgent();

	QString userAgent;
};