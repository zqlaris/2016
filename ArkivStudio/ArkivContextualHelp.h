/**
 * ArkivContextualHelp.h
 * Copyright (c) 2013 ARKIV Corp. All Rights Reserved.
 */

#pragma once

#include "ArkivBrowser.h"
#include "ArkivWebPage.h"

#include <QWidget>

class ArkivContextualHelpService : public QObject
{
    Q_OBJECT
public:
    ArkivContextualHelpService();
    
    static ArkivContextualHelpService& singleton();

public Q_SLOTS:
    void onHelpTopicChanged(const QString& helpTopic);

Q_SIGNALS:
    void helpTopicChanged(const QString&);

private:
    QString m_helpTopic;
};

class ArkivContextualHelp;

class ArkivHelpWebView : public ArkivBrowser
{
    Q_OBJECT
public:
    ArkivHelpWebView(ArkivContextualHelp* widget);

protected:
    void paintEvent(QPaintEvent* event);

private Q_SLOTS:
    void loadProgress(int);

private:
    ArkivContextualHelp*    m_contextualHelpWidget;
};

class ArkivContextualHelp : public QWidget
{
	Q_OBJECT
	
public:
    ArkivContextualHelp();

    void updateURL();

public Q_SLOTS:
    void onAuthenticationChanged(bool isAuthenticated);
    void onHelpTopicChanged(const QString& helpTopic);
    
private Q_SLOTS:
	void linkClicked(const QUrl& url);
    
private:
    void setupWebView();
   
    ArkivHelpWebView*      m_pWebView;
    ArkivWebPage*          m_pWebPage;
    QString                 m_urlString;
    bool                    m_urlDirty;
};

