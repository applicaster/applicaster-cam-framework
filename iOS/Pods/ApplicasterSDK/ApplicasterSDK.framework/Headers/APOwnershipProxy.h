//
//  APPriceProxy.h
//  applicaster
//
//  Created by Tom Susel on 12/15/10.
//  Copyright 2010 __MyCompanyName__. All rights reserved.
//

#import <Foundation/Foundation.h>

@class APPurchasableItem, APApplicasterController;

typedef enum{
	APProductOwnershipFree = 0,
	APProductOwnershipOwned = 1,
	APProductOwnershipNotOwned = 2,
}APProductOwnership;


@interface APOwnershipProxy : NSObject {
	
	NSMutableDictionary *_ownedByKey;
	
	APApplicasterController *__unsafe_unretained _controller;
}

@property (nonatomic, unsafe_unretained) id controller;

/*
 Singleton method, returns the single instance of APPriceProxy
 */
+ (APOwnershipProxy*)sharedInstance;

+ (void)setController:(APApplicasterController *)aController;

- (BOOL)isItemOwned:(APPurchasableItem*)purchasableItem;

- (BOOL)isItemFree:(APPurchasableItem*)purchasableItem;

- (void)setOwnership:(APProductOwnership)ownership forKey:(NSString*)key;

@end
