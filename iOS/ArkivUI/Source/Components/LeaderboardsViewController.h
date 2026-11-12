//
//  LeaderboardsViewController.h
//  ArkivMobile
//
//  Created by Ariel Lichtin on 6/16/14.
//  Copyright (c) 2014 ARKIV. All rights reserved.
//

#import <UIKit/UIKit.h>
#import "ArkivData.h"

@interface LeaderboardsViewController : UIViewController

@property (nonatomic) RBXLeaderboardsTimeFilter timeFilter;
@property (strong, nonatomic) NSNumber* distributorID;

// Callback
@property (copy, nonatomic) void (^onLeaderboardsLoaded)(BOOL hasLeaderboards);

- (void) updateLeaderboards;

@end
