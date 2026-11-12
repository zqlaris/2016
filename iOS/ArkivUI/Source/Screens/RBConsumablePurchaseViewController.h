//
//  RBPurchaseConsumableViewController.h
//  ArkivMobile
//
//  Created by alichtin on 10/1/14.
//  Copyright (c) 2014 ARKIV. All rights reserved.
//

#import <UIKit/UIKit.h>
#import "ArkivData.h"
#include "RBModalPopUpViewController.h"

@interface RBConsumablePurchaseViewController : RBModalPopUpViewController

@property(strong, nonatomic) NSString* gameTitle;

@property(strong, nonatomic) RBXGameGear* gearData;
@property(strong, nonatomic) RBXGamePass* passData;

@end
