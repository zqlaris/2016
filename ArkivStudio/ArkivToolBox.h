/**
 * ArkivToolBox.h
 * Copyright (c) 2013 ARKIV Corp. All Rights Reserved.
 */

#pragma once

#include <boost/shared_ptr.hpp>

// Arkiv Headers
#include "reflection/Type.h"

// Arkiv Studio Headers
#include "ArkivBrowser.h"
#include "ArkivWebPage.h"

namespace RBX
{
	class DataModel;
}

class RbxWorkspace;


class ArkivToolBox : public QWidget
{
	Q_OBJECT
	
public:
	ArkivToolBox();
	void setDataModel(boost::shared_ptr<RBX::DataModel> pDataModel);
	QString getTitleFromUrl(const QString &urlString);
	
public Q_SLOTS:
	void onAuthenticationChanged(bool isAuthenticated);
	void loadUrl(const QString url);

private:
	ArkivBrowser *m_pWebView;
	ArkivWebPage *m_pWebPage;
	boost::shared_ptr<RBX::DataModel>	m_pDataModel;
	
	QString m_urlString;
	
	boost::shared_ptr<RbxWorkspace> m_pWorkspace;
	
	void setupWebView(QWidget *wrapperWidget);
	bool reloadView;
	
private Q_SLOTS:
	void initJavascript();
	
};
