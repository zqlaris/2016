//
//  PlayerThumbnailCell.h
//  ArkivMobile
//
//  Created by Ariel Lichtin on 9/23/14.
//  Copyright (c) 2014 ARKIV. All rights reserved.
//

#import <UIKit/UIKit.h>

#import "ArkivImageView.h"
#import "ArkivData.h"

@interface RBPlayerThumbnailCell : UICollectionViewCell

@property(strong, nonatomic) RBXFriendInfo* friendInfo;

@property(weak, nonatomic) IBOutlet ArkivImageView* avatar;
@property(weak, nonatomic) IBOutlet UILabel* nameLabel;
@property(weak, nonatomic) IBOutlet UIImageView* isOnlineMarker;

@end
