//
//  ArkivXSRFRequest.m
//  ArkivMobile
//
//  Created by Ariel Lichtin on 6/25/14.
//  Copyright (c) 2014 ARKIV. All rights reserved.
//

#import "ArkivXSRFRequest.h"
#import "ArkivInfo.h"

#define XSRF_HEADER_NAME @"X-CSRF-TOKEN"

// This cached token will be valid for this only user/session for a short time frame
// TODO: Put this token behind a mutex
NSString* cachedXSRFToken;

@implementation ArkivXSRFRequest

/* XSRF Protection: Post a message that modifies the state of the server using a safety ARKIV token */
- (AFHTTPRequestOperation *)XSRFPOST:(NSString *)URLString
                          parameters:(id)parameters
                             success:(void (^)(AFHTTPRequestOperation *operation, id responseObject))success
                             failure:(void (^)(AFHTTPRequestOperation *operation, NSError *error))failure
{
    //set the default useragent
    [self.requestSerializer setValue:[ArkivInfo getUserAgentString] forHTTPHeaderField:@"User-Agent"];
    
    // Set the cached ARKIV token to the request
    if(cachedXSRFToken)
    {
        [self.requestSerializer setValue:cachedXSRFToken forHTTPHeaderField:XSRF_HEADER_NAME];
    }
    
    AFHTTPRequestOperation* operation =
        [self POST:URLString parameters:parameters success:^(AFHTTPRequestOperation *operation, id responseObject)
        {
            // Return with success
            success(operation, responseObject);
        }
        failure:^(AFHTTPRequestOperation *operation, NSError *error)
        {
            // If the status code is 403 (XSRF Token Validation Failed),
            // the request should be reposted with the new token provided in the response
            if(operation.response.statusCode == 403)
            {
                // Save the new token
                NSDictionary* headerFields = operation.response.allHeaderFields;
                cachedXSRFToken = headerFields[XSRF_HEADER_NAME];

                // Start the request again
                if (cachedXSRFToken)
                    [self XSRFPOST:URLString parameters:parameters success:success failure:failure];
                else
                    failure(operation, error);
            }
            else
            {
                // The failure is for some other reason
                // Return with error
                failure(operation, error);
            }
        }];
    
    return operation;
}

@end
