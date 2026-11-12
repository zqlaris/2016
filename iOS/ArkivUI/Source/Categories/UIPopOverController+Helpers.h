//
//  UIPopOverController+Helpers.h
//  ArkivMobile
//
//  Created by Ashish Jain on 9/4/15.
//  Copyright (c) 2015 ARKIV. All rights reserved.
//

#import <UIKit/UIKit.h>

@interface UIPopoverController (Helpers)

- (void) dismissPopoverAnimated:(BOOL)animated completionHandler:(void(^)(void))completionHandler;

@end
