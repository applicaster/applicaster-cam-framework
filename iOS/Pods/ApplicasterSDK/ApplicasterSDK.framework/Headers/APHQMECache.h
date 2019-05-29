//
//  APHQMECache.h
//  applicaster
//
//  Created by Neer Friedman on 1/3/11.
//  Copyright 2011 __MyCompanyName__. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "APASIDownloadCache.h"
@class APVodItem;
/**
 Manages the cache for HQME items loaded in the player
 
 Should only cache files directly related to playback
 This cache is used in the APHTTPServer
 
 TODO:
 we should define a directory structure to hold the following data on each vod item:
   - item meta data (APVodItem)
   - item m3u8 + TSs (check if headers are also required)
 
 */
@interface APHQMECache : APASIDownloadCache {

}

/**
 Vod Item details used to create the path for the current Download.
 This should be set before any use and cleared after every segment
 */
@property (nonatomic, strong) APVodItem *vodItem;

/**
 Returns a static instance of an APHQMECache
 @return The shared instance.
 */
+ (id)sharedCache;

/**
 Get the file path for video files.
 @return The full path to the .m3u8 and .ts files.
 */
- (NSString *)storagePath;

/**
 Delete a specific VOD item from cache.
 @param vodItemID The VOD item's ID.
 @param broadcasterID The broadcaster's unique ID.
 */
- (void)deleteCacheForVodItemID:(NSString*)vodItemID broadcasterID:(NSString*)broadcasterID;

/**
 Deletes all local files.
 */
- (void)clearAllCache;

/**
 Gets the vod item ID.
 @param path The path in which to search for the VOD item.
 @returns The VOD item ID or nil if not found.
 */
+ (NSString*)vodItemIDForURLPath:(NSString*)path;

/**
 String path for VOD item in cache directory
 */
- (NSString *)pathForVodItem:(APVodItem *)vodItem;

/**
 If a VOD item has stream url - it will return if it has HQME cache in the old way.
 */
+ (BOOL)isLegacyVOD:(APVodItem *)vodItem;

@end
