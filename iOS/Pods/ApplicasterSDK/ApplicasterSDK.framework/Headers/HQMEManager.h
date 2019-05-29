//
//  HQMEManager.h
//  BabyTVHQME
//
//  Created by Neer Friedman on 12/28/10.
//  Copyright 2010 __MyCompanyName__. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "APReachabilityManager.h"

extern NSString *const HQMEDownloadNextEpisodeNotification;
extern NSString *const APHQMEDidDeleteAllNotification;

@class HQMEDownloadManager;
//typedef enum{
//	HQMEManagerStateOnline,			/**< The application is online and works against the applicaster server */
//	HQMEManagerStateOffline,		/**< The device should work offline, against the local storage */
//	HQMEManagerStateUnavailable,	/**< No storage is available - server nor local */
//	HQMEManagerStateInitial,
//}HQMEManagerState;

@class APVodItem;

/**
 The singleton class for managing HQME content.
 */
@interface HQMEManager : NSObject {
	NSArray *_items;
	APHQMEState _state;
	HQMEDownloadManager *_downloadManager;
	NSString			*_backgroundDownloadEndedFileName;
}

/** The current state, being Online/Offline/Unavailable/Initial */
@property (nonatomic, assign) APHQMEState hqmeState;

/**
 Checks if HQME is supported and ready
 @returns YES when HQME is supported, NO othewise.
 */
@property (readonly) BOOL isReady;

/**
 Holds YES if HQME is supported, NO otherwise
 */
@property (nonatomic, readonly) BOOL hqmeSupported;

/**
 Returns the shared manager.
 @return The singleton HQMEManager object.
 */
+ (instancetype)sharedManager;

/**
 A test to see if the item should be stored to local cache.
 @param uniqueID The unique ID to identify the VOD item.
 @return YES if item is HQME-enabled and is marked for download (or prioritized for download)
 */
- (BOOL)shouldCacheVodItemWithID:(NSString*)uniqueID;

/**
 Deletes all local data.
 */
- (void)deleteAllLocalData;

/**
 Checks if a VOD item is hqme enabled.
 @param vodItemID The unique ID to identify the VOD item.
 @return YES if is enabled for HQME. NO otherwise.
 */
- (BOOL)isVodItemHQMEEnabled:(NSString *)vodItemID;

#pragma mark Download issues

/**
 Returns all the VOD items currently downloading.
 @return An array of APVodItem objects that are currently being downloaded.
 */
- (NSArray *)allDownloadingVODItems;

/**
 This method checks if a VOD item is downloading.
 @param aVodItem The VOD item.
 @return YES if the item is currently downloading. NO otherwise.
 */
- (BOOL)isVodItemDownloading:(APVodItem*)aVodItem;

/**
 Checks if a VOD item has finished downloading.
 @param aVodItem The VOD item.
 @return YES if the VOD item has downloaded successfully. NO otherwise.
 */
- (BOOL)isVodItemDownloaded:(APVodItem*)aVodItem;

/**
 Retrieves the download progress of the VOD item.
 @param aVodItem The VOD item.
 @return The current download progress. Value ranges from 0.0 to 1.0.
 */
- (CGFloat)vodItemDownloadProgress:(APVodItem*)aVodItem;

/**
 Request a VOD item to be downloaded.
 @param aVodItem The VOD item.
 */
- (void)markForDownload:(APVodItem*)aVodItem;

/**
 Delete a VOD item from storage.
 @param aVodItem The VOD item.
 */
- (void)deleteItem:(APVodItem*)aVodItem;

/**
 Cancel a currently downloading VOD item.
 @param aVodItem The VOD item.
 */
- (void)cancelDownload:(APVodItem*)aVodItem;

/**
 Pause all current VOD item downloads.
 */
- (void)pauseAllDownloads;

/**
 Resume all paused VOD item downloads.
 */
- (void)resumeAllDownloads;

/**
 Set the name of the file to play once a VOD item has completed downloading in the background.
 @param fileName The file name of the sound file.
 */
- (void)setBackgroundDownloadEndSoundFileName:(NSString*)fileName;

/**
 Retrieve the name of the sound file played once a VOD item has completed downloading.
 @return The file name.
 */
- (NSString*)backgroundDownloadEndSoundFileName;

/**
 Force state to be OFFLINE
 @return the offline state
 */
- (void)forceOfflineDueToBadConnectivity;

#pragma mark - Deprecated
/**
 Post HQME metrics to server
 Deprecated - Should not be used
 */
- (void)postHQMEMetrics;

/**
 Try Fetching Account if limited connectivity accoured until account fetched
 */
- (void)startFetchingAPAccountProccess;

@end
