//
//  APCollection.h
//  applicaster
//
//  Created by Liviu Romascanu on 11/25/13.
//  Copyright (c) 2013 Applicaster Ltd. All rights reserved.
//

#import "APModel.h"

/**
 APCollection is a model that can contain multiple types of children as it's Collection Items:
 Vod Item , Category , Channel , Collection.
 */
@interface APCollection : APModel

/**
 Collection title
 */
@property (nonatomic, readonly, strong) NSString *title;

/**
 Collection description
 */
@property (nonatomic, readonly, strong) NSString *collectionDescription;

/**
 Collection Items Array
 Returns objects of different types
 */
@property (nonatomic, readonly, strong) NSArray *collectionItems;

/**
 Collection Items Metadata Array
 Returns an array of APCollectionItemMetadata objects
 */
@property (nonatomic, readonly, strong) NSArray *collectionItemsMetadataArray;

/**
 Loaded pages ID - in NSNumber
 */
@property (nonatomic, strong) NSMutableDictionary *loadedPages;

/**
 Number of pages.
 Available only after a load operation
 */
@property (nonatomic, assign) NSInteger numberOfPages;


/**
 Load List of collections with the current account - APApplicasterController sharedInstance account ID
  @param completion handler - collection will be nil if loading failed
 */
+ (void)loadCollectionListWithCompletionHandler:(void (^)(NSArray *collectionsArray))completion;

/**
 Search specific collection by UI Tag from collection list
 @param uiTag UITag of APCollection
 @param collectionList Array of APCollection instances
 */
+ (APCollection *)collectionItemWithUITag:(NSString *)uiTag fromCollectionList:(NSArray *)collectionList;

/**
 Load collection item with a page and completion handler
 Do note - if the page is already loaded - it will not reload it.
 @param page number in integer - NOTE - the first page is 1! not 0!
 @param completion that returns an array of all the collection items - not only the loaded page
 */
- (void)loadCollectionItemsWithPage:(NSInteger)page andCompletionHandler:(void(^)(APCollection *collection))completion;

/**
 Load All pages of a certain completion
 Use with caution!
 @param completion block that will be returned after all the pages are loaded
 */
- (void)loadAllCollectionItemsWithCompletionHandler:(void(^)(APCollection *collection))completion;

/**
 Is a certain page loaded - quick convinience method
 @param page index
 @return YES if page is already loaded.
 */
- (BOOL)isPageLoaded:(NSInteger)page;

/**
 Search child Model by UI Tag
 @param uiTag UITag of APCollection
 @return instance of APModel if find or nil
 */
- (APModel *)childByUITag:(NSString *)uiTag;

/**
 Clears cache for the current collection.
 */
- (void)clearCache;

/**
 Clears all cache for collections.
 */
+ (void)clearAllCache;

/**
 Deprecated functions.
 The following function list should NOT be used on a collection.
 While relevant for APModel - These are no longer supported for collection.
 Collection should be either obtained from the collection list on the account or as a child of a collection
 Loading should be done with the paging mechanism.
 */

- (void)load __attribute__ ((deprecated));

- (void)cancel __attribute__ ((deprecated));
- (BOOL)isLoading __attribute__ ((deprecated));
- (BOOL)isLoaded __attribute__ ((deprecated));
- (void)addLoadingObserver:(id <APModelObserver>)observer __attribute__ ((deprecated));
- (void)removeLoadingObserver:(id <APModelObserver>)observer __attribute__ ((deprecated));
@end
