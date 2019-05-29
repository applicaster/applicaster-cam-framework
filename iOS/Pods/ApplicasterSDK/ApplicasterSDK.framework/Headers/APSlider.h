//
//  OBSlider.h
//
//  Created by Ole Begemann on 02.01.11.
//  Copyright 2011 Ole Begemann. All rights reserved.
//

#import <UIKit/UIKit.h>

@class APBreakpointsView;

extern const CGFloat kAPSliderScrubbingSpeedHigh;
extern const CGFloat kAPSliderScrubbingSpeedHalf;
extern const CGFloat kAPSliderScrubbingSpeedQuarter;
extern const CGFloat kAPSliderScrubbingSpeedFine;

@class APSlider;

@protocol APSliderDelegate <NSObject>
@optional
- (void)sliderDidStartScrubbing:(APSlider *)slider;
- (void)sliderDidEndScrubbing:(APSlider *)slider;
- (void)slider:(APSlider *)slider didChangeScrubbingSpeed:(CGFloat)scrubbingSpeed;

@end

@interface APSlider : UISlider
{
    CGPoint beganTrackingLocation;
    CGFloat realPositionValue;
}

@property (nonatomic, assign, readonly) CGFloat scrubbingSpeed;
@property (nonatomic, strong) NSArray *scrubbingSpeeds;
@property (nonatomic, strong) NSArray *scrubbingSpeedChangePositions;
@property (nonatomic, strong) APBreakpointsView *breakpointsView;
;


@property (nonatomic, assign) IBOutlet id <APSliderDelegate> delegate;

@end
