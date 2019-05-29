//
//  APStoreKitProducts.h
//  applicaster
//
//  Created by Philip Kramarov on 4/15/15.
//  Copyright (c) 2015 Applicaster Ltd. All rights reserved.
//

#import <Foundation/Foundation.h>
@import StoreKit;

@interface APStoreKitProducts : NSObject

/**
 *  Cached SKProduct for product identifier.
 *
 *  @param productIdentifier The product identifier of the in-app purchase product in the App Store.
 *
 *  @return SKProduct object that was cached.
 */
+ (SKProduct *)productForProductIdentifier:(NSString *)productIdentifier;

/**
 *  Retrive SKProducts from itunes connect for productIdentifiers.
 *
 *  @param productIdentifiers Array of product identifiers of the in-app purchase products in the App Store.
 *  @param completionBlock    The completionBlock will be call with array of SKProducts and SKProductsResponse. The completion block will return synchronic if the SKProducts were loaded otherwise the block will be call after the all products are loaded.
 */
+ (void)productsForProductIdentifiers:(NSArray *)productIdentifiers
                  withCompletionBlock:(void (^)(NSArray *array, SKProductsResponse *response))completionBlock;

/**
 *  Localized price of the productIdentifier. If the productIdentifier is loaded the completionBlock will be called return synchronic.
 *
 *  @param productIdentifier The product identifier of the in-app purchase product in the App Store.
 *  @param completionBlock The completionBlock will be call with localized price and SKProduct. The completion block will return synchronic if the productIdentifier was loaded otherwise the block will be call after the product will be loaded.
 */
+ (void)localizedPriceForProductWithProductIdentifier:(NSString*)productIdentifier
                           withCompletionBlock:(void (^)(NSString *price, SKProduct *product))completionBlock;

@end
