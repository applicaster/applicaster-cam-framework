//
//  APReachability.h
//  
//  Copyright (c) 2011, Nick Paulson
//  All rights reserved.
//  
//  Redistribution and use in source and binary forms, with or without modification, are permitted provided that the following conditions are met:
//  
//  Redistributions of source code must retain the above copyright notice, this list of conditions and the following disclaimer.
//  Redistributions in binary form must reproduce the above copyright notice, this list of conditions and the following disclaimer in the documentation and/or other materials provided with the distribution.
//  Neither the name of the Nick Paulson nor the names of its contributors may be used to endorse or promote products derived from this software without specific prior written permission.
//  THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
//

#import <Foundation/Foundation.h>
#import <SystemConfiguration/SystemConfiguration.h>
#import <netinet/in.h>
/**
 This is practically the NPReachability project except with no warnings and with documentation.
 */
@interface APReachability : NSObject {
	NSMutableDictionary *_handlerByOpaqueObject;
	
	SCNetworkReachabilityRef _reachabilityRef;
}

/**
 Retrieves the shared instance of APReachability.
 @return The shared instance.
 */
+ (APReachability *)sharedInstance;

/**
 Add a block to respond to changes in reachability.
 @param handler A block that uses the flags paramater to evaluate the current reachability value.
 @return An opaque object used for removal later.
 */
- (id)addHandler:(void (^)(SCNetworkReachabilityFlags flags))handler;

/**
 Allows remove of the opaque object created in addHandler:
 @param opaqueObject The object used to retain the handler block.
 */
- (void)removeHandler:(id)opaqueObject;

/**
 Checks the current reachability flags to see if reachability has been obtained.
 @return YES if the current reachability is reachable, NO otherwise.
 */
- (BOOL)isCurrentlyReachable;

/**
 Get the current reachability flags.
 @return The current reachability flags.
 */
- (SCNetworkReachabilityFlags)currentReachabilityFlags;

/**
 Checks for reachability using the supplied flags.
 @param flags The reachability flags being checked.
 @return YES if the reachability is valid for the given flags, NO otherwise.
 */
+ (BOOL)isReachableWithFlags:(SCNetworkReachabilityFlags)flags;

/*!
 * Checks whether a local WiFi connection is available.
 */
+ (BOOL)isWifiOn;

@end
