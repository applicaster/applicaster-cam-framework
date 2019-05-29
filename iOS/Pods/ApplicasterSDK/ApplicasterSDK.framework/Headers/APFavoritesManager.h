//
//  APFavoritesManager.h
//  applicaster
//
//  Created by Guy Kogus on 31/08/11.
//  Copyright 2011 __MyCompanyName__. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "APModel.h"

extern NSString *const APFavoriteDidAddNotification;
extern NSString *const APFavoriteDidAddNotificationKey;
extern NSString *const APFavoriteDidRemoveNotification;
extern NSString *const APFavoriteDidRemoveNotificationKey;

extern NSString *const APLocalFavoritesUpdatedNotification; // Notification that is thrown everytime the local favorites list is changed. It is also called after loading the local favorites for the first time. The notification's object is the new favorites list. 
extern NSString *const APLocalFavoritesDidRemoveNotification; // Notification that is thrown when local favorites is added - the notification's object is the model that was added.
extern NSString *const APLocalFavoritesDidAddNotification; // Notification that is thrown when local favorites is removed - the notification's object is the model that was removed.

@class APVodItem;

@protocol APFavoritesProtocol <NSObject>

@optional

/**
 Returns a boolean value if the Model item exists in the local's favorites list
 */
@property (nonatomic, readonly) BOOL isLocalFavorite;

/**
 * Adds the model to local favorites list
 * @return BOOL value if the model was added the favorites.
 */
- (BOOL)addToLocalFavorites;

/**
 * Remove the model from local favorites list
 * @return BOOL value if the model was removed from favorites.
 */
- (BOOL)removeFromLocalFavorites;

@end

/**
 The APFavoritesManager offers a simple interface for adding and removing items to the user's Favorites profile.
 This API should almost never be used. It is better to access the Favorites methods provided directly by the APVodItem class.
 */
@interface APFavoritesManager : NSObject <APModelObserver>

/**
 This method lazily creates the shared instance of the favorites manager.
 @return The shared APFavoritesManager instance.
 */
+ (id)sharedInstance;

/**
 Add a specific VOD item to favorites.
 @param vodItem The VOD item.
 */
- (void)addVodItemToFavorites:(APVodItem *)vodItem;

/**
 Add a specific VOD item from favorites by the VOD item's ID.
 @param vodItemId The VOD item's ID.
 */
- (void)addVodItemToFavoritesByID:(NSString *)vodItemId;

/**
 Remove a specific VOD item from favorites.
 @param vodItem The VOD item.
 */
- (void)removeVodItemFromFavorites:(APVodItem *)vodItem;

/**
 Remove a specific VOD item from favorites by the VOD item's ID.
 @param vodItemId The VOD item's ID.
 */
- (void)removeVodItemFromFavoritesByID:(NSString *)vodItemId;

/**
 The VOD items set as Favorites.
 */
- (NSArray *)favorites;

#pragma mark - Local favorites

/**
 *  Adds the model to local favorites list
 *
 *  @param model model The model that will be added.
 *  @return BOOL value if succeeded.
 */
- (BOOL)addModelToFavorites:(APModel *)model;


/**
 *  Removes the model from local favorites list
 *
 *  @param model The model that will be removed.
 *  @return BOOL value if succeeded.
 */
- (BOOL)removeModelFromFavorites:(APModel *)model;


/**
 *  Check if the model is in user's local favorite.
 *
 *  @param model The model that will be looked up in favorites list.
 *  @return BOOL value of the model was found in the favorites list.
 */
- (BOOL)isLocalFavorite:(APModel *)model;

/**
 The local favorites (category, vod and etc.) saved at user's device.
 */
- (NSArray *)localFavorites;

@end
