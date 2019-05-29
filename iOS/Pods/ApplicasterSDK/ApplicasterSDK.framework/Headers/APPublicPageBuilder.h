//
//  APPublicPageBuilder.h
//  applicaster
//
//  Created by dan g / applicaster on 8/31/14.
//  Copyright (c) 2014 Applicaster Ltd. All rights reserved.
//

#import <Foundation/Foundation.h>

@interface APPublicPageBuilder : NSObject

+ (NSURL *)getPublicPageForApp;
+ (NSURL *)getPublicPageForVodITem:(NSString *)vodItemUniqueID;
+ (NSURL *)getPublicPageForChannel:(NSString *)channelUniqueID;
+ (NSURL *)getPublicPageForFeed:(NSString *)timelineID;
+ (NSURL *)getPublicPageForCM:(NSString *)timelineID andFeedID:(NSString *)feedID andEventID:(NSString *)eventID;
@end
