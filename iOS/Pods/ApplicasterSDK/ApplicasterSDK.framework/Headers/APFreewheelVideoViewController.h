//
//  APFreewheelVideoViewController.h
//  applicaster
//
//  Created by Roee Minster on 1/19/15.
//  Copyright (c) 2015 Applicaster. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "APPlayerCommercialsProtocol.h"

@class APPlayerViewController;

@interface APFreewheelVideoViewController : UIViewController

/**
 *  Defines if to present close out button on the freewheel ad, upon taping the button will close the ad.
 *  Setting this propery must be before calling the playVideoWithFreewheelPlayerViewController method.
 */
@property (nonatomic, assign) BOOL shouldShowCloseOutButton;

/**
 *  Plays freewheel ad on top of the player view controller.
 *
 *  @param siteSectionId        freewheel siteSectionId
 *  @param playerViewController Applicaster player view controller that contains avplayer.
 *  @param completion           completion block that will called in the following cases:
 *  preroll or postroll finised or if adManager isn't initiated
 */
- (void)playVideoWithFreewheelPlayerViewController:(APPlayerViewController *)playerViewController
                            commercialsType:(APPlayerCommercialsType)playerCommercialsType
                          completionHandler:(void (^)(BOOL success, BOOL canceled))completion;

@end
