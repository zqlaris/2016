/**
 * ArkivSavingStateDialog.h
 * Copyright (c) 2013 ARKIV Corp. All Rights Reserved.
 */

#pragma once

// Qt Headers
#include <QDialog>
#include <QSettings>

template <typename T>
class ArkivSavingStateDialog : public T
{
public:
	ArkivSavingStateDialog(QWidget* parent, const QString geometrySettingName)
		: T(parent, Qt::WindowTitleHint | Qt::WindowSystemMenuHint)
		, m_geometrySettingName(geometrySettingName)
	{
		// restore settings
		QSettings settings;
        QDialog::restoreGeometry(settings.value(m_geometrySettingName).toByteArray());
	}

protected:
	QString m_geometrySettingName;
	virtual ~ArkivSavingStateDialog()
	{
		QSettings settings;
		settings.setValue(m_geometrySettingName, QDialog::saveGeometry());
	}

};