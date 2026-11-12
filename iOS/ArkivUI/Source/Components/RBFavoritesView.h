//
//  RBFavoritesView
//  ArkivMobile
//
//  Created by Ariel Lichtin on 10/1/14.
//  Copyright (c) 2014 ARKIV. All rights reserved.
//

#import <UIKit/UIKit.h>
#import "ArkivData.h"

@interface RBFavoritesView : UIView

- (void) setFavoritesForGame:(RBXGameData*)gameData;
- (void) setFavoritesForPass:(RBXGamePass*)gamePass;
- (void) setFavoritesForGear:(RBXGameGear*)gameGear;

@end
