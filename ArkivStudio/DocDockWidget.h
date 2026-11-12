/**
 * DocDockWidget.h
 * Copyright (c) 2013 ARKIV Corp. All Rights Reserved.
 */

#pragma once

// Qt Headers
#include <QDockWidget>

// Arkiv Headers
#include "rbx/BaldPtr.h"

// Arkiv Studio Headers
#include "IArkivDoc.h"

class ArkivMainWindow;
class DocDockManager;

class DocDockWidget : public QDockWidget
{
    Q_OBJECT

public:

    DocDockWidget(
        ArkivMainWindow&   mainWindow,
        DocDockManager&     docManager,
        IArkivDoc&         doc );

    virtual ~DocDockWidget();
    
    void setTitle(const QString& displayName,const QString& fileName);
    void cleanup();
    void startDragging();

public Q_SLOTS:

    void onAttachDoc();
    void onTopLevelChanged(bool TopLevel);
    void onDockLocationChanged(Qt::DockWidgetArea area);
    void onFocusChanged(QWidget* oldWidget,QWidget* newWidget);

protected:

    virtual void closeEvent(QCloseEvent* event);
    virtual void moveEvent(QMoveEvent* event);
    virtual void resizeEvent(QResizeEvent* event);
    virtual void mouseMoveEvent(QMouseEvent* event);
    virtual bool event(QEvent* event);
    virtual QSize sizeHint() const { return maximumSize(); }

#ifdef Q_WS_WIN32
    virtual bool winEvent(MSG* msg,long* result);
#endif

private:

    void simulateDrag();
    bool stopDragging();

    ArkivMainWindow&       m_MainWindow;
    DocDockManager&         m_DocManager;
    IArkivDoc&             m_Doc;
    IArkivDoc::RBXDocType  m_DocType;
    RBX::BaldPtr<QWidget>   m_Viewer;
    bool                    m_IsMoving;
    bool                    m_IsSimulatingDrag;
    QPoint                  m_StartPos;
};



