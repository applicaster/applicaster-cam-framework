//
//  APInstagramLikesCollection.h
//  ApplicasterSDK
//
//  Created by Liviu Romascanu on 3/10/15.
//  Copyright (c) 2015 Applicaster. All rights reserved.
//

#import "APInstagramModel.h"

@interface APInstagramLikesCollection : APInstagramModel

/**
 Number of items in NSNumber form
 */
@property (nonatomic, assign) NSUInteger count;

/**
 Raw data array of users who liked
 */
@property (nonatomic, weak, readonly) NSArray *dataArray;

/**
 APInstagramUser array
 */
@property (nonatomic, weak, readonly) NSArray *usersArray;

@end
