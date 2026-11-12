/**
 * ArkivBasicDoc.cpp
 * Copyright (c) 2013 ARKIV Corp. All Rights Reserved.
 */

#include "stdafx.h"
#include "ArkivBasicDoc.h"

// Qt Headers
#include <QString>

// Arkiv Studio Headers
#include "IExternalHandler.h"
#include "UpdateUIManager.h"
#include "ArkivDocManager.h"

ArkivBasicDoc::ArkivBasicDoc()
    : m_bActive(false)
{
}

ArkivBasicDoc::~ArkivBasicDoc()
{
}

void ArkivBasicDoc::addExternalHandler(IExternalHandler* extHandler)
{
	if(extHandler == NULL) 
		return;

	if(extHandler->handlerId().isEmpty())
		return;

	m_handlersMap[extHandler->handlerId()] = extHandler;
}

void ArkivBasicDoc::removeExternalHandler(const QString &handlerId)
{
	if(handlerId.isEmpty())
		return;

	m_handlersMap.erase(handlerId);
}

IExternalHandler* ArkivBasicDoc::getExternalHandler(const QString &handlerId)
{
	return m_handlersMap[handlerId];
}

bool ArkivBasicDoc::handleAction( const QString &actionID, bool isChecked /*= true*/ )
{
	// Try to see if inherited class handles this action
	return doHandleAction(actionID, isChecked);
}

/** do not override **/
bool ArkivBasicDoc::close()
{
	if (doClose())
	{
		ArkivDocManager::Instance().updateWindowMenu();
		return true;
	}
	return false;
}
