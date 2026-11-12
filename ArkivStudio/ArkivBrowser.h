/**
 * ArkivBrowser.h
 * Copyright (c) 2013 ARKIV Corp. All Rights Reserved.
 */

#pragma once

// Qt Headers
#include <QWebView>

class ArkivBrowser : public QWebView 
{
	Q_OBJECT

public: 

	ArkivBrowser(QWidget* parent=0);
    virtual ~ArkivBrowser();

public Q_SLOTS:

	bool close();
    void resetLoadingTimer();
    
protected:
    
    virtual void paintEvent(QPaintEvent*);
 	virtual void dropEvent(QDropEvent* evt);

private Q_SLOTS:

    void loadStarted();
    void loadFinished(bool);
    
private:
    
    void drawLoadingWatermark();
    
	ArkivBrowser*  m_pPopup;
	QDialog*        m_pPopupDlg;
    QTimer*         m_loadingTimer;
    float           m_refreshIncr;
};
