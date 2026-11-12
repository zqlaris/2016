/**
 * ArkivMouseConfig.cpp
 * Copyright (c) 2013 ARKIV Corp. All Rights Reserved.
 */

#include "stdafx.h"
#include "ArkivMouseConfig.h"

#include "util/NavKeys.h"
#include "V8DataModel/InputObject.h"

#include <QLayout>
#include <QLabel>
#include <QComboBox>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QWidget>
#include <QString>
#include <QApplication>
#include <QSettings>

ArkivMouseConfig::ArkivMouseConfig()
    : m_contextMenuConfig(MOUSEBUTTON_RIGHT)
{

}

void ArkivMouseConfig::loadMouseConfig()
{
    QSettings settings;
    settings.beginGroup("Arkiv Studio Mouse Mapping");
    if (!settings.childKeys().isEmpty())
        m_contextMenuConfig = settings.value("contextMenu").toUInt();
    settings.endGroup();
}

void ArkivMouseConfig::saveMouseConfig()
{
    QSettings settings;
    settings.beginGroup("Arkiv Studio Mouse Mapping");
    settings.remove("");
    settings.endGroup();
    
    settings.beginGroup("Arkiv Studio Mouse Mapping");
    settings.setValue("contextMenu", m_contextMenuConfig);
    settings.endGroup();
}

ArkivMouseConfig& ArkivMouseConfig::singleton()
{
    static ArkivMouseConfig* config = new ArkivMouseConfig();
    return *config;
}

bool ArkivMouseConfig::canOpenContextMenu(RBX::InputObject::UserInputType inputType,
                                           RBX::InputObject::UserInputState inputState)
{
    if (m_contextMenuConfig == 0)
        return false;
    
    bool buttonDown = 0;

    if ((m_contextMenuConfig & MOUSEBUTTON_RIGHT) == MOUSEBUTTON_RIGHT &&
        inputState == RBX::InputObject::INPUT_STATE_END && 
        inputType == RBX::InputObject::TYPE_MOUSEBUTTON2)
        buttonDown = true;

    Qt::KeyboardModifiers modifiers = QApplication::queryKeyboardModifiers();

    if (buttonDown &&
        m_contextMenuConfig == MOUSEBUTTON_RIGHT &&
        !(inputState == RBX::InputObject::INPUT_STATE_END && 
          inputType == RBX::InputObject::TYPE_MOUSEBUTTON1) &&
        (modifiers & Qt::ShiftModifier) == 0 &&
        (modifiers & Qt::AltModifier) == 0 &&
        (modifiers & Qt::ControlModifier) == 0
        )
        return true;

    if (buttonDown && m_contextMenuConfig & MOUSEMODIFIER_SHIFT)
    {
        if (modifiers & Qt::ShiftModifier)
            return true;
    }
    if (buttonDown && m_contextMenuConfig & MOUSEMODIFIER_ALT)
    {
        if (modifiers & Qt::AltModifier)
            return true;
    }
    if (buttonDown && m_contextMenuConfig & MOUSEMODIFIER_CONTROL)
    {
        if (modifiers & Qt::ControlModifier)
            return true;
    }

    return false;
}

ArkivMouseConfigWidget::ArkivMouseConfigWidget(QWidget* parent)
    : QWidget(parent)
    , m_contextMenuOption(NULL)
{
    initialize();
}

void ArkivMouseConfigWidget::initialize()
{
    m_contextMenuOverride = ArkivMouseConfig::singleton().contextMenuConfig();

    QLayout* layout = new QVBoxLayout;
    
    QWidget* widget = new QWidget();
    QHBoxLayout* mouseConfigItemLayout = new QHBoxLayout;
    
    QLabel* label = new QLabel("Context Menu");
    label->setContentsMargins(0, 0, 18, 0);
    label->setAlignment(Qt::AlignRight);
    mouseConfigItemLayout->addWidget(label);
    
    m_contextMenuOption = new QComboBox();
    m_contextMenuOption->addItem("Off");
    m_contextMenuOption->addItem("Right Click");
    m_contextMenuOption->addItem("Right Click + Shift");
    m_contextMenuOption->addItem("Right Click + Alt");
    m_contextMenuOption->addItem("Right Click + Ctrl");
    
    updateContextMenuOption();
    
    connect(m_contextMenuOption, SIGNAL(currentIndexChanged(const QString&)),
            this,                     SLOT(contextMenuOptionSelected(const QString&)));
    
    mouseConfigItemLayout->addWidget(m_contextMenuOption);
    widget->setLayout(mouseConfigItemLayout);
    layout->addWidget(widget);
    
    setLayout(layout);
    
}

void ArkivMouseConfigWidget::updateContextMenuOption()
{
    if (m_contextMenuOverride == 0)
    {
        m_contextMenuOption->setCurrentIndex(0);
    }
    else if (m_contextMenuOverride == ArkivMouseConfig::MOUSEBUTTON_RIGHT)
    {
        m_contextMenuOption->setCurrentIndex(1);
    }
    else if (m_contextMenuOverride & ArkivMouseConfig::MOUSEBUTTON_RIGHT &&
             m_contextMenuOverride & ArkivMouseConfig::MOUSEMODIFIER_SHIFT)
    {
        m_contextMenuOption->setCurrentIndex(2);
    }
    else if (m_contextMenuOverride & ArkivMouseConfig::MOUSEBUTTON_RIGHT &&
             m_contextMenuOverride & ArkivMouseConfig::MOUSEMODIFIER_ALT)
    {
        m_contextMenuOption->setCurrentIndex(3);
    }
    else if (m_contextMenuOverride & ArkivMouseConfig::MOUSEBUTTON_RIGHT &&
             m_contextMenuOverride & ArkivMouseConfig::MOUSEMODIFIER_CONTROL)
    {
        m_contextMenuOption->setCurrentIndex(4);
    }
}

void ArkivMouseConfigWidget::contextMenuOptionSelected(const QString& option)
{
    if (option == "Off")
    {
        m_contextMenuOverride = 0;
    }
    if (option == "Right Click")
    {
        m_contextMenuOverride = ArkivMouseConfig::MOUSEBUTTON_RIGHT;
    }
    else if (option == "Right Click + Shift")
    {
        m_contextMenuOverride = ArkivMouseConfig::MOUSEBUTTON_RIGHT |
                                ArkivMouseConfig::MOUSEMODIFIER_SHIFT;
    }
    else if (option == "Right Click + Alt")
    {
        m_contextMenuOverride = ArkivMouseConfig::MOUSEBUTTON_RIGHT |
                                ArkivMouseConfig::MOUSEMODIFIER_ALT;
    }
    else if (option == "Right Click + Ctrl")
    {
        m_contextMenuOverride = ArkivMouseConfig::MOUSEBUTTON_RIGHT |
                                ArkivMouseConfig::MOUSEMODIFIER_CONTROL;
    }
    
    Q_EMIT(dataChanged());
}

void ArkivMouseConfigWidget::accept()
{
    ArkivMouseConfig::singleton().setContextMenuConfig(m_contextMenuOverride);
    ArkivMouseConfig::singleton().saveMouseConfig();
}

void ArkivMouseConfigWidget::cancel()
{
    m_contextMenuOverride = ArkivMouseConfig::singleton().contextMenuConfig();
    updateContextMenuOption();
}

void ArkivMouseConfigWidget::restoreAllDefaults()
{
	m_contextMenuOverride = ArkivMouseConfig::MOUSEBUTTON_RIGHT;
    updateContextMenuOption();
    Q_EMIT(dataChanged());
}

