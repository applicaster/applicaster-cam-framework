//
//  APTwitterUser.h
//  ApplicasterSDK
//
//  Created by David Brownstone on 7/22/14.
//  Copyright (c) 2014 Applicaster. All rights reserved.
//

#import <Foundation/Foundation.h>

@interface APTwitterUser : NSObject

/**
 Twitter username.
 */
@property (nonatomic, strong, readonly) NSString *username;

/**
 The image URL for this Twitter user.
 */
@property (nonatomic, strong, readonly) NSString *imageURL;

/**
 initialize the model using the username
 */
- (id)initWithUsername:(NSString *)username
           andImageURL:imageURL;

@end
