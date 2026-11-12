//
//  RBGameViewController.m
//  ArkivMobile
//
//  Created by Ariel Lichtin on 10/22/14.
//  Copyright (c) 2014 ARKIV. All rights reserved.
//

#import "RBGameViewController.h"
#import "ArkivNotifications.h"
#import "ArkivHUD.h"
#import "ArkivInfo.h"
#import "ArkivGoogleAnalytics.h"

@interface RBGameViewController ()

@end

@implementation RBGameViewController

- (id) initWithLaunchParams:(RBXGameLaunchParams *)parameters
{
    self = [super init];
    if (self)
        _launchParams = parameters;
    
    return self;
}

#pragma ACCESSORS
#pragma mark
+ (BOOL) isAppRunning
{
    return [[PlaceLauncher sharedInstance] appActive];
}


#pragma VIEW FUNCTIONS
#pragma mark
- (void)viewDidLoad
{
    [super viewDidLoad];
    
    self.view.frame = [UIScreen mainScreen].bounds;
    self.view.backgroundColor = [UIColor clearColor];
    
    [[NSNotificationCenter defaultCenter] addObserver:self selector:@selector(didLeaveGame:) name:RBX_NOTIFY_GAME_DID_LEAVE object:nil];
    
    [self launchGame];
}
- (void)dealloc
{
    [[NSNotificationCenter defaultCenter] removeObserver:self];
}

- (void)didLeaveGame:(NSNotification*)notification
{
    dispatch_async(dispatch_get_main_queue(), ^
    {
        [self dismissViewControllerAnimated:NO
            completion:^
            {
                if(_completionHandler)
                {
                    _completionHandler();
                }
            }];
    });
}



#pragma GAME FUNCTIONS
#pragma mark
-(void)launchGame
{
    if( !hasMinMemory(512) )
    {
        [ArkivHUD showMessage:NSLocalizedString(@"UnsupportedDevicePlayError", nil)];
        return;
    }
    
    [[NSNotificationCenter defaultCenter] postNotificationName:RBX_NOTIFY_GAME_JOINED object:nil];
    [[NSUserDefaults standardUserDefaults] setObject:@"tryGameJoin" forKey:@"ArkivGameState"];
    [[NSUserDefaults standardUserDefaults] synchronize];
    
    [ArkivHUD showSpinnerWithLabel:NSLocalizedString(@"LaunchGame", nil) dimBackground:YES];
    
    // Delay execution of the start block to display the spinner properly
    // TODO: Start the game in the place launcher in a separate thread (not UI)
    dispatch_after(dispatch_time(DISPATCH_TIME_NOW, 0.25f * NSEC_PER_SEC), dispatch_get_main_queue(), ^
    {
        [[PlaceLauncher sharedInstance] startGame:_launchParams controller:self presentGameAutomatically:YES];
    });
    
    [ArkivGoogleAnalytics setPageViewTracking:@"Visit/Try/Join"];
}

-(void) handleStartGameFailure
{
    [ArkivHUD hideSpinner:YES];
}

-(void) handleStartGameSuccess
{
    [ArkivHUD hideSpinner:YES];
}




@end
