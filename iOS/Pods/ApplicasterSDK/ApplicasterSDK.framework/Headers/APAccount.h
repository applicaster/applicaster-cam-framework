//
//  APAccount.h
//  applicaster
//
//  Created by Guy Kogus on 5/01/12.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "APModel.h"
#import "APModelCollection.h"
#import "APAuthorizationProvider.h"

@class APModelCollection, APStoreKitPurchaseParams, APChannel, APAdvertiser;

/**
 Application Preload URL Type enum
 */
typedef enum{
	APPreloadURLTypeUnknown,/**< Unknown type - URL exists but not of specified type */
	APPreloadURLTypeNone,   /**< No App Preload */
	APPreloadURLTypeWeb,    /**< Web page preload */
	APPreloadURLTypeImage,  /**< Image preload */
	APPreloadURLTypeVideo,  /**< Video preload - should be either mp4 or m4v - preferably under 2 mb */
} APPreloadURLType;

/**
 Account model.
 The account represents the top level of the applicaster model tree.
 It contains the Broadcasters and the channels assigned to this account.
 
 Since the mobile SDK does not contain an app object - the Application relevant data from the managment servers are returned on this object
 */
@interface APAccount : APModel <APModelCollectionDelegate> {
	NSString *_accountID, *_secretKey;
	NSArray *_broadcasters;
    NSArray *_channels;
	APStoreKitPurchaseParams *_subscriptionVoucherParams;
}

/**
 Current account Identifier
 */
@property (readonly) NSString *accountID;

/**
 Secret key - specific per account.
 */
@property (readonly) NSString *secretKey;

/**
 Account Name
 */
@property (unsafe_unretained, readonly) NSString *name;

/**
 Array of broadcaster IDs
 */
@property (unsafe_unretained, readonly) NSArray *broadcasterIDs;

/**
 Array of channel IDs (should be checked if still returned
 */
@property (unsafe_unretained, readonly) NSArray *channelIDs;

/**
 Array of APBroadcasters belonging to the account
 */
@property (unsafe_unretained, readonly) NSArray *broadcasters;

/**
 Array of APBroadcasters belonging to the account
 */
@property (unsafe_unretained, readonly) NSArray *authorizationProviders;

/**
 Array of APChannels belonging to the account
 Returns cashed object - ready to be loaded / played if needed.
 */
@property (unsafe_unretained, readonly) NSArray *channels;

/**
 Returns YES if application is free
 */
@property (nonatomic, readonly) BOOL free;

/**
 Array of voucher templates relevant for the account
 */
@property (nonatomic, strong, readonly) NSArray *voucherTemplates;

/**
 Voucher template collection

 @discussion
 This will enable us to load voucher templates seperatly.
 Please use voucherTemplates property to access the list.
 This is only in order to be able to load them seperatly on the application loading process.
 */
@property (nonatomic, strong) APModelCollection *voucherTemplatesCollection;

/**
 *  Retrieve array of APVoucherTemplate instances that enabled in CMS
 */
@property (nonatomic, strong, readonly) NSArray *subscriptionVoucherTemplateEnabled;

/**
 Array of IDs of subscription vouchers relevant for the application
 */
@property (nonatomic, strong, readonly) NSArray *subscriptionVoucherTemplateIDs;

/**
 Store kit parameters to be used with an iOS SKPurchase
 */
@property (nonatomic, strong, readonly) APStoreKitPurchaseParams *subscriptionVoucherParams;

/**
 Returns YES if HQME is enabled for the application
 */
@property (nonatomic, readonly) BOOL hqmeEnabled;

/**
 Application preload URL
 */
@property (nonatomic, strong, readonly) NSString *preloadUrl;

/**
 Application preload URL type
 */
@property (nonatomic, readonly) APPreloadURLType preloadUrlType;

/**
 Application preload exposure time
 */
@property (nonatomic, strong, readonly) NSString *preloadUrlExposureTime;

/**
 Google analytics identifier used for locally gathered analytics
 */
@property (nonatomic, strong, readonly) NSString *systemAnalyticsID;

/**
 Flurry analytics identifier used for locally gathered analytics
 */
@property (nonatomic, strong, readonly) NSString *flurryAnalyticsID;

/**
 Application facebook account ID
 */
@property (nonatomic, strong, readonly) NSString *facebookAppID;

