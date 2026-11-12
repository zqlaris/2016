//
//  LeaderboardCell.h
//  ArkivMobile
//
//  Created by Ariel Lichtin on 6/6/14.
//  Copyright (c) 2014 ARKIV. All rights reserved.
//

#import <UIKit/UIKit.h>
#import "ArkivData.h"
#import "ArkivImageView.h"

@interface LeaderboardCell : UITableViewCell

@property (strong, nonatomic) IBOutlet UILabel* rankLabel;
@property (strong, nonatomic) IBOutlet UILabel *titleLabel;
@property (strong, nonatomic) IBOutlet UILabel *subtitleLabel;
@property (strong, nonatomic) IBOutlet UILabel *pointsLabel;
@property (strong, nonatomic) IBOutlet ArkivImageView *avatar;

- (void) showPlayerInfo:(RBXLeaderboardEntry*)data;
- (void) showClanInfo:(RBXLeaderboardEntry*)data;

@end
