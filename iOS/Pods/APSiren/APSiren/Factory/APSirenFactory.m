//
//  APSirenFactory.m
//  SirenParser
//
//  Created by Anton Kononenko on 3/11/15.
//  Copyright (c) 2015 Anton Kononenko. All rights reserved.
//

#import "APSirenFactory.h"
#import "APSirenParser.h"
#import "NSObject+APSirenAdditions.h"

static NSString *kDefaultBaseURL = @"";

@interface APSirenFactory ()

/**
*  Conversion JSON Object To APSirenEntity
*
*  @param json   JSON Siren Dictionary object
*  @param parentEntity Parent APSirenEntity instance
*
*  @return Converted APSirenEntity instance, nil if empty or has errors
*/
+ (APSirenEntity *)sirenEntityWithJSON:(NSDictionary *)json
                          parentEntity:(APSirenEntity *)parentEntity;

/**
 *  Retrieve object from NSDictionary for expected class.
 *
 *  @param json          JSON Siren Dictionary object
 *  @param expectedClass Checks if retrieved value is kind of selected class
 *  @param key           Will used to get value from json
 *
 *  @returns an Object from NSDictionary if it is of expected class and not empty otherwise returns nil
 */
+ (id)retrieveObjectFromJSON:(NSDictionary *)json
               expectedClass:(Class)expectedClass
                         key:(NSString *)key;

/**
 *  Retrieve entities from NSDictionary and creates APSirenEntities
 *
 *  @param json        JSON Siren Dictionary object
 *  @param parentSirenEntity Used to add parent entity for new APSirenEntities
 *
 *  @returns NSArray of siren entities, nil if no siren entities.
 */
+ (NSArray *)retrieveSirenEntitiesFromJSON:(NSDictionary *)json
                         parentSirenEntity:(APSirenEntity *)parentSirenEntity;

/**
 *  Retrieve links from NSDictionary and creates APSirenLinks
 *
 *  @param json        JSON Siren Dictionary object
 *
 *  @returns NSArray of APSirenLinks, nil if no APSirenLinks
 *  @see APSirenLink
 */
+ (NSArray *)retrieveLinksFromJSON:(NSDictionary *)json;

#pragma mark - Helper methods

@end

@implementation APSirenFactory

#pragma mark - Public methods

+ (NSString *)baseURL {
    return kDefaultBaseURL;
}

+ (void)setBaseURL:(NSString *)baseURL {
    kDefaultBaseURL = baseURL;
}

+ (void)convertJSONToSirenEntity:(NSDictionary *)json
                    parentEntity:(APSirenEntity *)parentEntity
               completionHandler:(void (^)(NSError *error, APSirenEntity *sirenEntity))completion {
    if ([json isKindOfClass:[NSDictionary class]]) {
        APSirenEntity *sirenEntity = [self sirenEntityWithJSON:json
                                                  parentEntity:parentEntity];
        completion(nil, sirenEntity);
    } else {
        NSError *error = [NSError errorWithDomain:NSInvalidArgumentException
                                             code:0
                                         userInfo:@{NSLocalizedDescriptionKey : @"Sender should be NSDictionary format, regarding Siren convension"}];
        completion(error, nil);
    }
}

#pragma mark - Private methods

