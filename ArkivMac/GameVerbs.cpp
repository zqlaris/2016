/*
 *  GameVerbs.cpp
 *  MacClient
 *
 *  Created by Tony on 2/2/11.
 *  Copyright 2011 __MyCompanyName__. All rights reserved.
 *
 */

#include "GameVerbs.h"
#include "ArkivView.h"

LeaveGameVerb::LeaveGameVerb(ArkivView *pArkivView, VerbContainer* container) : 
	Verb(container, "Exit")
	,arkivView(pArkivView)
{
}

void LeaveGameVerb::doIt(RBX::IDataState* dataState)
{
	if (arkivView)
	{
		arkivView->leaveGame();
	}
}

ShutdownClientVerb::ShutdownClientVerb(ArkivView *pArkivView, VerbContainer* container) :
	Verb( container, "ShutdownClient")
	,arkivView(pArkivView)
{
}

void ShutdownClientVerb::doIt(RBX::IDataState* dataState)
{
	if (arkivView)
	{
		arkivView->shutdownClient();
	}
}

ToggleFullscreenVerb::ToggleFullscreenVerb(ArkivView *pArkivView, VerbContainer* container, VideoControl* videoControl) :
	Verb(container, "ToggleFullScreen")
	, videoControl(videoControl)
	,arkivView(pArkivView)
{}

void ToggleFullscreenVerb::doIt(RBX::IDataState* dataState)
{
	if (arkivView)
	{
		arkivView->toggleFullScreen();
	}
}

bool ToggleFullscreenVerb::isEnabled() const
{
	return true; 
}
