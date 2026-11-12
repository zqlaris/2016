/**
 * ArkivInputConfigDialog.h
 * Copyright (c) 2013 ARKIV Corp. All Rights Reserved.
 */

#pragma once

#include <QAction>
#include <QDialog>
#include <QString>
#include <QWidget>

#include "rbx/BaldPtr.h"

class ArkivMainWindow;
class QEvent;
class QTreeView;
class QDialogButtonBox;
class QAbstractButton;
class ArkivKeyboardConfigWidget;
class ArkivMouseConfigWidget;

//
// A dialog for configuring mouse and keyboard shortcuts for all actions
// under the ArkivMainWindow.
//
class ArkivInputConfigDialog : public QDialog
{
    Q_OBJECT
    
public:

    ArkivInputConfigDialog(ArkivMainWindow& MainWindow);
    virtual ~ArkivInputConfigDialog();
    
private Q_SLOTS:
    void accept();
    void cancel();
    void clicked(QAbstractButton* button);
    
    void dataChanged();
    
private:
    virtual void closeEvent(QCloseEvent* event);
    void restoreAllDefaults();
    void initialize();

    QDialogButtonBox*           m_dialogButtonBox;
    ArkivKeyboardConfigWidget* m_keyboardConfigWidget;
    ArkivMouseConfigWidget*    m_mouseConfigWidget;
    ArkivMainWindow&           m_mainWindow;
    bool                        m_dataChanged;
};

