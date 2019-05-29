//
//  APInstagramCommentsCollection.h
//  ApplicasterSDK
//
//  Created by Liviu Romascanu on 3/10/15.
//  Copyright (c) 2015 Applicaster. All rights reserved.
//

#import "APInstagramModel.h"

@interface APInstagramCommentsCollection : APInstagramModel

/**
 Number of items in NSNumber form
 */
@property (nonatomic, assign) NSUInteger count;

/**
 Raw form of captions in Dictionary form
 */
@property (nonatomic, weak, readonly) NSArray *dataArray;

/**
 Array of APInstagramCaption
 */
@property (nonatomic, weak, readonly) NSArray *captionsArray;

@end
