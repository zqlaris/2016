//
//  GamePreviewScreenController.h
//  ArkivMobile
//
//  Created by alichtin on 5/30/14.
//  Copyright (c) 2014 ARKIV. All rights reserved.
//

#import <UIKit/UIKit.h>
#import "ArkivData.h"

@interface GamePreviewScreenController : UIViewController<UITextViewDelegate, UIScrollViewDelegate>

@property (strong, nonatomic) RBXGameData* gameData;

@end
