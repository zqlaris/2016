/**
 * ArkivReportView.h
 * Copyright (c) 2013 ARKIV Corp. All Rights Reserved.
 */

#pragma once

// Qt Headers
#include <QTreeWidget>
#include <QStyledItemDelegate>

class ArkivCategoryItemDelegate : public QStyledItemDelegate
{
public:
	ArkivCategoryItemDelegate(QWidget *parent = 0) : QStyledItemDelegate(parent) {}

	QSize sizeHint(const QStyleOptionViewItem &option, const QModelIndex &index) const;
protected:
	void initStyleOption(QStyleOptionViewItem *option, const QModelIndex &index) const;
};

class ArkivCategoryItem: public QTreeWidgetItem
{
public:
	ArkivCategoryItem();
};

class ArkivReportView : public QTreeWidget
{
public:
	ArkivReportView(); 
	virtual ~ArkivReportView();

	void addCategoryItem(ArkivCategoryItem* pItem);
	bool isCategoryItem(const QModelIndex &index);
	ArkivCategoryItem* findCategoryItem(const QString& category);
	bool addToCategory(const QString& category, QTreeWidgetItem* pItem);
		
private:
	/*override*/void drawRow(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const;
	/*override*/void drawBranches(QPainter * painter, const QRect & rect, const QModelIndex & index ) const;
};


