
#import <Foundation/Foundation.h>

@interface ArkivAlert : NSObject

+(void) ArkivAlertWithMessage:(NSString*) message;
+(void) ArkivOKAlertWithMessageAndDelegate:(NSString*) message Delegate:(id) delegate;
+(void) ArkivAlertWithMessageAndDelegate:(NSString*) message Delegate:(id) delegate;
@end

