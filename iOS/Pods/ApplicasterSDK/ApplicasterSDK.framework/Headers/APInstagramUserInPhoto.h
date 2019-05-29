//
//  APUserInPhoto.h
//  ApplicasterSDK
//
//  Created by Liviu Romascanu on 3/10/15.
//  Copyright (c) 2015 Applicaster. All rights reserved.
//

#import "APInstagramModel.h"
@class APInstagramUser;

@interface APInstagramUserInPhoto : APInstagramModel

/**
 X Position in the image - Relative - 0.0-1.0 so it can be applied to any image size chosen
 */
@property (nonatomic, readonly, assign) CGFloat xPosition;

/**
 Y Position in the image - Relative - 0.0-1.0 so it can be applied to any image size chosen
 */
@property (nonatomic, readonly, assign) CGFloat yPosition;

/**
 APInstagram user tagged in the photo
 */
@property (nonatomic, weak, readonly) APInstagramUser *user;

@end
