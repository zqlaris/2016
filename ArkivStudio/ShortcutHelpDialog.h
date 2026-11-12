/**
 * ShortcutHelpDialog.h
 * Copyright (c) 2013 ARKIV Corp. All Rights Reserved.
 */

#pragma once

// Qt Headers
#include <QDialog>

// Arkiv Headers
#include "rbx/BaldPtr.h"

class QTreeWidget;
class ArkivMainWindow;

/**
 * Dialog that displays all the shortcut key sequences for actions in the main window.
 *  Also displays the actions' icon and statustip text.
 *  The dialog does not delete on close.
 */
class ShortcutHelpDialog : public QDialog
{
    public:

        ShortcutHelpDialog(ArkivMainWindow& MainWindow);
        virtual ~ShortcutHelpDialog();

    private:

        void initialize();
        void populate();

        RBX::BaldPtr<QTreeWidget>   mTree;
        ArkivMainWindow&           mMainWindow;
};