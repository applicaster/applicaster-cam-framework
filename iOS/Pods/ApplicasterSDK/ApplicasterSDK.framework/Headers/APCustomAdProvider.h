//
//  APCustomAdProvider.h
//  applicaster
//
//  Created by Guy Kogus on 17/01/13.
//  Copyright (c) 2013 Applicaster Ltd. All rights reserved.
//

#import "APAdProvider.h"

/**
 This is the custom ad provider that will be used by the <APAdvertiser> object when it registers a custom ad provider in the CMS.
 */
@interface APCustomAdProvider : APAdProvider

@property (nonatomic, strong) NSArray *customFields;

/**
 Initialise the custom ad provider with the given custom fields.
 @param customFields The 5 custom fields filled in the CMS.
 */
- (id)initWithCustomFields:(NSArray *)customFields;

@end
