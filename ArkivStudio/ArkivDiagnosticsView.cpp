/**
 * ArkivDiagnosticsView.cpp
 * Copyright (c) 2013 ARKIV Corp. All Rights Reserved.
 */

#include "stdafx.h"
#include "ArkivDiagnosticsView.h"

// Qt Headers
#include <QTimer>
#include <QHeaderView>

// Arkiv Headers
#include "v8datamodel/DataModel.h"
#include "v8datamodel/Stats.h"
#include "util/Profiling.h"

static const int UpdateInterval = 1000 / 5;

ArkivDiagnosticsViewItem::ArkivDiagnosticsViewItem(boost::shared_ptr<RBX::Stats::Item> pItem)
: m_pItem(pItem)
{
	//RBX::DataModel::LegacyLock lock(getTreeWidget()->dataModel(), RBX::DataModelJob::Read);
	setText(0, m_pItem->getName().c_str());
	setText(1, m_pItem->getStringValue().c_str());

	m_pItem->visitChildren(boost::bind(&ArkivDiagnosticsViewItem::onChildAdded, this, _1));
	m_childAddedConnection = m_pItem->getOrCreateChildAddedSignal()->connect(boost::bind(&ArkivDiagnosticsViewItem::onChildAdded, this, _1));
	m_childRemovedConnection = m_pItem->getOrCreateChildRemovedSignal()->connect(boost::bind(&ArkivDiagnosticsViewItem::onChildRemoved, this, _1));
}

ArkivDiagnosticsView *ArkivDiagnosticsViewItem::getTreeWidget()
{	return dynamic_cast<ArkivDiagnosticsView *>(treeWidget()); }

ArkivDiagnosticsViewItem* ArkivDiagnosticsViewItem::getItemParent()
{	return dynamic_cast<ArkivDiagnosticsViewItem*>(parent()); }

void ArkivDiagnosticsViewItem::onChildAdded(boost::shared_ptr<RBX::Instance> child)
{
	if(!child)
		return;

	boost::shared_ptr<RBX::Stats::Item> item = RBX::shared_dynamic_cast<RBX::Stats::Item>(child);
	if (!item)
		return;

	ArkivDiagnosticsViewItem* pViewItem = new ArkivDiagnosticsViewItem(item);
	if(pViewItem)
	{
		addChild(pViewItem);
	}
}

void ArkivDiagnosticsViewItem::onChildRemoved(boost::shared_ptr<RBX::Instance> inst)
{
	if(!inst)
		return;

	boost::shared_ptr<RBX::Stats::Item> item = RBX::shared_dynamic_cast<RBX::Stats::Item>(inst);
	if (!item)
		return;

	ArkivDiagnosticsViewItem* pItemToDelete = NULL;
	for(int ii=0; ii<childCount(); ii++)
	{
		ArkivDiagnosticsViewItem* pViewItem = dynamic_cast<ArkivDiagnosticsViewItem*>(child(ii));
		if(pViewItem->getItem() == item)
		{
			pItemToDelete = dynamic_cast<ArkivDiagnosticsViewItem*>(takeChild(ii));
			break;
		}
	}

	if(pItemToDelete)
	{
		delete pItemToDelete;
		pItemToDelete = NULL;
	}

	if (!isExpanded() && childCount() > 0)					
		setChildIndicatorPolicy(QTreeWidgetItem::DontShowIndicatorWhenChildless);
}

void ArkivDiagnosticsViewItem::updateValues()
{
	setText(1, m_pItem->getStringValue().c_str());

	for(int ii=0; ii<childCount(); ii++)
	{
		ArkivDiagnosticsViewItem* pViewItem = dynamic_cast<ArkivDiagnosticsViewItem*>(child(ii));
		if(pViewItem)
			pViewItem->updateValues();
	}
}

ArkivDiagnosticsView::ArkivDiagnosticsView(bool createdFromIDEDoc)
: m_pTimer(new QTimer(this))
, m_bPreviousProfiling(false)
, m_bIsCreatedFromIDEDoc(createdFromIDEDoc)
{
	setUniformRowHeights(true);
	setEditTriggers(QAbstractItemView::NoEditTriggers);
	setAlternatingRowColors(true);

	setColumnCount(2);
	QStringList headerLabels;
	headerLabels << "Name" << "Value";
	setHeaderLabels(headerLabels);

	header()->setDefaultSectionSize(125);

    m_pTimer->setInterval(UpdateInterval);
	connect(m_pTimer, SIGNAL(timeout()), this, SLOT(updateValues()));
}

