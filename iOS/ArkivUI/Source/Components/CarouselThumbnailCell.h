//
//  GameThumbnailCell.h
//  ArkivMobile
//
//  Created by Ariel Lichtin on 5/27/14.
//  Copyright (c) 2014 ARKIV. All rights reserved.
//

#import <UIKit/UIKit.h>

@class RBXGameData;
@class ArkivImageView;

@interface CarouselThumbnailCell : UICollectionViewCell

-(void) setGameData:(RBXGameData*)data;

@end
