//
//  APLoadingView.h
//  applicaster
//
//  Created by Tom Susel on 1/18/12.
//  Copyright (c) 2012 Applicaster. All rights reserved.
//

#import <Foundation/Foundation.h>

/**
 Loading View protocol.
 The view is shown to the user while some asynchronous action takes place.
 */
@protocol APLoadingView <NSObject>

@property (strong, nonatomic) IBOutlet UIButton *cancelButton;

@optional
/**
 Called when the loading starts.
 Implement this method to start animations  i.e.
 */
- (void)loadingStarted;

/**
 Called when loading stops.
 Loading may start again, so this is a good point in time to pause animations or other actions.
 */
- (void)loadingStopped;

/**
 Called when the loading starts.
 Implement this method to start animations i.e. or show the playable's metadata.

 @param playable - the item that is currently played in the player.
 */
- (void)loadingStartedWithPlayable:(id)playable;

/**
 Called when loading stops.
 Loading may start again, so this is a good point in time to pause animations or other actions. At this point the playable's metadata should be already loaded so you may   use it also to refresh the UI.

 @param playable - the item that is currently played in the player.
 */
- (void)loadingStoppedWithPlayable:(id)playable;

/**
 Called when loading fails.
 @param message - A description of the failure. This value should already be localized.
 */
- (void)loadingFailedWithMessage:(NSString*)message;

/**
 When received, the loading view should convey the message.
 @param message - A description of the current load state.
 */
- (void)setLoadingMessage:(NSString*)message;

@end
