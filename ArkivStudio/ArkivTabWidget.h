/**
 * ArkivTabWidget.h
 * Copyright (c) 2013 ARKIV Corp. All Rights Reserved.
 */

#pragma once

// Qt Headers
#include <QTabWidget>

class ArkivTabWidget : public QTabWidget
{
    public:

        ArkivTabWidget(QWidget* parent)
            : QTabWidget(parent)
        {
        }

        QTabBar& getTabBar() { return *tabBar(); }
};


