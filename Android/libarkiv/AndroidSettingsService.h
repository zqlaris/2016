//
//  Copyright (c) 2012 ARKIV. All rights reserved.
//

#ifndef __ArkivMobile__AndroidSettingsService__
#define __ArkivMobile__AndroidSettingsService__

#include "v8datamodel/FastLogSettings.h"
#include "util/Statistics.h"

#include <iostream>



class AndroidSettingsService : public RBX::FastLogJSON
{
    
public:
    START_DATA_MAP(AndroidSettingsService)
//    DECLARE_DATA_INT(iPadMinimumVersion)
    END_DATA_MAP();
};

#endif /* __ArkivMobile__AndroidSettingsService__ */
