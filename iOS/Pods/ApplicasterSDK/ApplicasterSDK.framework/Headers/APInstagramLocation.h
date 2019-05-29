//
//  APInstagramLocation.h
//  ApplicasterSDK
//
//  Created by Liviu Romascanu on 3/10/15.
//  Copyright (c) 2015 Applicaster. All rights reserved.
//

#import "APInstagramModel.h"

@interface APInstagramLocation : APInstagramModel

/**
 Latitude
 */
@property (nonatomic, weak, readonly) NSString *latitude;

/**
 Longitude
 */
@property (nonatomic, weak, readonly) NSString *longitude;

/**
 Location name if available
 */
@property (nonatomic, weak, readonly) NSString *name;

/**
 Unique location Identifier if available
 */
@property (nonatomic, weak, readonly) NSString *uniqueID;

@end
