//
//  APCategory.h
//  applicaster
//
//  Created by Guy Kogus on 5/01/12.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "APFavoritesManager.h"
#import "APShareable.h"

typedef NS_ENUM(NSInteger, APCategoryNature) {
    APCategoryNatureUnknown,
    APCategoryNatureShow,
    APCategoryNatureSeason,
    APCategoryNatureTopLevel,
    APCategoryNatureGeneric,
    APCategoryNatureLink,
    APCategoryNatureAtomFeed,
    APCategoryNatureItemList
};

/**
 APCategory Represents a model that holdes one of the following 3 types of data:
 1. Link Category - A Category holding a link. This should be used to avoid hard coding links in places in the application and to add categories that contains outside links to other apps , web pages etc.
 2. Category with Subcategories - In this case the Children array exists (not cashed) containing other categories.
 3. Category with VOD Items - In this case the Children array exists (not cashed) containing VOD items.
 
 Please note: While some of the data comes with the category when not loaded (for example - when you get it as a subcategory infro from a parent category),
 Some of the info that a category contains requieres loading the category (For example - the children array).
 A Category should be loaded before used as a data source.
 */
@interface APCategory : APModel <APFavoritesProtocol, APUICustomizationExtendedProtocol, APShareable> {
	NSArray *_children;
}

#pragma mark - Properties
/**
 Category Name
 */
@property (unsafe_unretained, readonly) NSString *name;

/**
 Category description text
 */
@property (unsafe_unretained, readonly) NSString *categoryDescription;

/**
 Broadcaster ID under which the category resides
 */
@property (unsafe_unretained, readonly) NSString *broadcasterID;

/**
 Top level category ID.
 */
@property (unsafe_unretained, readonly) NSString *topLevelCategoryID;

/**
 Parent Category ID
 */
@property (unsafe_unretained, readonly) NSString *parentID;

/**
 Show name
 */
@property (nonatomic, strong, readonly) NSString *showName;

/**
 Season name
 */
@property (nonatomic, strong, readonly) NSString *seasonName;

/**
Top Level Category name
*/
@property (nonatomic, weak, readonly) NSString *topLevelCategoryName;

/**
 Category Preroll URL that should be used with the category children.
 This will be used unless a child category / VOD item has a different value.
 */
@property (unsafe_unretained, readonly) NSString *defaultPrerollURL;

/**
 Category Splash Image URL that should be used with the category children.
  This will be used unless a child category / VOD item has a different value.
 */
@property (unsafe_unretained, readonly) NSString *defaultSplashURL;

/**
 Category Model URL
 */
@property (unsafe_unretained, readonly) NSString *URL;

/**
 Category Link dictionary - Can be used with APTimedWebViewController
 */
@property (unsafe_unretained, readonly) NSDictionary *linkDictionary;

/**
 Children array.
 This array is filled with data only after the category is loaded
 */
@property (unsafe_unretained, readonly) NSArray  *children;

/**
 In case the category is a link category - This value will return the link url.
 This value is cached - A category doesn't need to be loaded to use this
 */
@property (unsafe_unretained, readonly) NSString *linkURL;

/**
 Returns YES if category is free
 */
@property (nonatomic, readonly, getter= isFree) BOOL free;

/**
 Returns broadcast times.
 This is a string value incerted in the CMS - not a time object
 */
@property (unsafe_unretained, readonly) NSString *broadcastTimes;

/**
 User Generated content HTML
 */
@property (unsafe_unretained, readonly) NSString *ugcHtml;

/**
 Widget typ (used for UGC)
 */
@property (unsafe_unretained, readonly) NSString *widgetType;

/**
 The Facebook object ID for comments.
 */
@property (unsafe_unretained, readonly) NSString *facebookObjectID;

/**
 Returns the category nature - Show , Season , Generic, Link, Atom Feed
 */
@property (unsafe_unretained, readonly) APCategoryNature categoryNature;

/*
 The category will stay in the cache after it was loaded and not removed after expiration time.
 */
@property (nonatomic, assign) BOOL isPersistent;

/**
 Category Top Level dictionary - Can be used with GAAnalyticsManager
 */
@property (weak, readonly) NSDictionary *topLevelCatagoryDictionary;

/**
 Checks if the category children are VOD items
 @return YES if the category contains VOD items
 */
- (BOOL)containsVodItems;

/**
 Checks if the category children are Categories items
 @return YES if the category contains Categories
 */
- (BOOL)containsCategories;

/**
 Child by UI Tag returns an APModel containing the UI tag handed to the function.
 @param uiTag string to be matched
 @return Either a APCategory or APVodItem. If none are found / Children are not loaded - nil is returned
 */
- (APModel *)childByUITag:(NSString *)uiTag;

/**
 Checks if an image exists lcoally and returns it
 @param name of the image from the Category Image Dictionary
 @return UIImage object if image exists or nil if it does not.
 */
- (UIImage*)localImageForName:(NSString*)name;

//Check Fucntionality
+ (NSString *)URL;

/**
 Checks if the category contains downloaded items
 @return BOOL if the category contains downloaded items
 */
-(BOOL)hasDownloadedVods;

/**
 Checks if the category contains url dictionary
 @return BOOL if the category contains url dictionary
 */
-(BOOL)isURLType;

/**
 Empty hashmap
 */
+(void)emptyLoadedCategoriesList;

/**
 Clears cache for the current category.
 */
- (void)clearCache;

/**
 This methods loads the category from cache if cached.
 @return BOOL if category was cached and loaded.
 */
- (BOOL)loadFromCache;

/**
 Retrieves programs that are connected to the show in from date with pages.
 Each page can contains up to 50 items. The date should be passed timeless and in local time.
 @param fromDate The date that we want to receive the programs from this date.
 @param page The page number.
 @param completion The completion handler to be run when the programs are loaded
 with params of requested model, array of the programs and BOOL of has next page or not.
 @param forceReload forces method to load from server and not from cache.
 */
- (void)showProgramsFromDate:(NSDate *)fromDate
                        page:(NSUInteger)pageNumber
                  completion:(void (^)(APCategory *model, NSArray *programs, BOOL hasNextPage))completion
                 forceReload:(BOOL)forceReload;

/**
 Retrieves programs that are connected to the show in particular date with pages.
 Each page can contains up to 50 items. The date should be passed timeless and in local time.
 @param inDate The date that we want to receive the programs.
 @param page The page number.
 @param completion The completion handler to be run when the programs are loaded
 with params of requested model, array of the programs and BOOL of has next page or not.
 @param forceReload forces method to load from server and not from cache.
 */
- (void)showProgramsInDate:(NSDate *)inDate
                      page:(NSUInteger)pageNumber
                completion:(void (^)(APCategory *model, NSArray *programs, BOOL hasNextPage))completion
                      forceReload:(BOOL)forceReload;

/**
 Retrieves all programs that are connected to the show within a given time range.
 The dates should be passed timeless and in local time.
 @param startDate The starting point of the time range.
 @param endDate The ending point of the time range.
 @param completion The completion handler to be run when the programs are loaded
        with params of requested model and array of the programs.
 @param forceReload forces method to load from server and not from cache.
 */
- (void)showProgramsFromDate:(NSDate *)startDate
                     endDate:(NSDate *)endDate
                  completion:(void (^)(APCategory *model, NSArray *programs))completion
                 forceReload:(BOOL)forceReload;

@end
