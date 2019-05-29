//
//  APEndUserProfile.h
//  applicaster
//
//  Created by Guy Kogus on 5/01/12.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//

#import "APModel.h"

@class APVoucher;

extern NSString * const APEndUserProfileUpdated;
extern NSString * const APEndUserProfileUpdateFailed;
extern NSString * const APEndUserProfileSubscriptionChecked;

/**
 The end user profile represents the device's user.
 */
@interface APEndUserProfile : APModel{
	BOOL isDuringPost;
	NSInteger currentReportedDuration;
	id decrementTarget;
	SEL decrementSelector;
	
//	TTURLRequest    *decrementRequest;
	NSMutableArray  *_vouchers;
    NSArray         *_favorites;
}

@property (nonatomic, strong, readonly) NSString *videoFolderSize;
@property (nonatomic, strong, readonly) NSArray *vouchers;

/*	Decrements and calls the selector upon finish
 *	The selector must be of the form: "decrementDidFinishWithDuration:(NSNumber*)duration
 *	The selector will not be called if decrement failed.
 * @deprecated
 */
- (void)decrement:(NSInteger)durtion withCallbacTarget:(id)aTarget andCallbackSelector:(SEL)aSelector;

/*	Adds a voucher to the array.
 *	Does nothing if a voucher with the same ID exists.
 */
- (void) addVoucher:(APVoucher*)aVoucherToAdd;

/**
 Checks each voucher for a valid application voucher and returns the latest date. If the user has a permanent voucher, which can normally only be done through the CMS, the returned date is the distant future (01/01/4001).
 @return The latest subscription expiration date, or nil if no valid subscription voucher can be found.
 */
- (NSDate *)subscriptionExpirationDate;

/**
 @return The voucher with the latest expiration date of domain type APVoucherDomainTypeApp.
 */
- (APVoucher *)latestVoucherDomainTypeApp;

/**
 Returns a URL for the account management web interface
 */
- (NSString*)accountManagementUrlPath;

/**
 Returns a URL for the account management web interface
 */
- (NSString*)redeemPage;


/**
 Adds the array of vod items to the favorites list.
 @param vodItems Array of strings representing vod item IDs
 */
- (void)addVodItemsToFavorites:(NSArray*)vodItems;

/**
 Removes the array of vod items to the favorites list.
 @param vodItems Array of strings representing vod item IDs
 */
- (void)removeVodItemsFromFavorites:(NSArray*)vodItems;

/**
 The current list of vodItems.
 */
- (NSArray*)favoriteVodItems;

@end
