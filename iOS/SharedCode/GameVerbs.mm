/*
 *  GameVerbs.mm
 *  iOS
 *
 *  Created on 5/19/14
 *  Copyright 2014 ARKIV. All rights reserved.
 *
 */

#import "PlaceLauncher.h"

#include "GameVerbs.h"
#include "ArkivView.h"

#include "v8datamodel/GameBasicSettings.h"

LeaveGameVerb::LeaveGameVerb(ArkivView *pArkivView, VerbContainer* container) : 
	Verb(container, "Exit")
	,arkivView(pArkivView)
{
}

void LeaveGameVerb::doIt(RBX::IDataState* dataState)
{
	[[PlaceLauncher sharedInstance] leaveGame:YES];
    
    RBX::GlobalBasicSettings::singleton()->saveState();
}
