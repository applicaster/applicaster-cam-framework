//
//  APFeedEventVideo.h
//  applicaster
//
//  Created by Liviu Romascanu on 8/1/13.
//  Copyright (c) 2013 Applicaster Ltd. All rights reserved.
//

#import "APFeedEventImage.h"

@interface APFeedEventVideo : APFeedEventImage

/**
 Video URL
 */
@property (nonatomic, strong) NSURL *videoURL;

@end
