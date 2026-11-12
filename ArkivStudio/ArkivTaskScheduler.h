/**
 * ArkivTaskScheduler.h
 * Copyright (c) 2013 ARKIV Corp. All Rights Reserved.
 */

#pragma once

// Arkiv Headers
#include "rbx/TaskScheduler.h"

// Arkiv Studio Headers
#include "ArkivReportView.h"

class TSJobItem;

class ArbiterItem: public ArkivCategoryItem
{
public:
	ArbiterItem() {}
	TSJobItem* getOrCreateTSJobItem(boost::shared_ptr<const RBX::TaskScheduler::Job> pJob);
};

class TSJobItem: public QTreeWidgetItem
{
public:
	TSJobItem(ArbiterItem* pParentItem, boost::shared_ptr<const RBX::TaskScheduler::Job> pJob);

	boost::shared_ptr<const RBX::TaskScheduler::Job> getJob() { return m_pJob; }
	void updateValues();

private:
	boost::shared_ptr<const RBX::TaskScheduler::Job>	m_pJob;
};

class ArkivTaskScheduler : public ArkivReportView
{
	Q_OBJECT
public:
	ArkivTaskScheduler(); 
	virtual ~ArkivTaskScheduler();

public Q_SLOTS:
	void setVisible(bool visible);

private Q_SLOTS:
	void updateValues();

private:
	typedef std::vector<boost::shared_ptr<const RBX::TaskScheduler::Job> > Jobs;
	typedef std::map<boost::shared_ptr<RBX::TaskScheduler::Arbiter>, ArbiterItem*> ArbiterItemsMap;
	typedef std::set<TSJobItem*> TSJobItemCollection;

	ArbiterItem* getOrCreateArbiterItem(boost::shared_ptr<RBX::TaskScheduler::Arbiter> pArbiter);
	void syncTSJobItems(const TSJobItemCollection &currentTaskSchedulerItems);

	ArbiterItemsMap				 m_arbiterMap;
	TSJobItemCollection          m_TSJobItems;

	QTimer						*m_pTimer;
};


