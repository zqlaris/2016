/*
 *  GameVerbs.h
 *  iOS
 *
 *  Created on 5/18/14.
 *  Copyright 2014 ARKIV. All rights reserved.
 *
 */

#pragma once

#include "v8tree/Verb.h"
using namespace RBX;

class LeaveGameVerb : public RBX::Verb
{
	class ArkivView *arkivView;
	
public :
	LeaveGameVerb(class ArkivView *pArkivView, VerbContainer* container);
	virtual void doIt(RBX::IDataState* dataState);
	
};
