//
//  APInstagramVideo.h
//  ApplicasterSDK
//
//  Created by Liviu Romascanu on 3/10/15.
//  Copyright (c) 2015 Applicaster. All rights reserved.
//

#import "APInstagramModel.h"

@interface APInstagramVideo : APInstagramModel

/**
 Video URL in String Format
 */
@property (nonatomic, weak, readonly) NSString *urlString;

/**
 Video width in pixels
 */
@property (nonatomic, weak, readonly) NSNumber *width;

/**
 Video height in pixels
 */
@property (nonatomic, weak, readonly) NSNumber *height;

/**
 Standard CGSize of the image (Pixels - non retina
 */
@property (nonatomic, readonly, assign) CGSize size;


@end
