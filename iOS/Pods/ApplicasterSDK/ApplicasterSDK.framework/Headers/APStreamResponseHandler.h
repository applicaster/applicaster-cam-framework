//
//  APStreamResponseHandler.h
//  applicaster
//
//  Created by Neer Friedman on 1/1/11.
//  Copyright 2011 __MyCompanyName__. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "APHTTPResponseHandler.h"
@class APASIHTTPRequest;

@interface APStreamResponseHandler : APHTTPResponseHandler {
	
	APASIHTTPRequest *_remoteRequest;

}

/**
 Call this method in order to register this class in the list of registered HTTP response handlers.
 Without this method being called the player will not play any item offline.
 */
+ (void)registerHandler;

@end
