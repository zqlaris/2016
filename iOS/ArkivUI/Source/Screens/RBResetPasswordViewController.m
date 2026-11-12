//
//  RBResetPasswordControllerViewController.m
//  ArkivMobile
//
//  Created by Christian Hresko on 6/26/14.
//  Copyright (c) 2014 ARKIV. All rights reserved.
//

#import "RBResetPasswordViewController.h"
#import "ArkivInfo.h"

@interface RBResetPasswordViewController ()

@end

@implementation RBResetPasswordViewController

- (BOOL)webView:(UIWebView *)webView shouldStartLoadWithRequest:(NSURLRequest *)request navigationType:(UIWebViewNavigationType)navigationType
{
    return YES;
}

- (BOOL)gestureRecognizer:(UIGestureRecognizer *)gestureRecognizer shouldReceiveTouch:(UITouch *)touch {
    return NO;
}

@end
