//
//  APInstagramPagination.h
//  ApplicasterSDK
//
//  Created by Liviu Romascanu on 3/10/15.
//  Copyright (c) 2015 Applicaster. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "APInstagramModel.h"

@interface APInstagramPagination : APInstagramModel

/**
 Next Maximum tag
 */
@property (nonatomic, weak, readonly) NSString *nextMaxTag;

/**
 Minimum Item tag
 */
@property (nonatomic, weak, readonly) NSString *minTagID;

/**
 Next page URL to paginate the request
 */
@property (nonatomic, weak, readonly) NSString *nextURLString;

@end
