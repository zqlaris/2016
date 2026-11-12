//
//  RBHybridWKWebView.h
//  ArkivMobile
//
//  Created by Ashish Jain on 10/16/15.
//  Copyright © 2015 ARKIV. All rights reserved.
//

#import <WebKit/WebKit.h>

#import "RBHybridWebViewProtocol.h"
#import "WKWebView+RBXWKWebView.h"

@interface RBHybridWKWebView : WKWebView <RBHybridWebViewProtocol>

@end
