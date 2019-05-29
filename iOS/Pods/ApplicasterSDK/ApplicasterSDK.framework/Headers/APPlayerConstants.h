//
//  APPlayerConstants.h
//  ApplicasterSDK
//
//  Created by Tom Susel on 1/2/12.
//  Copyright (c) 2012 Applicaster. All rights reserved.
//

typedef enum {
    APMovieScalingModeAspectFit,  /**< Uniform scale until one dimension fits */
    APMovieScalingModeAspectFill, /**< Uniform scale until the movie fills the visible bounds. One dimension may have clipped contents */
    APMovieScalingModeFill        /**< Non-uniform scale. Both render dimensions will exactly match the visible bounds */
} APMovieScalingMode;

typedef enum {
    APMoviePlaybackStateStopped,
    APMoviePlaybackStatePlaying,
    APMoviePlaybackStatePaused,
    APMoviePlaybackStateInterrupted,
    APMoviePlaybackStateSeekingManually,
    APMoviePlaybackStateSeekingForward,
    APMoviePlaybackStateSeekingBackward
} APMoviePlaybackState;

typedef enum {
    APMovieLoadStateUnknown,
    APMovieLoadStateLoading,
    APMovieLoadStateLoaded,
    APMovieLoadStateError,
} APMovieLoadState;


typedef enum{
    APPlayerActionAtItemEndAdvance  = 0,
    APPlayerActionAtItemEndPause    = 1,
    APPlayerActionAtItemEndNone     = 2,
    APPlayerActionAtItemEndRepeat   = 3,
} APPlayerActionAtItemEnd;

typedef enum{
    APPlayerContentDurationTypeUnknown,     /**< Duration type is still unknown */
    APPlayerContentDurationTypeBounded,     /**< The content will eventually end */
    APPlayerContentDurationTypeIndefinite,  /**< Indicates that the time is indefinite. */
} APPlayerContentDurationType;
