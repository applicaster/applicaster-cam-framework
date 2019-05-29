//
//  APSirenFactory.h
//  SirenParser
//
//  Created by Anton Kononenko on 3/11/15.
//  Copyright (c) 2015 Anton Kononenko. All rights reserved.
//

#import <Foundation/Foundation.h>
@class APSirenEntity;

#pragma mark - Siren Structure Definitions

static NSString *const SirenStructureTitleKey      = @"title";
static NSString *const SirenStructureClassKey      = @"class";
static NSString *const SirenStructurePropertiesKey = @"properties";
static NSString *const SirenStructureEntitiesKey   = @"entities";
static NSString *const SirenStructureActionsKey    = @"actions";
static NSString *const SirenStructureLinksKey      = @"links";
static NSString *const SirenStructureRelationsKey  = @"rel";
static NSString *const SirenStructureHrefKey       = @"href";

@interface APSirenFactory : NSObject

/**
 *  Convert JSON Siren Dictionary to APSirenEntity
 *
 *  @param json JSON Siren Dictionary instance
 *  @param parentEntity Parent APSirenEntity instance
 *  @param completion   Has two params. 1. Error: not nil if there was a problem during conversion. 2. Converted APSirenEntity instance, nil if empty or has Errors
 */
+ (void)convertJSONToSirenEntity:(NSDictionary *)json
                    parentEntity:(APSirenEntity *)parentEntity
               completionHandler:(void (^)(NSError *error, APSirenEntity *rootSirenEntity))completion;

/**
 @return Base URL
 */
+ (NSString *)baseURL;

/**
 Base URL that will be used if set. Prefix of any hRef link.
 */
+ (void)setBaseURL:(NSString *)baseURL;

@end
