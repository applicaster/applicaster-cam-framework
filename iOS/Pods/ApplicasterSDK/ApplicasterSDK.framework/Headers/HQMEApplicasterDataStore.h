//
//  HQMEApplicasterDataStore.h
//  applicaster
//
//  Created by Tom Susel on 1/4/11.
//  Copyright 2011 __MyCompanyName__. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "APASIHTTPRequestDelegate.h"
#import "APAccount.h"

@class APBroadcaster, APASINetworkQueue, APVodItem, APEndUserProfile, APCategory, APAccount, APItemList;

/**
 An object that holds all of the necessary applicaster objects for offline mode.
 */
@interface HQMEApplicasterDataStore : NSObject <APASIHTTPRequestDelegate>{
	APAccount *_account;	
	
	__strong APASINetworkQueue *_networkQueue;
    
    NSMutableArray *_locallyStoredItems;
    NSMutableArray *_locallyStoredItemIDs;
}

@property (nonatomic, strong) APAccount *account;
@property (nonatomic, strong) NSMutableArray *locallyStoredItems;
@property (nonatomic, strong) NSMutableArray *locallyStoredItemIDs;

/**
 Deletes all of the locally stored data.
 */
- (void)clearStore;



/**
 Returns the singleton instance
 @returns The singleton instance.
 */
+ (id)sharedInstance;

/**
 Retrieves the local path for a type of image for a VOD item.
 @param vodItem The VOD item.
 @param imageName The name of the image, i.e. thumbnail
 @returns The local path for an image with a certain name
 */
- (NSString*)imagePathForVodItem:(APVodItem*)vodItem
                        withName:(NSString*)imageName;

/**
 Return image path for category item.
 @param category The category.
 @param imageName The name of the image.
 @return The full path of the image.
 */
- (NSString*)imagePathForCategoryItem:(APCategory*)category
                             withName:(NSString*)imageName;

/**
 Saves the vod item locally.
 @param aVodItem The VOD item to be saved to disk.
 */
- (void)saveVodItemLocally:(APVodItem*)aVodItem;

/**
 Save the end user profile to local disk.
 @param endUserProfile The end user profile.
 */
- (void)saveEndUserProfile:(APEndUserProfile *)endUserProfile;

/**
 Get the end user profile that has been saved to disk.
 @return The end user profile.
 */
- (APEndUserProfile *)retrieveEndUserProfileFromDisk;

/**
 Retrieves the vod item from the local store.
 @param vodItemID The unique ID of the VOD item.
 @return The VOD item.
 */
- (APVodItem*)vodItemForID:(NSString*)vodItemID;

//Liviu
/**
 Saves a given broadcaster locally.
 It will use the APBroadcaster directory and use the APBroadcaster's unique ID for the naming convension
 @param broadcaster to be saved
 */
- (void)saveBroadcasterLocally:(APBroadcaster *)broadcaster;

/** 
 Get broadcaster by unique ID and returns broadcaster from file if exists.
 If file does not exist - returns nil
 @param broadcasterID The broadcaster's unique ID.
 @return Broadcaster object from file
 */
- (APBroadcaster *)getBroadcasterbyID:(NSString *)broadcasterID;


/**
 Saves a given category locally
 It will use the APCategory directory and use the itemlist's unique ID for the naming convension
 Also - in case the HQME state is online - the items will be fetched
 @param category The category to be saved.
 */
- (void)saveCategoryLocally:(APCategory*)category;

/** 
 Get category by unique ID and returns category from file if exists.
 if file does not exist - returns nil
 @param categoryID The unique ID of the category to retrieve from file.
 @return Item list from file or nil if not found.
 */
- (APCategory*)getCategorybyID:(NSString *)categoryID;

/**
 Get local category by name
 @param name The name of the category.
 @return Item list from file or nil if not found.
 */
-(APCategory *)getCategoryByName:(NSString *)name;

/**
 Saves a given item list locally
 It will use the APItemList directory and use the itemlist's unique ID for the naming convension
 Also - in case the HQME state is online - the items will be fetched
 @param anItemsList The item list to be saved locally.
 */
- (void)saveItemListLocally:(APItemList*)anItemsList;

/** 
 Get item list by unique ID and returns item list from file if exists.
 If file does not exist - returns nil
 @param itemListID The unique ID of the item list to be retrieved.
 @return The item list from file.
 */
- (APItemList*)getItemListbyID:(NSString *)itemListID;

/**
 Retrieve all the VOD items in a specific category.
 @param category The category to search.
 @return items for category from disk
 */
- (NSArray*)vodItemsForCategory:(APCategory *)category;

/**
 Gets APModel , tries to load it from disk
 @param APModel to be fetched
 @return if the model is empty - return NO if the model is found - return YES and sets object with dictionary
 */
- (BOOL)tryLoadingAPModelFromFile:(APModel *)model;

/**
 Gets Account and returns account from file
 @param APAccount to be fetched
 @return if the model is empty - return NO if the model is found - return YES and sets object with dictionary
 */
- (BOOL)tryLoadingAPAccountFromFile:(APAccount *)anAccount;


/**
 cleanUpLocalDataStore
 This function runs on Content category for current Broadcaster from the APApplicaster currentBroadcaster property
 Deletes all categories with no hqme vod items underneath
 during this - deletes all expiered / nonhqme vod items and data (if any is saved)
 */
- (void)cleanUpLocalDataStore;

/** 
 Same as cleanUpLocalDataStore - but with configurable category name
 @param name for category to delete
 */
- (void)cleanUpLocalDataStoreForCategoryName:(NSString *) name;

/**
 Call this method in order to delete all the data that the given vod item is using (Images, pre/post rolls etc...)
 
 @param vodItem - the vod item that it's data you wish to delete.
 */
- (void)deleteDataForVodItem:(APVodItem*)vodItem;

/** 
 Checks if a model has offline content by checking if it's dictionary exists
 @param model The model to check.
 */
- (BOOL)hasOfflineContent:(APModel *)model;

/**
 checks if a VOD item is hqme enabled and returns yes / no
 Loads item from disk
 @param vodItemID The unique ID for the VOD item.
 @return Yes if succeded in loading - no otherwise
 */
- (BOOL)isVodItemHQMEEnabled:(NSString *) vodItemID;

/**
 Returns an array of locally stored vod items
 @return Array of VOD items
 */
- (NSArray *)getAllLocalVodItems;

/** 
 Store Local file ID's to disk
 */
- (void)writeIDsToFile;

/**
 Get back a local NSURL for preload by name
 @param preLoadName string
 @return NSURL of a localpath
 */
- (NSURL *)getLocalURLForPreload:(NSString *)preloadName withType:(APPreloadURLType)type;

/**
 Get back a local NSURL for preload by name
 @param preLoadName string
 @return NSURL of a localpath
 */
- (NSURL *)getLocalURLForPreroll:(NSString *)prerollURL;
/**
 Get back a local NSURL for preload by name
 @param preLoadName string
 @return NSURL of a localpath
 */
- (NSURL *)getLocalURLForSplash:(NSString *)splashURL;

#pragma mark - Deprecated

/**
 Post HQME Metrics to server - Deprecated - Should not be used
 */
- (void)postHQMEMetrics;

@end
