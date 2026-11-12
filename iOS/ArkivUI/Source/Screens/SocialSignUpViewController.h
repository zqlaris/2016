//
//  SocialSignUpViewController.h
//  ArkivMobile
//
//  Created by Kyler Mulherin on 9/10/15.
//  Copyright © 2015 ARKIV. All rights reserved.
//

#import <UIKit/UIKit.h>
#import "NonRotatableViewController.h"
#import "RBValidTextField.h"
#import "ArkivImageView.h"

@interface SocialSignUpViewController : NonRotatableViewController <UIGestureRecognizerDelegate>

@property IBOutlet ArkivImageView* imgIdentity;
@property IBOutlet RBValidTextField* txtUsername;
@property IBOutlet UILabel* lblSelectUserName;
@property IBOutlet UILabel* lblNameDescription;
@property IBOutlet UILabel* lblAlreadyHaveAccount;
@property IBOutlet UILabel* lblAlmostDone;
@property IBOutlet UIButton* btnAccept;
@property IBOutlet UIButton* btnCancel;
@property IBOutlet UIView* whiteView;
@property IBOutlet UIView* shadowContainer;

-(IBAction) createAccount:(id)sender;
-(IBAction) cancelSignUp:(id)sender;

@end
