//
//  RBVotesView.h
//  ArkivMobile
//
//  Created by Ariel Lichtin on 10/1/14.
//  Copyright (c) 2014 ARKIV. All rights reserved.
//

#import <UIKit/UIKit.h>
#import "ArkivData.h"

@interface RBVotesView : UIView

- (void) setVotesForGame:(RBXGameData*)gameData;
- (void) setVotesForPass:(RBXGamePass*)gamePass;

@end
