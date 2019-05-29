//
//  APURLSchemeHandler.h
//  applicaster
//
//  Created by Guy Kogus on 27/11/12.
//  Copyright (c) 2012 Applicaster Ltd. All rights reserved.
//

#import <Foundation/Foundation.h>

@class APApplicasterController;
    
/**        
 This class is responsible for handling URL schemes.
 */
@interface APURLSchemeHandler : NSObject

/**
 Creates a singleton if necessary and returns it.
 @return The shared handler.
 */
+ (id)sharedHandler;

/**
 Handle a URL being opened from the given applicaster controller.
 @param url The URL scheme used to open the application.
 @param applicaster The Applicaster Controller that requested a URL to be opened.
 @return YES if the URL was handled, otherwise NO.
 */
- (BOOL)handleURL:(NSURL *)url forApplicasterController:(APApplicasterController *)applicaster;

/**
 Check if url scheme is a url pattern for playing vod.
 @param url The URL scheme used to open the application.
 @return YES if the URL pattern is for playing vod , otherwise NO.
 */
- (BOOL)isVodPlayUrlScheme:(NSURL *)url;

/**
 @param url The URL scheme used to open the application.
 @return The vod item's id that is extracted from the given url.
 */
- (NSString *)vodItemIDForUrl:(NSURL *)url;

/**
 @param url The URL scheme used to open the application.
 @return YES whether the given URL is a URL to presenting a URL.
 */
- (BOOL)isPresentURLScheme:(NSURL *)url;

/**
 @param url The URL scheme used to open the application.
 @return The given URL to a present URL scheme. (Example: reshet://present?url=<return>).
 */
- (NSURL *)presentURLForUrl:(NSURL *)url;

@end
