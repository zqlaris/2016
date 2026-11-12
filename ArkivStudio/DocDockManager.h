/**
 * DocDockWidget.h
 * Copyright (c) 2013 ARKIV Corp. All Rights Reserved.
 */

#pragma once

// Qt Headers
#include <QDockWidget>
#include <QMap>

// Arkiv Headers
#include "RBX/BaldPtr.h"

// Arkiv Studio Headers
#include "IArkivDoc.h"

class ArkivMainWindow;
class DocDockWidget;

class DocDockManager : public QObject
{
    Q_OBJECT

    public:

        DocDockManager(ArkivMainWindow& mainWindow);
        virtual ~DocDockManager();

        void addDoc(IArkivDoc& doc);
        bool removeDoc(IArkivDoc& doc);
        bool renameDoc(IArkivDoc& doc,const QString& text,const QString& tooltip);

        bool setCurrentDoc(IArkivDoc& doc);
        IArkivDoc* getCurrentDoc() const;

        void startDrag(IArkivDoc& doc);

    Q_SIGNALS:

        void attachTab(IArkivDoc& doc);

    private:

        typedef QMap< RBX::BaldPtr<IArkivDoc>,RBX::BaldPtr<DocDockWidget> > tDocDockMap;

        ArkivMainWindow&   m_MainWindow;
        tDocDockMap         m_Docs;
};

