//
//  APPlayerInterruptionView.h
//  applicaster
//
//  Created by Tom Susel on 2/2/12.
//  Copyright (c) 2012 Applicaster. All rights reserved.
//

#import <Foundation/Foundation.h>

typedef NS_ENUM(NSUInteger, APPlayerInterruptionReason) {
	APPlayerInterruptionReasonBackFromBackground,
	APPlayerInterruptionReasonResumePlayback,
	APPlayerInterruptionReasonCaptureMoment
};

@class APPlayerController;

/**
 A protocol that any interruption view must contain.
 */
@protocol APPlayerInterruptionViewProtocol <NSObject>

@optional
@property (nonatomic, strong) IBOutlet UIButton *resumeButton;  /** Resumes playback at previous position */
@property (nonatomic, strong) IBOutlet UIButton *restartButton; /** Restarts playback from the begining of the current item */
@property (nonatomic, strong) IBOutlet UIButton *closeButton; /** Restarts playback from the begining of the current item */
@property (nonatomic, strong) IBOutlet UIButton *captureShareButton;
@property (nonatomic, strong) IBOutlet UIButton *captureRestartButton;
@property (nonatomic, strong) IBOutlet UIButton *captureResumeButton;
@property (nonatomic, unsafe_unretained) APPlayerController *playerController; /** A refference to the player controller */
@property (nonatomic, assign) APPlayerInterruptionReason interruptionReason; /** The reason for the interruption view's appearance. Default is APPlayerInterruptionReasonBackFromBackground. */

@end
