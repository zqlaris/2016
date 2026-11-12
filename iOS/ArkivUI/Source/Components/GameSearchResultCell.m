//
//  GameSearchResultCell.m
//  ArkivMobile
//
//  Created by Ariel Lichtin on 6/10/14.
//  Copyright (c) 2014 ARKIV. All rights reserved.
//

#import "GameSearchResultCell.h"
#import "ArkivImageView.h"
#import "ArkivTheme.h"
#import "ArkivInfo.h"
#import "RBActivityIndicatorView.h"

@implementation GameSearchResultCell
{
    IBOutlet ArkivImageView* _thumbnail;
    IBOutlet UILabel *_title;
    IBOutlet RBActivityIndicatorView *_activityIndicator;
}

+(CGSize)getCellSize
{
    return [ArkivInfo thisDeviceIsATablet] ? CGSizeMake(160, 220) : CGSizeMake(140, 215);
}
+(NSString*)getNibName
{
    return [ArkivInfo thisDeviceIsATablet] ? @"GameSearchResultCell" : @"GameSearchResultCell_iPhone";
}

- (void)awakeFromNib
{
	[ArkivTheme applyToGameSearchToolbarCell:_title];
    _thumbnail.animateInOptions = RBXImageViewAnimateInIfNotCached;
    _thumbnail.layer.cornerRadius = 5;
    _thumbnail.layer.masksToBounds = YES;
    _thumbnail.layer.borderColor = [UIColor whiteColor].CGColor;
    _thumbnail.layer.borderWidth = 1;
    
    _title.hidden = YES;
    _activityIndicator.hidden = NO;
}

- (void)setGameData:(RBXGameData *)gameData
{
    if (gameData)
    {
        _gameData = gameData;
        _title.text = gameData.title;
        _title.hidden = NO;
        
        [_activityIndicator startAnimating];
        [_thumbnail loadThumbnailForGame:gameData withSize:[ArkivTheme sizeGameCoverSquare] completion:^{
            dispatch_async(dispatch_get_main_queue(), ^
           {
               [_activityIndicator stopAnimating];
               _thumbnail.hidden = NO;
           });
        }];
    }
    else
    {
        _title.hidden = YES;
        _thumbnail.hidden = YES;
        [_activityIndicator startAnimating];
    }
    
}

@end
