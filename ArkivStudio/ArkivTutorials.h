/**
 * ArkivTutorials.h
 * Copyright (c) 2014 ARKIV Corp. All Rights Reserved.
 */

#pragma once

#include <QObject>
#include <QWidget>
#include <QPushButton>

class QUrl;
class QToolBar;

class ArkivBrowser;

class ArkivTutorials: public QWidget
{
	Q_OBJECT

public:
	ArkivTutorials();

private Q_SLOTS:
	void linkClicked(const QUrl& url);
	void urlChanged(const QUrl& url);
	void disableLinks(const QUrl& url);
	void updateButtons();
	void handleHomeClicked();

	void resizeWidget();

private:
	void setupWebView(QWidget*);

	ArkivBrowser                       *m_pWebView;
	ArkivBrowser						*m_pWebContentsView;
	QWidget                             *m_pWrapperWidget;
	QPushButton							*m_pBackButton;
	QPushButton							*m_pForwardButton;
	QPushButton							*m_pStopButton;
	QPushButton							*m_pReloadButton;
	QPushButton							*m_pHomeButton;

	bool								m_firstPaint;
	bool								m_firstClick;
};

