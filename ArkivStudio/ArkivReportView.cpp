/**
 * ArkivReportView.cpp
 * Copyright (c) 2013 ARKIV Corp. All Rights Reserved.
 */

#include "stdafx.h"
#include "ArkivReportView.h"

// Qt Headers
#include <QPainter>

#ifdef Q_WS_MAC
    #define CATEGORY_ITEM_PADDING	7
    #define CATEGORY_ITEM_INDENT	24
#else
    #define CATEGORY_ITEM_PADDING	3
    #define CATEGORY_ITEM_INDENT    20
#endif

ArkivCategoryItem::ArkivCategoryItem()
{
	setFlags(Qt::ItemIsEnabled);

	QFont boldFont(font(0));
	boldFont.setBold(true);
	boldFont.setPointSize(9);
	setFont(0, boldFont);

	setTextAlignment(0, Qt::AlignJustify | Qt::AlignVCenter);
}

void ArkivCategoryItemDelegate::initStyleOption(QStyleOptionViewItem *option, const QModelIndex &index) const
{
	QStyledItemDelegate::initStyleOption(option, index);
	ArkivReportView *pTree = dynamic_cast<ArkivReportView*>(parent());
	if(pTree->isCategoryItem(index)) 
	{
		QRect rect = option->rect;
		QRect newRect(rect.left()+CATEGORY_ITEM_INDENT, rect.top(), rect.width(), rect.height()+CATEGORY_ITEM_PADDING);
		option->rect = newRect;
	}
}

QSize ArkivCategoryItemDelegate::sizeHint(const QStyleOptionViewItem &option,
											  const QModelIndex &index) const
{
	QSize sz = QStyledItemDelegate::sizeHint(option, index);
	ArkivReportView *pTree = dynamic_cast<ArkivReportView*>(parent());
	if(pTree->isCategoryItem(index)) 
	{		
		sz.setWidth(sz.width() - CATEGORY_ITEM_INDENT);
		sz.setHeight(sz.height() + CATEGORY_ITEM_PADDING);
	}
	return sz;
}

ArkivReportView::ArkivReportView()
{
	setEditTriggers(QAbstractItemView::NoEditTriggers);
	setAlternatingRowColors(true);
	setIndentation(0);

	ArkivCategoryItemDelegate *pItemDelegate = new ArkivCategoryItemDelegate(this);
	setItemDelegate(pItemDelegate);
}

ArkivReportView::~ArkivReportView()
{}

void ArkivReportView::addCategoryItem(ArkivCategoryItem* pItem)
{
	if(!pItem)
		return;

	addTopLevelItem(pItem);
	setFirstItemColumnSpanned(pItem, true);
	
	QSize sz = pItem->sizeHint(0);
	sz.scale(sz.width(), sz.height()*2, Qt::KeepAspectRatio);
	pItem->setSizeHint(0, sz);
}

ArkivCategoryItem* ArkivReportView::findCategoryItem(const QString& category)
{
	ArkivCategoryItem* pCategoryItem = NULL;
	QList<QTreeWidgetItem*> items = findItems(category, Qt::MatchExactly);
	if(items.count())
		pCategoryItem = dynamic_cast<ArkivCategoryItem*>(items[0]);
	
	return pCategoryItem;
}

bool ArkivReportView::addToCategory(const QString& category, QTreeWidgetItem* pItem)
{
	if(!pItem)
		return false;

	ArkivCategoryItem* pCategory = findCategoryItem(category);
	if(pCategory)
	{
		pCategory->addChild(pItem);
		return true;
	}

	return false;
}

void ArkivReportView::drawRow(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
	QStyleOptionViewItemV3 opt = option;
	
	ArkivCategoryItem* pCategoryItem = dynamic_cast<ArkivCategoryItem*>(itemFromIndex(index));
	if(pCategoryItem)
	{
		const QColor c = option.palette.color(QPalette::Dark);
        painter->fillRect(option.rect, c);
        opt.palette.setColor(QPalette::AlternateBase, c);
	}

	QTreeWidget::drawRow(painter, opt, index);
}

void ArkivReportView::drawBranches(QPainter * painter, const QRect & rect, const QModelIndex & index ) const
{
	ArkivCategoryItem* pCategoryItem = dynamic_cast<ArkivCategoryItem*>(itemFromIndex(index));
	if(pCategoryItem)
	{
		QRect primitive(rect.left(), rect.top(), indentation()+CATEGORY_ITEM_INDENT, rect.height()+CATEGORY_ITEM_PADDING);

		QStyleOptionViewItemV4 opt = viewOptions();
		QStyle::State extraFlags = QStyle::State_None;
		if (isEnabled())
			extraFlags |= QStyle::State_Enabled;
		if (window()->isActiveWindow())
			extraFlags |= QStyle::State_Active;
		QPoint oldBO = painter->brushOrigin();
		if (verticalScrollMode() == QAbstractItemView::ScrollPerPixel)
			painter->setBrushOrigin(QPoint(0, verticalOffset()));

		if(alternatingRowColors())
		{
			opt.features |= QStyleOptionViewItemV4::Alternate;
		}

		if(selectionModel()->isSelected(index))
			extraFlags |= QStyle::State_Selected;

        opt.rect = primitive;
		opt.state = QStyle::State_Item | extraFlags | QStyle::State_Children
					| (pCategoryItem->isExpanded() ? QStyle::State_Open : QStyle::State_None);

		style()->drawPrimitive(QStyle::PE_IndicatorBranch, &opt, painter, this);
		
		painter->setBrushOrigin(oldBO);
	}
	else
	{
		QTreeWidget::drawBranches(painter, rect, index );
	}
}

bool ArkivReportView::isCategoryItem(const QModelIndex &index)
{
	ArkivCategoryItem* pCategoryItem = dynamic_cast<ArkivCategoryItem*>(itemFromIndex(index));
	return (pCategoryItem != NULL);
}

