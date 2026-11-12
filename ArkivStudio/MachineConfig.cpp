/**
 * MachineConfig.cpp
 * Copyright (c) 2013 ARKIV Corp. All Rights Reserved.
 */

#include "stdafx.h"
#include "MachineConfig.h"

// Arkiv Headers
#include "MachineConfiguration.h"

// Arkiv Studio Headers
#include "ArkivSettings.h"

MachineConfig* MachineConfig::machineConfig = NULL;
////////////////////////////////////////////////////////////////////////////////////

void MachineConfig::PostMachineConfiguration(bool authSuccess)
{
	if(authSuccess)
	{
		disconnect(&AuthenticationHelper::Instance(), SIGNAL(authenticationDone(bool)), machineConfig, SLOT(PostMachineConfiguration(bool)));

        ArkivSettings settings;
        int lastGfxMode = settings.contains("lastGFXMode") ? settings.value("lastGFXMode").toInt() : 0;

		RBX::postMachineConfiguration(ArkivSettings::getBaseURL().toLocal8Bit().constData(), lastGfxMode);
	}
}
/////////////////////////////////////////////////////////////////////////////////
