/**
 * DocTabWidget.h
 * Copyright (c) 2013 ARKIV Corp. All Rights Reserved.
 */

#pragma once

// Qt Headers
#include <QRubberBand>
#include <QIcon>

// Arkiv Headers
#include "RBX/BaldPtr.h"

// Arkiv Studio Headers
#include "IArkivDoc.h"

class QRubberBand;

class ArkivMainWindow;
class ArkivTabWidget;

class DocTabManager : public QObject
{
    Q_OBJECT

    public:

        DocTabManager(ArkivMainWindow& mainWindow);
        virtual ~DocTabManager();

        void addDoc(IArkivDoc& doc, int index = -1);
        bool removeDoc(IArkivDoc& doc);
        bool renameDoc(IArkivDoc& doc,const QString& text,const QString& tooltip,const QIcon& icon = QIcon());

        bool setCurrentDoc(IArkivDoc& doc);
        IArkivDoc* getCurrentDoc() const;

        void setDockHoverOverPos(const QPoint& globalPos);
        bool attemptAttach(IArkivDoc& doc,const QPoint& globalPos);

        void restoreAsCentralWidget();

    public Q_SLOTS:
        void showNextTabPage();
        void showPreviousTabPage();

    protected:

        virtual bool eventFilter(QObject* object,QEvent* event);

    private Q_SLOTS:

        void onCurrentChanged(int index);
        bool onTabCloseRequested(int index);
        void onCurrentTabCloseRequested();
        void onDetachDoc();
        void onFocusChanged(QWidget* oldWidget,QWidget* newWidget);
        
    private:

        void onMousePressEvent(QMouseEvent* event);
        void onMouseMoveEvent(QMouseEvent* event);
        void onMouseReleaseEvent(QMouseEvent* event);
        bool isValidHoverOver(const QPoint& globalPos);
    
        void setupTabPageSwitchingShortcuts();
        void setCurrentTabPage(int index);

        typedef QVector< RBX::BaldPtr<IArkivDoc> > tDocList;

        tDocList                		m_Docs;
        ArkivMainWindow&       		m_MainWindow;
        QPoint                  		m_ClickPos;
        bool                    		m_MouseDown;
        int                     		m_DragTabIndex;
        QRubberBand             		m_RubberBand;
        RBX::BaldPtr<QWidget>   		m_FakeTab;
		RBX::BaldPtr<ArkivTabWidget>	m_TabWidget;
};

