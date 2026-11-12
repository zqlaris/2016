//
//  RBMessageComposeScreenController.h
//  ArkivMobile
//
//  Created by alichtin on 9/18/14.
//  Copyright (c) 2014 ARKIV. All rights reserved.
//

#import <UIKit/UIKit.h>
#import "ArkivData.h"

@interface RBMessageComposeScreenController : UIViewController

- (void) replyToMessage:(RBXMessageInfo*)message;

- (void) sendMessageToUser:(NSNumber*)userID name:(NSString*)userName;

@end
