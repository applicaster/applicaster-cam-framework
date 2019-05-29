//
//  APDefaultPlayerControlsView.h
//  ApplicasterSDK
//
//  Created by Tom Susel on 1/8/12.
//  Copyright (c) 2012 Applicaster. All rights reserved.
//

#import <UIKit/UIKit.h>
#import "APPlayerControls.h"
#import "APSlider.h"

/**
 A standard set of controls for the video player. Conforms to the <APPlayerControls> protocol.
 */
@interface APPlayerControlsView : UIView <APPlayerControls, APSliderDelegate>{
	IBOutlet UIImageView *_backgroundImageView;
    IBOutlet UILabel *_timeLabel;   /**< Current time and duration */

	IBOutlet UIActivityIndicatorView *_bufferingIndicator;
    NSTimeInterval _playbackDuration;
    NSTimeInterval _playbackCurrentTime;
}

@property (nonatomic, assign, getter = isPlayerPlaying) BOOL playerPlaying;

/**
 Sets the slider images.
 @param slider The seeker.
 */
- (void)customizeSeekSliderView:(UISlider*)slider;

/**
 Returns the already watched percentage of the current playing item for VOD (between 0.0 - 1.0). Returns 1.0 for Live.
 */
- (CGFloat)normalizedPlayedPercentage;

@end
