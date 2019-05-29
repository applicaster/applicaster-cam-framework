//
//  APOverlayController.h
//  applicaster
//
//  Created by Tom Susel on 1/11/12.
//  Copyright (c) 2012 Applicaster. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "APCAllbackHandler.h"

/**
 The overlay controller is responsible of the overlay layer that appears above the player.
 */
@interface APOverlayController : APCallbackHandler

/**
 The overlay controller view.
 */
@property (nonatomic, strong, readonly) UIView *view;

@end
