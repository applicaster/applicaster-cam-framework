//
//  APPreloadViewController.h
//  applicaster
//
//  Created by Guy Kogus on 25/07/11.
//  Copyright 2011 __MyCompanyName__. All rights reserved.
//

#import <UIKit/UIKit.h>
#import "APAccount.h"

@class APPreloadViewController;

/**
 The APPreloadViewControllerDelegate is responsible for handling the end of the preload.
 @see APPreloadViewController
 */
@protocol APPreloadViewControllerDelegate <NSObject>

@optional
/**
 This callback method indicates when the preload content has finished loading. Some delegates may want to wait until all content is loaded before displaying, while others may want to show a loading screen.
 @param preloadViewController The <APPreloadViewController> that has finished loading its content.
 */
- (void)preloadViewControllerDidFinishLoadingContent:(APPreloadViewController *)preloadViewController;

/**
 This method is called when the timed webviewcontroller did Disappear.
 This can be used to determin when it was dismissed
 @param preloadVC The preload that was dismissed.
 */
- (void)preloadViewDidDisappear:(APPreloadViewController *)preloadVC;

@required
/**
 This method is called when the preload content has finished viewing.
 
 There are 3 reasons for this method to be called:<p>
 - An image has displayed for 6 seconds.<p>
 - A video has finished playing.<p>
 - The web page preload has been dismissed.<p>
 This will also be called if any of the preload content types failed to load.
 @param preloadViewController The <APPreloadViewController> that has finished displaying its content.
 */
- (void)preloadViewControllerFinished:(APPreloadViewController *)preloadViewController;

@end

/**
 The APPreloadViewController is designed to handle all preload (splash) content types. These are currently web, image and video.
 */
@interface APPreloadViewController : UIViewController {
    id <APPreloadViewControllerDelegate> _delegate;
    BOOL _shouldPlayMovie;
}

/**
 This bitmask defines the allowed interface orientations. See <UIInterfaceOrientations> for the interface orientations that can be combined using the C bitwise OR operation.
 */
@property (nonatomic, assign) UIInterfaceOrientationMask allowedInterfaceOrientations;

/**
 The <APPreloadViewControllerDelegate> is responsible for handling the end of the preload.
 */
@property (nonatomic, unsafe_unretained) id<APPreloadViewControllerDelegate> delegate;

/**
 The loading spinner.
 */
@property (nonatomic, strong) UIActivityIndicatorView *spinner;

/**
 There are 3 regular types of preloads: web, image and video.
 */
@property (nonatomic, assign) APPreloadURLType type;

/**
 The URL that points to the preload content.
 */
@property (nonatomic, strong) NSURL *url;

/**
 The length of time to display the preload content.
 */
@property (nonatomic, assign) NSTimeInterval exposureTime;

/**
 The primary preload view controller initialization method.
 @param aType See the <type> property.
 @param aUrl See the <url> property.
 @param anExposureTime See the <exposureTime> property.
 @return The APPreloadViewController object.
 */
- (id)initWithPreloadType:(APPreloadURLType)aType forURL:(NSURL *)aUrl withExposureTime:(NSTimeInterval)anExposureTime;

/**
 Checks to see if the preload content has finished loading.
 @return YES if the content has finished loading. No otherwise.
 */
- (BOOL)isContentLoaded;

@end