ArkivDiagnosticsView::~ArkivDiagnosticsView()
{
	// turn off profiling
	if (!m_bIsCreatedFromIDEDoc)
		RBX::Profiling::setEnabled(false);

//	setDataModel(shared_ptr<RBX::DataModel>());
}

void ArkivDiagnosticsView::setDataModel(boost::shared_ptr<RBX::DataModel> pDataModel)
{
	if(m_pDataModel == pDataModel)
		return;

	m_pTimer->stop();

	if (m_pDataModel)
	{
		RBX::DataModel::LegacyLock lock(m_pDataModel, RBX::DataModelJob::Write);
		m_childAddedConnection.disconnect();
		m_childRemovedConnection.disconnect();
		clear();
	}

	m_pStats.reset();
	m_pDataModel = pDataModel;

	if (m_pDataModel)
	{
		RBX::DataModel::LegacyLock lock(m_pDataModel, RBX::DataModelJob::Write);
		m_pStats = shared_from(RBX::ServiceProvider::create<RBX::Stats::StatsService>(m_pDataModel.get()));
		m_pTimer->start();
		
		m_pStats->visitChildren(boost::bind(&ArkivDiagnosticsView::onChildAdded, this, _1));
		m_childAddedConnection = m_pStats->getOrCreateChildAddedSignal()->connect(boost::bind(&ArkivDiagnosticsView::onChildAdded, this, _1));
		m_childRemovedConnection = m_pStats->getOrCreateChildRemovedSignal()->connect(boost::bind(&ArkivDiagnosticsView::onChildRemoved, this, _1));
	} 
}

boost::shared_ptr<RBX::DataModel> ArkivDiagnosticsView::dataModel()
{	return m_pDataModel; }

void ArkivDiagnosticsView::updateValues()
{
    // if the window is hidden, stop the update timer
    if ( !isVisible() )
    {
        m_pTimer->stop();
        return;
    }

	for(int ii=0; ii<topLevelItemCount(); ii++)
	{
		ArkivDiagnosticsViewItem* pViewItem = dynamic_cast<ArkivDiagnosticsViewItem*>(topLevelItem(ii));
		if(pViewItem)
			pViewItem->updateValues();
	}
}

void ArkivDiagnosticsView::setVisible(bool visible)
{
	if(visible)
	{
		m_bPreviousProfiling = RBX::Profiling::isEnabled();
		if(!m_bPreviousProfiling)
			RBX::Profiling::setEnabled(true);

		m_pTimer->start();
	}
	else
	{
		RBX::Profiling::setEnabled(m_bPreviousProfiling);
		m_pTimer->stop();
	}
	QTreeWidget::setVisible(visible);
}

void ArkivDiagnosticsView::onChildAdded(boost::shared_ptr<RBX::Instance> child)
{
	if(!child)
		return;

	boost::shared_ptr<RBX::Stats::Item> item = RBX::shared_dynamic_cast<RBX::Stats::Item>(child);
	if (!item)
		return;
	
	ArkivDiagnosticsViewItem* pViewItem = new ArkivDiagnosticsViewItem(item);
	if(pViewItem)
	{
		addTopLevelItem(pViewItem);
	}
}

void ArkivDiagnosticsView::onChildRemoved(boost::shared_ptr<RBX::Instance> child)
{
	if(!child)
		return;

	boost::shared_ptr<RBX::Stats::Item> item = RBX::shared_dynamic_cast<RBX::Stats::Item>(child);
	if (!item)
		return;

	ArkivDiagnosticsViewItem* pItemToDelete = NULL;
	for(int ii=0; ii<topLevelItemCount(); ii++)
	{
		ArkivDiagnosticsViewItem* pViewItem = dynamic_cast<ArkivDiagnosticsViewItem*>(topLevelItem(ii));
		if(pViewItem->getItem() == item)
		{
			pItemToDelete = dynamic_cast<ArkivDiagnosticsViewItem*>(takeTopLevelItem(ii));
			break;
		}
	}

	if(pItemToDelete)
	{
		delete pItemToDelete;
		pItemToDelete = NULL;
	}
}



