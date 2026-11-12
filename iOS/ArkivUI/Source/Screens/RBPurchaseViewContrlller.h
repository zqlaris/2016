//
//  RBPurchaseViewContrlller.h
//  ArkivMobile
//
//  Created by Christian Hresko on 6/16/14.
//  Copyright (c) 2014 ARKIV. All rights reserved.
//

#import <UIKit/UIKit.h>

// TODO - make this a subclass of a common Modal UIViewController
@interface RBPurchaseViewContrlller : UIViewController<UIWebViewDelegate, UIGestureRecognizerDelegate>

- (id)initWithURL:(NSURL*)url andTitle:(NSString*)title;

@end
