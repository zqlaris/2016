//
//  GameSearchResultCell.h
//  ArkivMobile
//
//  Created by Ariel Lichtin on 6/10/14.
//  Copyright (c) 2014 ARKIV. All rights reserved.
//

#import <UIKit/UIKit.h>

#import "ArkivData.h"

@interface GameSearchResultCell : UICollectionViewCell

@property(strong, nonatomic) RBXGameData* gameData;

+(CGSize) getCellSize;
+(NSString*) getNibName;

@end
