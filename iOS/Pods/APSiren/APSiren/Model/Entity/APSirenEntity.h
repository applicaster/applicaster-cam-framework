//
//  APSirenEntity.h
//  SirenParser
//
//  Created by Anton Kononenko on 3/11/15.
//  Copyright (c) 2015 Anton Kononenko. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <APSiren/APSirenLinkEntity.h>

@interface APSirenEntity : APSirenLinkEntity <NSCoding>

/**
 *  Instance of parent Entity
 *  Not nil in case entity has a parent
 */
@property (nonatomic, strong) APSirenEntity *parentEntity;

/**
 *  Array of NSString instances
 *  Representation type of Siren class
 *  @note By Siren conventions this property should be NSString array only
 */
@property (nonatomic, strong) NSArray *classes;

/**
 *  Entity properties
 *  Can contain Any object parsed from json - NSString, NSArray, NSDictionary, NSNumber
 */
@property (nonatomic, strong) NSDictionary *properties;

/**
 *  Array of APSirenEntities instances
 *  Children of entity
 *  @note This property should be APSirenEntities array only
 *  @see APSirenEntity
*/
@property (nonatomic, strong) NSArray *entities;

/**
 *  Array of APSirenLink instances
 *  @see APSirenLink
*/
@property (nonatomic, strong) NSArray *links;

/**
 *  Array of APSirenActions instances
 *  Not implemented
 */
@property (nonatomic, strong) NSArray *actions;

/**
* Used to override default property instance with class type
* @note Should be of class NSDictionary otherwise, this class will not be used
*
*  @note @b expectedPropertyClass should be of NSDictionary class. Otherwise it will not be used.
*  This convenience property was created to separate possible property parameters for different entity types.
*  @b Example: ComponentEntity and AppDefineEntity probably will have different property types
*/
@property(nonatomic, strong) Class expectedPropertyClass;

#pragma mark - Public Methods
/**
 *  Creates new APSirenEntity instance with URL
 *
 *  @param url Use to load data from json and parse it
 *
 *  @note   This method throws an exception if the URL string is nil.
 *  @return Created APSirenEntity instance
 */
- (instancetype)initWithURL:(NSURL *)url;

/**
 *  Creates new APSirenEntity instance with URL
 *
 *  @param url Use to load data from json and parse it
 *
 *  @return Created APSirenEntity instance. In case url is nil, return nil
 */
+ (instancetype)entityWithURL:(NSURL *)url;


/**
 *  Loads JSON and fills entity with data.
 *
 *  @param sessionConfiguration Custom configuration for NSURLSession
 *  @param completion NSError: Returns error if was problems during loading or parsing process. APSirenEntity: Return APSirenEntity instance if loading and parse was completed without problems, otherwise nil.
 *  @note  If sessionConfiguration is nil, NSURLSession will use default configuration
 */
- (void)loadWithConfiguration:(NSURLSessionConfiguration *)sessionConfiguration completionHandler:(void (^)(NSError *error, APSirenEntity *sirenEntity))completion;

#pragma mark - Fetching Entities
/**
 *  Search first entity object inside entity with requested class name
 *
 *  @param className that supposed to be searched
 *
 *  @return APSirenEntity if object was found other case nil
 */
-(APSirenEntity *)firstEntityByClassName:(NSString *)className;

/**
 *  Search entities inside entity with requested class name
 *
 *  @param className that supposed to be searched
 *
 *  @return NSArray of APSirenEntities instances if at least one object was found, otherwise nil
 */
-(NSArray *)entitiesByClassName:(NSString *)className;

/**
 *  Search first entity inside entity with requested relation name
 *
 *  @param relation that supposed to be searched
 *
 *  @return APSirenEntity if object was found otherwise nil
 */
-(APSirenEntity *)firstEntityByRelation:(NSString *)relation;

/**
 *  Search entity inside entity with requested relations name
 *
 *  @param relation that supposed to be searched
 *
 *  @return NSArray of APSirenEntities instances if at least one object was found, otherwise nil
 */
-(NSArray *)entitiesByRelation:(NSString *)relation;

/**
 *  Search first object with required className and relation.
 *
 *  @param className that supposed to be searched
 *  @param relation that supposed to be searched
 *
 *  @return APSirenEntity if object was found otherwise nil
 */
-(APSirenEntity *)firstEntityByClassName:(NSString *)className
                                relation:(NSString *)relation;

/**
*  Search objects object with required className and relation.
 *
 *  @param className that supposed to be searched
 *  @param relation that supposed to be searched
 *
 *  @return NSArray of APSirenEntities instances if at least one object was found, other case nil
 */
-(NSArray *)entitiesByClassName:(NSString *)className
                       relation:(NSString *)relation;
@end
