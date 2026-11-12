//
//  SimplePlayerMacAppDelegate.h
//  SimplePlayerMac
//
//  Created by Tony on 10/26/10.
//  Copyright 2010 __MyCompanyName__. All rights reserved.
//
#pragma once

#import <Cocoa/Cocoa.h>
#import <Breakpad.h>

#import "ArkivOgreView.h"

#include "rbx/signal.h"
#import "RbxWebView.h"
#import "RBXWindow.h"

class ArkivView;

namespace RBX
{
    class DataModel;
}

@interface ArkivPlayerAppDelegate : NSResponder <NSWindowDelegate>
{
    RBXWindow *window;
	NSView *mainView;
    RbxWebView *rbxWebView;
	ArkivOgreView *ogreView;
	ArkivView *arkivView;
	NSMenu *mainMenu;
	BOOL running;
	BOOL quitOnLeave;
	ArkivAppShutdownCode shutdownCode;
	BreakpadRef breakpad;
    rbx::signals::scoped_connection openUrlConnection;
    rbx::signals::scoped_connection closeUrlConnection;
    ArkivGameType gameType;
}

-(id) init;

- (BOOL) checkUpdater:(BOOL) showUpdateOptionsDialog;

-(void)marshallFunction:(NSEvent *)evt;

-(void)addLogFile:(NSString *)file;
-(void)addBreakPadKeyValue:(NSString *)breakPadKey withValue:(NSString *)value;
-(void)addDbgInfoToBreakPad;

-(void)applicationDidFinishLaunching:(NSNotification *)aNotification;
-(NSApplicationTerminateReply)applicationShouldTerminate:(NSApplication *)sender;
-(BOOL)applicationShouldTerminateAfterLastWindowClosed:(NSApplication *)theApplication;
-(void)applicationWillTerminate:(NSNotification *)aNotification;

-(void)windowWillClose:(NSNotification *)notification;

-(void)ShutdownDataModel;
-(void)leaveGame;
-(void)handleLeaveGame;
-(BOOL)requestShutdownClient:(ArkivAppShutdownCode)code;
-(void)handleShutdownClient;

-(void)handleToggleFullScreen;
-(bool)inFullScreenMode;

-(void)teleport:(NSString *)ticket withAuthentication:(NSString *)url withScript:(NSString *)script;
-(void)StartGame:(NSString *)ticket withAuthentication:(NSString *)url withScript:(NSString *)script;

bool requestPlaceInfo(int testPlaceID, std::string& authenticationUrl, std::string& ticket, std::string& scriptUrl);
RequestPlaceInfoResult requestPlaceInfo(const std::string& placeLauncherUrl, std::string& authenticationUrl, std::string& ticket, std::string& scriptUrl);

-(void) openUrlWindow:(std::string) url;

- (IBAction)crash:(id)sender;

-(void) setupGameServices;
-(void) setupDataModelServices:(RBX::DataModel*) dataModel;

+(void) reportRenderViewInitError:(const char *)message;

@property (assign) IBOutlet RBXWindow *window;
@property (assign) IBOutlet NSView *mainView;

@property (readwrite, assign) ArkivView *arkivView;
@property (assign) IBOutlet ArkivOgreView *ogreView;
@property (assign) IBOutlet NSMenu *mainMenu;

@end
