//
//  APStoreKitPurchase.h
//  applicaster
//
//  Created by Neer Friedman on 3/15/10.
//  Copyright 2010 __MyCompanyName__. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "APModel.h"

@class APStoreKitPurchaseParams, SKPaymentTransaction, APPurchasableItem;

/**
 APStoreKitPurchase is an object used by the APStoreKit to represent a purchase and validate it against the applicaster servers
 */
@interface APStoreKitPurchase : APModel
{
	NSDictionary *_transactionParams;
}

#pragma mark - Properties

/**
 Transaction set for the APStoreKitPurchase instance
 */
@property (nonatomic, strong, readonly) SKPaymentTransaction *transaction;

/**
 Aditional parameters for verification agains Applicaster servers
 */
@property (nonatomic, strong, readonly) APStoreKitPurchaseParams *additionalParameters;

/**
 Product identifier representing the current purchase */
@property (nonatomic, strong, readonly) NSString *productIdentifier;

#pragma mark - APStoreKitPurchase

/**
 Initialize  with dictionary , purchasable item and target
 @param aDict Dictionary with purchase info
 @param aModel Either a VOD item or Channel
 @param identifier Target product identifier
 @return initialized storekit purchase
 */
- (id)initWithDictionary:(NSDictionary*)aDict
			 targetModel:(APPurchasableItem*)aModel
		targetIdentifier:(NSString*)identifier;

/**
 Initialize with dictionary and storekit purchase parameters
 @param aDict dictionary with purchase info
 @param storeKitPurchaseParams from the model / subscription
 @return initialized storekit purchase
 */
- (id)initWithDictionary:(NSDictionary*)aDict
  storeKitPurchaseParams:(APStoreKitPurchaseParams*)storeKitPurchaseParams;

/**
 Set a transaction with Additional parameters
 @param aTransaction - sets at the current transaction
 @param params used as aditional parameters with Applicaster server
 */
- (void)setTransaction:(SKPaymentTransaction*)aTransaction andAdditionalParams:(APStoreKitPurchaseParams*)params;

/**
 Creates and sends a transaction
 @param aTransaction - sets at the current transaction
 */
- (void)createWithTransaction:(SKPaymentTransaction*)aTransaction;

/**
 Creates and sends a transaction with Additional parameters
 @param aTransaction - sets at the current transaction
 @param params - Additional parameters
 */
- (void)createWithTransaction:(SKPaymentTransaction*)aTransaction andAdditionalParams:(APStoreKitPurchaseParams*)params;

/**
 Send the current transaction request to Apple and then to Applicaster
 */
- (void)sendTransactionRequest;

@end

#pragma mark - APStoreKitPurchaseDelegate

/**
 Storekit purchase delegate is used so that the storekit purchase can update the delegate if a transaction succeeded or failed.
 */
@protocol APStoreKitPurcaseDelegate

- (void)modelDidFinishCreate:(APStoreKitPurchase *)transaction;
- (void)modelDidFailCreate:(APStoreKitPurchase *)transaction;

@end
