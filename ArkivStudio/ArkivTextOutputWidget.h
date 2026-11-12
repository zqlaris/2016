/**
 * ArkivTextOutputWidget.h
 * Copyright (c) 2013 ARKIV Corp. All Rights Reserved.
 */

#pragma once

//this will make sure that we can use qt with boost (else moc compiler errors)
#ifndef QT_NO_KEYWORDS
    #define QT_NO_KEYWORDS
#endif

// Qt Headers
#include <QPlainTextEdit>
#include <QMenu>

// Arkiv Headers
#include "rbx/signal.h"
#include "util/standardout.h"
#include "reflection/Property.h"

class QMenu;
class QAction;

// Override the plain text edit so that other features can be added to it.
class ArkivTextOutputWidget : public QPlainTextEdit
{
    Q_OBJECT

    public:

        ArkivTextOutputWidget(QWidget* parent);
        virtual ~ArkivTextOutputWidget();

		virtual QSize sizeHint() const;

    protected:

        virtual void contextMenuEvent(QContextMenuEvent *event);
        virtual bool event(QEvent* evt);

		virtual void resizeEvent(QResizeEvent *e);

		bool isScrollOnBottom();

    protected Q_SLOTS:

        void appendOutputText(const QString message,RBX::MessageType type);

    private:

        void onPropertyChanged(const RBX::Reflection::PropertyDescriptor* pDescriptor);

        rbx::signals::scoped_connection     m_PropertyChangedConnection;
        QTextCharFormat                     m_TextFormats[RBX::MESSAGE_TYPE_MAX];
};
