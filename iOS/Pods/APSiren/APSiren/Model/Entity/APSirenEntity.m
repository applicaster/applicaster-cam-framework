//
//  APSirenEntity.m
//  SirenParser
//
//  Created by Anton Kononenko on 3/11/15.
//  Copyright (c) 2015 Anton Kononenko. All rights reserved.
//

#import "APSirenEntity.h"
#import "APSirenParser.h"
#import "NSObject+APSirenAdditions.h"
#import "NSArray+APSirenAdditions.h"

#pragma mark - Enums
typedef NS_ENUM(NSInteger, APSirenEntitySearchDirection) {
    APSirenEntitySearchDirectionClasses,
    APSirenEntitySearchDirectionRelation
};

@interface APSirenEntity ()

/**
 *
 */
@property (nonatomic, strong) NSURL *url;

/**
 *  Search String in the Entities array in the required direction specified
 *
 *  @param string          search string
 *  @param entitiesArray   array of the entities that method will search
 *  @param searchDirection APSirenEntitySearchDirection enum. It will take selected array from entity.
 *
 *  @return In case at least one instance was found, return NSArray instance otherwise nil.
 */
-(NSArray *)searchString:(NSString *)string
         inEntitiesArray:(NSArray *)entitiesArray
         searchDirection:(APSirenEntitySearchDirection)searchDirection;

/**
 *  Get array instance from selected entity in the requested direction.
 *
 *  @param sirenEntity     instance for searched array
 *  @param searchDirection APSirenEntitySearchDirection enum. It will take selected array from entity.
 *
 *  @return NSArray instance for selected direction in case at least once instance available in array.
 */
-(NSArray *)searchArrayFromEntity:(APSirenEntity *)sirenEntity
                  searchDirection:(APSirenEntitySearchDirection)searchDirection;
@end
@implementation APSirenEntity
@synthesize properties = _properties;

- (NSString *)debugDescription {
    return [NSString stringWithFormat:@"<entity:%@, title:%@, class:%@, rel:%@ childrenCount:%lu properties:%@> ",self, self.title, self.classes,  self.relations, (unsigned long)self.entities.count, self.properties];
}

#pragma mark - Public methods

+ (instancetype)entityWithURL:(NSURL *)url {
    id retVal = nil;
    if (url) {
        retVal = [(APSirenEntity *) [[self class] alloc] initWithURL:url];
    }
    
    return retVal;
}

- (instancetype)initWithURL:(NSURL *)url {
    if (!url) {
        [NSException raise:@"Invalid NSURL value" format:@"URL can not be nil"];
    }
    self = [self init];
    if (self) {
            self.url = url;
        }
    return self;
}

- (void)loadWithConfiguration:(NSURLSessionConfiguration *)sessionConfiguration
            completionHandler:(void (^)(NSError *error, APSirenEntity *sirenEntity))completion {
    if (self.url || self.hRef) {
        NSURL *loadURL = self.hRef ? [NSURL URLWithString:self.hRef] : self.url;
        [APSirenParserLoadingManager loadSirenWithURL:loadURL
                                        configuration:sessionConfiguration
                                    completionHandler:^(NSError *error, APSirenEntity *sirenEntity) {
                                        if (sirenEntity) {
                                            self.parentEntity = sirenEntity.parentEntity;

                                            self.title        = sirenEntity.title;
                                            self.relations    = sirenEntity.relations;
                                            self.hRef         = sirenEntity.hRef;

                                            self.classes      = sirenEntity.classes;
                                            self.properties   = sirenEntity.properties;
                                            self.entities     = sirenEntity.entities;
                                            self.links        = sirenEntity.links;
                                            self.actions      = sirenEntity.actions;
                                            self.url          = nil;
                                        }
                                        completion (error, self);
                                    }];
    } else {
        NSError *error = [NSError errorWithDomain:NSInvalidArgumentException
                                             code:0
                                         userInfo:@{ NSLocalizedDescriptionKey : @"Can not start load Siren JSON with empty URL" }];
        completion (error, self);
    }
}

#pragma mark - Fetching Entities

- (APSirenEntity *)firstEntityByClassName:(NSString *)className {
    return [[self entitiesByClassName:className] firstObject];
}

- (NSArray *)entitiesByClassName:(NSString *)className {
    return [self searchString:className
              inEntitiesArray:self.entities
              searchDirection:APSirenEntitySearchDirectionClasses];
}

- (APSirenEntity *)firstEntityByRelation:(NSString *)relation {
    return [[self entitiesByRelation:relation] firstObject];
}

- (NSArray *)entitiesByRelation:(NSString *)relation {
    return [self searchString:relation
              inEntitiesArray:self.entities
              searchDirection:APSirenEntitySearchDirectionRelation];
}

- (APSirenEntity *)firstEntityByClassName:(NSString *)className
                                 relation:(NSString *)relation {
    return [[self entitiesByClassName:className
                             relation:relation] firstObject];
}

