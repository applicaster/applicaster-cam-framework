//
//  APPurchasableItem.h
//  applicaster
//
//  Created by Guy Kogus on 5/01/12.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "APModel.h"

/**
 APPurchasableItem represents all objects that can be purchased.
 Current objects that implement it are Category and VOD item
 */
@interface APPurchasableItem : APModel {
	
}

/**
 An array of associated Products to the purchasable item.
 Used to return more then one product identifier that are relevant to a specific item.
 For example - you can have different purchase options for a chapter , season and series.
 */
@property (nonatomic, strong, readonly) NSArray *associatedProductIdentifiers;

/**
 Returns an Array containing all the UniqueIDs of the authorization providers that this pruchasable item accepts.
 If the key doesnt exist in the object dictionary - will return empty array.
 */
@property (nonatomic, unsafe_unretained, readonly) NSArray *authorizationProvidersIDs;

/**
 Returns the purchaseParams in a dictionary of voucher template IDs
*/
- (NSDictionary*)storeKitPurchaseParamsByVoucherTemplateIDs;

/**
 Checks if Item is free
 @return YES if item is free
 */
- (BOOL)isFree;

/**
 @return YES when the item is owned (or free) Otherwise returns NO
 */
- (BOOL)isOwned;

/**
 Returns a price strine
 @return price
 */
- (NSString*)price;

// Test functionality
- (NSArray*)ownershipSearchPathsForOwnership:(int)ownership;

/**
 Call this method in order to attemp to purchase this item.
 
 @param error - error which you can return.

 @return YES if was handled, NO otherwise.
 */
- (BOOL)attemptToPurchaseWithError:(NSError **)error;

/**
 Authorization provider headers to add to a purchasable item load
 @return NSDictionary to add to the request headers or nil
 */
- (NSDictionary *)authorizationProvidersHeaders;

@end