+ (APSirenEntity *)sirenEntityWithJSON:(NSDictionary *)json
                          parentEntity:(APSirenEntity *)parentEntity {
    APSirenEntity *retVal = nil;

    if (json) {
        retVal = [APSirenEntity new];

        if ([parentEntity isKindOfClass:[APSirenEntity class]] && [parentEntity isNotEmpty]) {
            retVal.parentEntity = parentEntity;
        }

        retVal.title = [self retrieveObjectFromJSON:json
                                      expectedClass:[NSString class]
                                                key:SirenStructureTitleKey];

        retVal.classes = [self retrieveObjectFromJSON:json
                                        expectedClass:[NSArray class]
                                                  key:SirenStructureClassKey];

        retVal.properties = [self retrieveObjectFromJSON:json
                                           expectedClass:[NSDictionary class]
                                                     key:SirenStructurePropertiesKey];

        retVal.entities = [self retrieveSirenEntitiesFromJSON:json
                                            parentSirenEntity:retVal];

        retVal.actions = [self retrieveObjectFromJSON:json
                                        expectedClass:[NSArray class]
                                                  key:SirenStructureActionsKey];

        retVal.links = [self retrieveLinksFromJSON:json];
        
        NSString *hRefRoute = [self retrieveObjectFromJSON:json
                                        expectedClass:[NSString class]
                                                  key:SirenStructureHrefKey];
        if (hRefRoute) {
            retVal.hRef = [kDefaultBaseURL stringByAppendingPathComponent:hRefRoute];
        }

        retVal.relations = [self retrieveObjectFromJSON:json
                                          expectedClass:[NSArray class]
                                                    key:SirenStructureRelationsKey];

        if (![retVal isNotEmpty]) {
            retVal = nil;
        }
    }
    return retVal;
}

+ (id)retrieveObjectFromJSON:(NSDictionary *)json
               expectedClass:(Class)expectedClass
                         key:(NSString *)key {
    id retVal = nil;
    if ([key isNotEmpty]) {
        NSObject *retrievedObject = json[key];
        if ([retrievedObject isKindOfClass:expectedClass] && [retrievedObject isNotEmpty]) {
            retVal = retrievedObject;
        }
    }
    return retVal;
}

+ (NSArray *)retrieveSirenEntitiesFromJSON:(NSDictionary *)json
                         parentSirenEntity:(APSirenEntity *)parentSirenEntity {
    NSArray *retVal = nil;
    NSArray *entities = [self retrieveObjectFromJSON:json
                                       expectedClass:[NSArray class]
                                                 key:SirenStructureEntitiesKey];
    if ([entities isNotEmpty]) {
        __block NSMutableArray *sirenEntities = [NSMutableArray new];
        for (NSDictionary *entityDictionary in entities) {
            [APSirenFactory convertJSONToSirenEntity:entityDictionary
                                        parentEntity:parentSirenEntity
                                   completionHandler:^(NSError *error, APSirenEntity *sirenEntity) {
                                       if (sirenEntity) {
                                           [sirenEntities addObject:sirenEntity];
                                       }
                                   }];
        }
        if ([sirenEntities isNotEmpty]) {
            retVal = [sirenEntities copy];
        }
    }
    return retVal;
}

+ (NSArray *)retrieveLinksFromJSON:(NSDictionary *)json {
    NSArray *retVal = nil;
    NSArray *linksData  = [self retrieveObjectFromJSON:json
                                         expectedClass:[NSArray class]
                                                   key:SirenStructureLinksKey];
    NSMutableArray *sirenLinks = [NSMutableArray new];

        for (NSDictionary *linkDictionary in linksData) {
            if ([linkDictionary isKindOfClass:[NSDictionary class]]) {
                APSirenLinkEntity *sirenLinkEntity = [APSirenLinkEntity new];
                sirenLinkEntity.title = [self retrieveObjectFromJSON:linkDictionary
                                                       expectedClass:[NSString class]
                                                                 key:SirenStructureTitleKey];
                NSString *hRefRoute = [self retrieveObjectFromJSON:linkDictionary
                                                      expectedClass:[NSString class]
                                                                key:SirenStructureHrefKey];
                if (hRefRoute) {
                    sirenLinkEntity.hRef = [kDefaultBaseURL stringByAppendingPathComponent:hRefRoute];
                }
                
                sirenLinkEntity.relations = [self retrieveObjectFromJSON:linkDictionary
                                                           expectedClass:[NSArray class]
                                                                     key:SirenStructureRelationsKey];
                if ([sirenLinkEntity isNotEmpty]) {
                    [sirenLinks addObject:sirenLinkEntity];
                }
            }
        }
    if ([sirenLinks isNotEmpty]) {
        retVal = sirenLinks;
    }

    return retVal;
}

@end
