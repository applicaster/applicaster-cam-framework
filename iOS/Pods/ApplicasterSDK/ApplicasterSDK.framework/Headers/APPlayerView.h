//
//  AVPlayerView.h
//  ApplicasterSDK
//
//  Created by Tom Susel on 1/2/12.
//  Copyright (c) 2012 Applicaster. All rights reserved.
//

#import <UIKit/UIKit.h>

@class AVPlayer;
/**
 A view that is used to render the <code>AVPlayer</code> content.
 */
@interface APPlayerView : UIView

/**
 The player who's layer is associated with this view's layer.
 */
@property (nonatomic, retain) AVPlayer *player;

@end
