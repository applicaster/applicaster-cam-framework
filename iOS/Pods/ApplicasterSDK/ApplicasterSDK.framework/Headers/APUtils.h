//
//  APUtils.h
//  applicaster
//
//  Created by Neer Friedman on 12/8/09.
//  Copyright 2009 __MyCompanyName__. All rights reserved.
//

#import <UIKit/UIKit.h>
#import <Foundation/Foundation.h>

/**
 This class provides some basic utility methods.
 */
@interface APUtils : NSObject

+ (NSDictionary *)signRequestParams:(NSDictionary *)params URL:(NSString *)url withKey:(NSString *)key;
+ (NSString *)signedURLPath:(NSString *)urlPath withParams:(NSDictionary *)params withKey:(NSString *)key;

/**
 * Parse string to date
 * @param stringDate - the date as string
 * @return the NSString of the format dd.mm.yyyy 
 */
+ (NSString *)dateFormatFromString:(NSString *)stringDate;

/**
 Checks if the stream is valid.
 @param streamPath - The path of the stream to test
 @return NO if the stream is empty or has expired, YES otherwise.
 */
+ (BOOL)isStreamValid:(NSString *)streamPath;

/**
 Converts a date from local time zone to UTC.
 @param localDate - A date in local time zone.
 @return The date normalized to UTC time zone.
 */
+ (NSDate *)getUTCDateFromLocalDate:(NSDate *)localDate;

/**
 Checks if a selected URL link should be opened externally or internally.
 @param URL The URL being checked.
 @return YES if the link should be opened externally. NO otherwise.
 */
+ (BOOL)shouldOpenURLExternally:(NSURL *)URL;

/**
 @return YES if the given URL is a web one (one that can be opened from the Safari for example)
 */
+ (BOOL)isWebURL:(NSURL*)URL;

/**
 @return YES if the given URL is a web one (one that can be opened from the Safari for example)
 */
+ (BOOL)isWebStringURL:(NSString *)stringURL;

@end
