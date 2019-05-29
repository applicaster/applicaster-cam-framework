//
//  APInstagramCaption.h
//  ApplicasterSDK
//
//  Created by Liviu Romascanu on 3/10/15.
//  Copyright (c) 2015 Applicaster. All rights reserved.
//

#import "APInstagramModel.h"

@class APInstagramUser;
@interface APInstagramCaption : APInstagramModel

/**
 Instagram user that posted the caption
 */
@property (nonatomic, weak, readonly) APInstagramUser *user;

/**
 Text
 */
@property (nonatomic, weak, readonly) NSString *text;

/**
 Caption / comment unique ID
 */
@property (nonatomic, weak, readonly) NSString *uniqueID;

/**
 Creation date
 */
@property (nonatomic, weak, readonly) NSDate *createdAt;

@end