/**
 Application facebook app display name
 */
@property (nonatomic, strong, readonly) NSString *facebookAppDisplayName;

/**
 Boolean value - YES if push notifications is enabled for this application
 */
@property (nonatomic, readonly) BOOL pushEnabled;

/**
 Push engine used - Currently either Urban Airship or Appoxee
 */
@property (nonatomic, strong, readonly) NSString *pushEngine;

/**
 Urban Airship username
 */
@property (nonatomic, strong, readonly) NSString *pushUAUsername;

/**
 Urban Airship password
 */
@property (nonatomic, strong, readonly) NSString *pushUAPassword;

/**
 Appoxee SDK key
 */
@property (nonatomic, strong, readonly) NSString *pushAppoxeeSDKKey;

/**
 Appoxee secret key
 */
@property (nonatomic, strong, readonly) NSString *pushAppoxeeSecretKey;

/**
 Web Preload Fallback.
 In HQME Applications - A web Preload cannot be displayed in offline mode.
 Instead an image can be provided and displayed.
 The image is saved when in online mode and displayed when offline.
 */
@property (nonatomic, strong, readonly) NSString *webPreloadFallback;

/**
 Checks if Redeem code templates are avilable.
 This enables us to decide in an inteligent way if to display Redeem code interface
 */
@property (nonatomic, readonly) BOOL redeemCodeTemplatesExist;

/**
 Application's iTunes Identifier.
 This value is currently used for the App rater.
 If no iTunes ID is provided - Rater is not running
 */
@property (nonatomic, strong, readonly) NSString *appiTunesID;

/**
 The days it takes untill the rater is displayed.
 If not set in the account - the default value is 10.
 */
@property (nonatomic, strong, readonly) NSString *raterDays;

/**
 The Application loadings / back from backgrounds it takes untill the rater is displayed.
 If not set in the account - the default value is 20.
 */
@property (nonatomic, strong, readonly) NSString *raterUses;

/**
 Crash reporter id (HockeyApp)
 */
@property (nonatomic, strong, readonly) NSString *crashReporterId;

/**
 Boolean if to use or not the social bar (Open graph player)
 */
@property (nonatomic, readonly) BOOL socialBarEnabled;


/**
 The advertiser model for this application. This contains the ad providers used to create APBannerView objects.
 */
@property (nonatomic, readonly) APAdvertiser *advertiser;


/**
 Server Message URL
 used for JS calls
 */
@property (nonatomic, strong, readonly) NSString *activitiesListenerURL;

/**
 Dictionary containing Preload splash extended parameters
 */
@property (strong, readonly) NSDictionary *preloadWebParams;

/**
 Boolean value to determine if Capture video feature is enabled or not
 */
@property (nonatomic, readonly) BOOL isCaptureVideoEnabled;

/**
 Initialization function for account.
 @param accountID account unique identifier
 @param secretKey defined in the CMS
 */
- (id)initWithAccountID:(NSString *)accountID 
			  secretKey:(NSString *)secretKey;

/**
 Get the authorization provider by uniqueID.
 
 @param uniqueID
 
 @return the authorization provider instance with the given uniqueID or nil if not found.
 */
- (APAuthorizationProvider *)authorizationProvidersByUniqueID:(NSString *)uniqueID;

/**
 Get channel by UI Tag
 @param uiTag used to identify the channel
 @return APChannel (using cashed data - including next program , metadata and image links) or nil of channel does not exist
 */
- (APChannel *)channelByUITag:(NSString *)uiTag;

/**
 Get channel by uniqueID
 @param channelID used to identify the channel
 @return APChannel (using cashed data - including next program , metadata and image links) or nil of channel does not exist
 */
- (APChannel *)channelByUniqueID:(NSString *)channelID;

- (void)loadChannelsWithParameters:(NSDictionary *)parameters
						completion:(void (^)(NSArray *channels))completion
						   failure:(void (^)(NSError *error))failure;


/**
 Load the model.
 
 Force Loading from server and not localy event if HQMEState is set to offline
 */
- (void)loadAccountFromServer;

/**
 Force To load account localy in order to know if the app is hqme enable
 */
- (void)loadAccountLocaly;

/**
 Get Public page base URL path
 */
- (NSString *)publicPageURLBasePath;

@end

