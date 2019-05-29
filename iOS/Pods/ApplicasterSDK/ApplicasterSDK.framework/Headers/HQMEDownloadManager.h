//
//  HQMEDownloadManager.h
//  applicaster
//
//  Created by Tom Susel on 1/5/11.
//  Copyright 2011 __MyCompanyName__. All rights reserved.
//

#import <Foundation/Foundation.h>

@class APVodItem;
/**
 The HQMEDownloadManager class is responsible for downloading HQME content.
 */
@interface HQMEDownloadManager : NSObject {
	NSOperationQueue	*_mainQueue;
	UILocalNotification	*_downloadTimeWillExpireNotification;
}

/**
 Returns all the VOD items currently downloading.
 @return An array of APVodItem objects that are currently being downloaded.
 */
- (NSArray *)allDownloadingVODItems;

/**
 Marks a vod item for download.
 If HQME is in online state, should add the vod item immediately to the download queue.
 @param aVodItem The vod item to download
 */
- (void)markVodItemForDownload:(APVodItem*)aVodItem;

/**
 Checks if a specific VOD item is downloading.
 @param vodItemID The ID for the VOD item.
 @return YES if the item is currently downloading, NO otherwise.
 */
- (BOOL)isVodItemDownloading:(NSString*)vodItemID;

/**
 Get the current download progress for the supplied VOD item.
 @param aVodItem The VOD item.
 @return The download progress, ranging from 0.0 to 1.0.
 */
- (CGFloat)vodItemDownloadProgress:(APVodItem*)aVodItem;

/**
 Cancel the currently downloading VOD item.
 @param aVodItem The VOD item.
 */
- (void)cancelDownload:(APVodItem*)aVodItem;

/**
 Cancel all downloads.
 */
- (void)cancelAllDownloads;

/**
 Pauses all downloads.
 
 This pauses the main queue, and thus the subqueues.
 */
- (void)pause;

/**
 Resumes all paused downloads.
 */
- (void)resume;

@end
