//
//  AFURLConnectionOperation+APAddition.h
//  ApplicasterSDK
//
//  Created by Guy Kogus on 5/01/12.
//  Copyright (c) 2012 Applicaster. All rights reserved.
//

#import <AFNetworking/AFHTTPRequestOperation.h>

@interface AFHTTPRequestOperation (APAddition)

/**
 This convenience method creates a simple NSURLRequest object before calling initWithURLRequest:
 @param url The URL whose information is being loaded.
 @return The new operation that will download the data at url.
 */
- (id)initWithURL:(NSURL *)url;

/**
 Automatically enqueues the operation with normal priority.
 */
- (void)startAsynchronous;

/**
 Automatically enqueues the operation with the set priority.
 */
- (void)startAsynchronousWithPriority:(NSOperationQueuePriority)priority;


/**
 Checks if the url request responses successful. This method creates a url request and checks the response from url.
 @param url The url that will requested.
 @param completionBlock This completionBlock has no return value and takes two arguments: the first argument will return BOOL success. YES if the request was successful without any error. NO if the request had error.
    The secound argument the error that occurred during the request if the request wasn't successful. 
 
 This block has no return value and takes two arguments: the receiver operation and the error that occurred during the request
 */
+ (void)checkURLResponseForURL:(NSURL *)url withCompletionBlock:(void (^)(BOOL success, NSError *error))completionBlock;

@end
