//
//  APInstagramUser.h
//  ApplicasterSDK
//
//  Created by Liviu Romascanu on 3/10/15.
//  Copyright (c) 2015 Applicaster. All rights reserved.
//

#import "APInstagramModel.h"

@interface APInstagramUser : APInstagramModel

/**
 Instagram user name
 */
@property (nonatomic, weak, readonly) NSString *userName;

/**
 Profile Image URL in String form
 */
@property (nonatomic, weak, readonly) NSString *profilePictureURLString;

/**
 Full user name
 */
@property (nonatomic, weak, readonly) NSString *fullName;

/**
 Unique User Identifier
 */
@property (nonatomic, weak, readonly) NSString *uniqueID;

@end