- (NSArray *)entitiesByClassName:(NSString *)className
                        relation:(NSString *)relation {
    NSArray *entities = [self entitiesByClassName:className];

    return [self searchString:relation
              inEntitiesArray:entities
              searchDirection:APSirenEntitySearchDirectionRelation];
}

#pragma mark - Private methods
#pragma mark - Custom Setters

- (void)setParentEntity:(APSirenEntity *)parentEntity {
    _parentEntity = nil;
    if ([parentEntity isNotEmpty] && [parentEntity isKindOfClass:[APSirenEntity class]]) {
        _parentEntity = parentEntity;
    }
}

- (void)setClasses:(NSArray *)classes {
    _classes = nil;
    if ([classes isNotEmpty] && [classes isKindOfClass:[NSArray class]]) {
        _classes = [NSArray arrayWithArray:classes
                    expectedClassInObjects:[NSString class]];
    }
}

- (void)setProperties:(NSDictionary *)properties {
    _properties = nil;
    if ([properties isNotEmpty] && [properties isKindOfClass:[NSDictionary class]]) {
        _properties = properties;
    }
}


- (void)setEntities:(NSArray *)entities {
    _entities = nil;
    if ([entities isNotEmpty] && [entities isKindOfClass:[NSArray class]]) {
        _entities = [NSArray arrayWithArray:entities
                     expectedClassInObjects:[APSirenEntity class]];
    }
}

- (void)setLinks:(NSArray *)links {
    _links = nil;
    if ([links isNotEmpty] && [links isKindOfClass:[NSArray class]]) {
        _links = [NSArray arrayWithArray:links
                  expectedClassInObjects:[APSirenLinkEntity class]];
    }
}

- (void)setActions:(NSArray *)actions {
    _actions = nil;
    if ([actions isNotEmpty] && [actions isKindOfClass:[NSArray class]]) {
        _actions = actions;
    }
}

- (void)setExpectedPropertyClass:(Class)expectedPropertyClass {
    _expectedPropertyClass = nil;
    if ([expectedPropertyClass isMemberOfClass:[NSDictionary class]]) {
        _expectedPropertyClass = expectedPropertyClass;
    }
}

#pragma mark - Custom Getters

- (NSDictionary *)properties {
    NSDictionary *retVal = nil;
    if ([_properties isNotEmpty]) {
        if (self.expectedPropertyClass) {
            retVal = (NSDictionary *)[self.expectedPropertyClass dictionaryWithDictionary:_properties];
        } else {
            retVal = _properties;
        }
    }
    return retVal;
}

#pragma mark - Helpers methods

- (BOOL)emptyEntity {
    BOOL retVal = [super emptyEntity];
    if (self.classes ||
            self.properties ||
            self.entities ||
            self.links ||
            self.actions) {
        retVal = NO;
    }
    return retVal;
}

- (NSArray *)searchString:(NSString *)string
          inEntitiesArray:(NSArray *)entitiesArray
          searchDirection:(APSirenEntitySearchDirection)searchDirection {
    NSArray *retVal = nil;
    NSMutableArray *filteredArray = [NSMutableArray new];

    for (APSirenEntity *entity in entitiesArray) {

        NSArray *searchArray = [self searchArrayFromEntity:entity
                                           searchDirection:searchDirection];
        if ([searchArray existsString:string]) {
            [filteredArray addObject:entity];
        }
    }
    if ([filteredArray isNotEmpty]) {
        retVal = [filteredArray copy];
    }
    return retVal;
}

- (NSArray *)searchArrayFromEntity:(APSirenEntity *)sirenEntity
                   searchDirection:(APSirenEntitySearchDirection)searchDirection {
    NSArray *retVal = nil;
    switch (searchDirection) {
        case APSirenEntitySearchDirectionClasses:
            retVal = sirenEntity.classes;
            break;
        case APSirenEntitySearchDirectionRelation:
            retVal = sirenEntity.relations;
            break;
        default:
            break;
    }
    return retVal;
}

#pragma mark - NSCoding

- (id)initWithCoder:(NSCoder *)decoder {
    if (self = [super initWithCoder:decoder]) {
        self.parentEntity = [decoder decodeObjectForKey:@"parentEntity"];
        self.classes = [decoder decodeObjectForKey:@"classes"];
        self.properties = [decoder decodeObjectForKey:@"properties"];
        self.entities = [decoder decodeObjectForKey:@"entities"];
        self.links = [decoder decodeObjectForKey:@"links"];
        self.actions = [decoder decodeObjectForKey:@"actions"];
    }
    return self;
}

- (void)encodeWithCoder:(NSCoder *)encoder {
    [super encodeWithCoder:encoder];
    [encoder encodeObject:_parentEntity forKey:@"parentEntity"];
    [encoder encodeObject:_classes forKey:@"classes"];
    [encoder encodeObject:_properties forKey:@"properties"];
    [encoder encodeObject:_entities forKey:@"entities"];
    [encoder encodeObject:_links forKey:@"links"];
    [encoder encodeObject:_actions forKey:@"actions"];
}

@end
