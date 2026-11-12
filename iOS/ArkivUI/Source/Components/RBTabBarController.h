//
//  RBTabBarController.h
//  ArkivMobile
//
//  Created by Ashish Jain on 12/8/15.
//  Copyright © 2015 ARKIV. All rights reserved.
//

#import <UIKit/UIKit.h>
#import "RBXEventReporter.h"

@interface RBTabBarController : UITabBarController

-(RBXAnalyticsCustomData) getCurrentTabContext;

@end
