//
//  APFeedFeed.h
//  applicaster
//
//  Created by Liviu Romascanu on 8/1/13.
//  Copyright (c) 2013 Applicaster Ltd. All rights reserved.
//

#import <Foundation/Foundation.h>

@interface APFeedFeed : NSObject
{
    NSMutableDictionary *_object;
}

/**
 json dict
 */
@property (nonatomic, strong) NSDictionary *object;

/**
 Episode Unique ID
 */
@property (nonatomic, strong) NSString *uniqueID;

/**
 Feed Name
 */
@property (nonatomic, strong) NSString *name;

/**
 Is this a public feed.
 If so should automatically follow it in an episode
 */
@property (nonatomic, assign) BOOL isPublic;

/**
 Push notifications tag
 */
@property (nonatomic, strong) NSString *pushTag;

/**
 Position in the UI
 */
@property (nonatomic, assign) NSInteger position;

/**
 Feed Description
 */
@property (nonatomic, strong) NSString *feedDescription;

/**
 Welcome Text
 */
@property (nonatomic, strong) NSString *welcomeText;

/**
 Image dictionary
 */
@property (nonatomic, strong) NSDictionary *imageDictionary;

/**
 Init with dictionary from JSON
 Be sure to call the correct feed type object
 */
- (id)initWithDictionary:(NSDictionary *)dictionary;

@end
