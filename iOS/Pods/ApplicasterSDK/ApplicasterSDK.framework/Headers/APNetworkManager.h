//
//  APNetworkManager.h
//  ApplicasterSDK
//
//  Created by Tom Susel on 3/2/11.
//  Copyright 2011 Applicaster. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <AFNetworking/AFHTTPRequestOperationManager.h>

#pragma mark - Definitions

static NSString *const kErrorMessage = @"Error";

@interface APNetworkManager : AFHTTPRequestOperationManager

/**
 Singleton instance getter.
 @returns The network manager singleton instance.
 */
+ (APNetworkManager *)sharedNetworkManager;

#pragma mark -
#pragma mark Retrieve Device IP

// Get IP Address
- (NSString *)getIPAddress;

@end