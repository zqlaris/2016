//
//  ArkivCache.h
//  ArkivMobile
//
//  Created by Ariel Lichtin on 8/29/14.
//  Copyright (c) 2014 ARKIV. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <UIKit/UIKit.h>

@interface ArkivImageCache : NSObject

+ (ArkivImageCache*) sharedInstance;

- (UIImage*) getImage:(NSString*)key size:(CGSize)size;
- (void) setImage:(UIImage*)image key:(NSString*)key size:(CGSize)size;

@end
