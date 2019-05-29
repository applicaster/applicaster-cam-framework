//
//  VodItemShowOperation.h
//  applicaster
//
//  Created by Neer Friedman on 1/5/11.
//  Copyright 2011 __MyCompanyName__. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <AVFoundation/AVFoundation.h>
#import "APModel.h"

@class APVodItem;
/**
 A subclass of <NSOperation>, this operation type is responsible for downloading individual VOD items.
 */
@interface VodItemDownloadOperation : NSOperation <AVAudioPlayerDelegate, APModelObserver> {
	NSOperationQueue *_segmentsQueue;
	
	NSInteger _segmentsDetected;
	NSInteger _segmentsDownloaded;
	
	//NSOperation
	//BOOL _finished, _executing;
	BOOL _cancelled;
	UIBackgroundTaskIdentifier _backgroundTask;
    
    BOOL _didNotifyFailure;
}

/**
 The VOD item to download.
 */
@property (nonatomic, strong, readonly)	APVodItem			*vodItem;

/**
 The <NSOperationQueue> object used for downloading the segments of the video.
 */
@property (nonatomic, readonly)	NSOperationQueue	*segmentsQueue;

//@property (nonatomic, assign, getter=isFinished)	BOOL		finished;
//@property (nonatomic, assign, getter=isExecuting)	BOOL		executing;

/**
 The primary initialization method for a video download operation.
 @param manager The download manager responsible for the downloading of the video.
 @param vodItem The VOD item whose video is being downloaded.
 */
- (id)initWithVodItem:(APVodItem*)vodItem;

/**
 Returns the current download progress of the video.
 @return The current progress of the download between 0.0 and 1.0.
 */
- (CGFloat)progress;

/**
 Returns whether or not the item was downloaded successfully.
 @return YES if download succeeded, NO otherwise.
 */
- (BOOL)didDownloadSuccessfully;

@end
