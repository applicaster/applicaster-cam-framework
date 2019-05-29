//
//  APApplicasterController.h
//  applicaster
//
//  Created by Neer Friedman on 1/23/10.
//  Copyright 2010 __MyCompanyName__. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "APAccount.h"
#import "APPlayable.h"
#import "APPreloadViewController.h"
#import "APApplicasterController.h"
#import "APReachabilityManager.h"
#import "APStoreKitManager.h"

extern NSString * const APErrorDomain;

@class APCategory, APCategoryView, APAccount, APChannel, APLoadingViewController,
		APStoreKitManager, APEndUserProfile, APModel, APStoreKitPurchase, APPurchasableItem, APStoreKitPurchaseParams,
        APModelCollection, APFacebookSDKClient, APNotificationManager, APBannerManager;

@protocol APApplicasterControllerDelegate, APPlayable;

@class APBroadcaster, APVodItem;

extern NSString * const APApplicasterControllerCurrentBroadcasterChanged;

/**
 Applicaster controller represents a singleton object in charge of handling Applicaster actions agains the application and holding various parts of the SDK like the player.
 
 This object should be set up and loaded from the Application's delegate.
 Short code example of basic setup and loading that should be done in the app delegate::
 <code>
 - (BOOL)application:(UIApplication *)application didFinishLaunchingWithOptions:(NSDictionary *)launchOptions
 {
    _applicaster = [APApplicasterController initSharedInstanceWithAccountID:<Account id - String> withSecretKey:<Acount Secret - String>]; 
    _applicaster.delegate = self;
    [APPlayerViewContrlller setDefaultLoadingViewClass:<i>A class that conforms to <APPlayerControls>. The view is loaded using the <initWithFrame:> method, so any initialization should be done there.</i>];
    _applicaster.rootViewController = <i>The applications Root view controller - used to display video on top of</i>;
    [_applicaster load];
 } </code>
 
 Notes:
 
 1 .To use a local intro movie - just add a .mp4 file to the bundle with the following naming conventions:
    iPhone - local_splash_video.mp4
    iPhone 5 - local_splash_video-568h.mp4
    iPad   - local_splash_video-iPad.mp4
 
 2. To set the splash image before the local intro movie - just put the next images to the budle with the following naming conventions:
    iPhone - local_splash
    iPhone 5 - local_splash-568h
    iPad - local_splash~ipad
 */
@interface APApplicasterController : NSObject<UIAlertViewDelegate> 

@property (nonatomic, strong) APEndUserProfile *endUserProfile;

/**
    APApplicaster Controller Delegate - This should usually be set as the application delegate
 */
@property (nonatomic, strong) id<APApplicasterControllerDelegate> delegate;

/**
 Account object
 Created after initial loading process of applicaster
 */
@property (readonly) APAccount *account;

/**
 The root view controller of the application.
 As a referece point to display videos on.
 */
@property (nonatomic, strong) UIViewController *rootViewController;

/**
 Default Applicaster Storekit manager.
 This is used to manage purchases (Either with no UI or against an application storefront).
 */
@property (nonatomic, strong, readonly) APStoreKitManager *storeKitManager;

/**
 Current broadcaster used by Applicaster.
 This should be set by the application once the acount is returned.
 */
@property (nonatomic, strong) APBroadcaster *currentBroadcaster;

/**
 Singleton class of the APSocial manager handling all social interaction inside Applicaster.
 For example - Facebook calls
 */
@property (nonatomic, readonly) APFacebookSDKClient *facebookClient;

/**
 APNotification manager singleton class - Used to handle all kind of local and remote notifications.
 For example - This class manages implementation of different push engines
 */
@property (nonatomic, strong) APNotificationManager *notificationManager;


/**
 Localization language value is given in (usually) 2 letters code string to represent a language.
 check out http://en.wikipedia.org/wiki/List_of_ISO_639-1_codes for example.
 We sometimes use longer codes to reprsented localizations - like en-UK (language 2 letters - country / region 2 letters)
 
 NOTE: Do not use this setter to change localization language anymore.
 Instead use setLocalizationLanguage:success:failure: instad
 */
@property (nonatomic, copy) NSString *localizationLanguage;

/**
 Boolean value representing if subcategory images should be saved.
 By defaul - this value is NO.
 
 This should be disabled on apps that do not use full tree navigation for HQME , enabled for full tree navigations
 */
@property (nonatomic, assign) BOOL  shouldSaveSubcategoryImages;

/**
 Enables / disables Recursive Datastore cleanup from the content category onwards.
 This will delete data of undownloaded items and empty offline categories on back from background and application startup.
 By default this value is NO.
 
 This should be disabled on apps that do not use full tree navigation for HQME , enabled for full tree navigations
 */
@property (nonatomic, assign) BOOL  shouldCleanupDatastore;

/**
Boolean value representing if category images should be saved.
By defaul - this value is NO.

 This should be disabled on apps that do not use full tree navigation for HQME , enabled for full tree navigations
*/
@property (nonatomic, assign) BOOL  shouldSaveCategoryImages;


/**
 The old banner manager.
 */
@property (nonatomic, strong) APBannerManager *bannerManager;


/**
 Allowed Interface orientation for preroll / web splash - Legacy mode.
 This is not a must property.
 In case no values are inserted - the current orienation will be chosen using the current statusbar orientation.
 */
@property (nonatomic, assign) UIInterfaceOrientationMask preloadInterfaceOrientations;

@property (nonatomic, strong) NSDictionary *applicasterSettings;

// General Setup and initialization

/**
 Main function to initialize the Applicaster shared instance - updated with bucket ID for AIS
 @param accountID The account ID from the Applicaster CMS
 @param secretKey The secret key value for the application from the Applicaster CMS
 @param bucketID - used for AIS to generate UUID Correctly
 @return Applicaster shared instance
 */
+(id)initSharedInstanceWithAccountID:(NSString *)accountID withSecretKey:(NSString *)secretKey withBucketID:(NSString *)bucketID DEPRECATED_ATTRIBUTE;

/**
 Updated function to initialize shared Instance using ApplicasterSettings Plist file
 The Plist file which is used is called "ApplicasterSettings.plist"

 It should contain the following values:
    APAccountID - Account ID - Must
    APBucketID - Bucket ID - Must
    APDefaultVideoLoadingClass - Default Video loading class name
    APAudioOnlyImageName - Audio only image name (let's still leave the option for a view seperate? or should we do a view class name?)
    APPlayerControlsClass (for custom controls)
	APSocialPlayerControlsClass (for custom controls for live videos)
    APCurrentLanguage - Current language code string
    APAppSpecificLocalizationBundle - Specific localization bundle prefix
    APBackgroundDownloadEndSound - Sound file name
    APDefaultBroadcasterName - DEPRECATED - DO NOT USE!
    APBroadcasterID - Broadcaster ID to be selected , if none exists - first broadcaster will be chosen by default
    APGoogleAnalyticsOverride - Application level override to analytics ID (like in Televisa)
    APBackFromBackgroundViewEnabled - default - On
 
 @param secretKey The secret key for loading the account.
 
 @return Applicaster shared instance
 */
+(id)initSharedInstanceWithPListSettingsWithSecretKey:(NSString *)secretKey;

/**
 Returns the Applicaster sharedInstance
 @return Applicaster Shared Instance Singleton
 */
+(APApplicasterController *)sharedInstance;

/**
 Load APApplicasterController.
 This should be ran after initial configuration
 */
- (void)load;

/**
 Called from HQMEManager when account cant be fetched due to limited connectivity until succeed.
 */
- (void)tryLoadingAccountWhileLimitedConnectivity;

/**
 Verifies if the Applicaster Shared Instance is ready (After initial load)
 @return YES if Applicaster / account is loaded , No otherwise
 */
- (BOOL)isReady;

/**
 Verifies if the Applicaster Shared Instance is still loading / started loading
 @return YES if Applicaster / account is loading , No otherwise
 */
- (BOOL)isLoading;

/**
 Sets No Video background slide
 @param fileName of a png file inside the main bundle
 */
- (void)setBackgroundDownloadEndSoundFileName:(NSString*)fileName;

/**
 *  applicastion preload activity indicator (spinner) color that is definied in the applicasterSettings plist.
 *  @return string hex color with alpha the is defined in applicasterSettings plist
 */
- (NSString *)appPreloadActivityIndicatorHexColor;

//API METHODS:

/**
 Returns channel with a set ID
 @param channelID unique identifier for channel
 @return Autoreleased, non-loaded APChannel object with a set ID
 */
- (APChannel *)channelWithID:(NSString *)channelID;

/**
 Returns channel with a set name. 
 This should not be used - instead use channel with ID / get channel list from account object
 @param channelName The channel's name.
 @return Autoreleased, non-loaded APChannel object with a set name
 */
- (APChannel *)channelWithName:(NSString *)channelName;

/**
 Returns the current user profile.
 @return APEndUserProfile
 */
- (APEndUserProfile*)endUserProfile;

/**
 Start listen to applicaster activities.
 This method will start listening to activties, is should be called ONLY when the account is loaded. 
 When the account is loaded by default applicasterController start listening to activites.
 */
- (void)startActivitiesListener;

/**
 Pause listen to applicaster activities.
 */
- (void)pauseActivitiesListener;

/**
 Resume listen to applicaster activities.
 */
- (void)resumeActivitiesListener;

/**
 Set localization language with success and failure blocks.
 Do not - if language is already available or in offline mode and exists in cache - this might be called synchronously.
 @param localizationLanguage - Two letters language code
 @param success - Success completion block
 @param failure - Failure completion block with error
 */
- (void)setLocalizationLanguage:(NSString *)localizationLanguage
                     withSucces:(void (^)(void))success
                    withFailure:(void (^)(NSError *error))failure;

/**
 Set localization language with success and failure blocks.
 Do not - if language is already available or in offline mode and exists in cache - this might be called synchronously.
 @param localizationLanguage - Two letters language code
 @param shouldCache - default is NO. If you set it to YES the language will be device cached and will not be loaded from ApplicasterSettings anymore.
 @param success - Success completion block
 @param failure - Failure completion block with error
 */
- (void)setLocalizationLanguage:(NSString *)localizationLanguage
                    shouldCache:(BOOL)shouldCache
                     withSucces:(void (^)(void))success
                    withFailure:(void (^)(NSError *error))failure;

#pragma mark - StoreKit

/**
 restore all previous purchases
 */
- (void)restoreCompletedTransactions;

#pragma mark - Favorites

/**
 Returns the favorites array of Vod Items for the current user profile
 @return NSArray of VOD Items
 */
- (NSArray *)favorites;

/**
 Returns the favorites array of models.
 @return NSArray of favorites models
 */
- (NSArray *)localFavorites;

// HQME

/**
 Invoke cleanup on local DataStore
 */
- (void)cleanUpLocalDataStore;

/**
 Returns only the VOD items that have completely downloaded. This differs to getAllLocalVodItems in that
 getAllLocalVodItems returns all the items that have been stored on the local data storage.
 @return The downloaded VOD items.
 */
- (NSArray *)getAllDownloadedVODItems;

/** 
 Return List of local items - HQME
 @return NSArray of local VOD Items
 */
- (NSArray *)getAllLocalVodItems;

/**
 Current Applicaster HQME State
 @return APHQMEState ENUM
 */
- (APHQMEState)hqmeState;

/**
 Checks if HQME manager is ready.
 @return YES if Account is loaded and HQME is enabled
 */
- (BOOL)hqmeReady;

/**
 Checks if a vod item is downloaded
 @param vodItemID Using this ID , the vod item is checked agains the local filesystem
 @return YES if item exists locally
 */
- (BOOL)isVodItemDownloaded:(NSString*)vodItemID;

/**
 Remove all local HQME Data.
 Also Cancels all active downloads
 */
- (void)removeAllHQMEData;

/**
 Reloads the app completely after removing the runtime cache.
 */
- (void)reloadApp;

/**
 Creates and returns an VOD item stored locally by ID
 @param vodItemID The unique ID for the VOD item to search in the list.
 @return The downloaded HQME VOD item, or nil if none is found.
 */
- (APVodItem*)hqmeVodItemForID:(NSString*)vodItemID;

// URL Scheme Handling
/**
 THIS METHOD IS DEPRECATED - please use the same method that passes the complete information.
 This method is used to pass the Applicaster Controller a URL that it can parse and pass on to its delegate.
 
 If the Applicaster controller is going to handle opening URL schemes automatically, it is essential that you set the current broadcaster
 using the  setCurrentBroadcaster: method.
 @param url The URL used for opening the application.
 @param source application
 @return YES if URL opened successfully. NO otherwise.
 */
- (BOOL)applicationDidOpenURL:(NSURL *)url withSourceApplication:(NSString *)sourceApplication DEPRECATED_ATTRIBUTE;

/**
 This method is used to pass the Applicaster Controller a URL that it can parse and pass on to its delegate.
 
 If the Applicaster controller is going to handle opening URL schemes automatically, it is essential that you set the current broadcaster
 using the  setCurrentBroadcaster: method.
 @param application Current application usually
 @param url The URL used for opening the application.
 @param source application
 @param annotation Dictionary object usually passed by file handling applications.
 @return YES if URL opened successfully. NO otherwise.
 */
- (BOOL)application:(UIApplication *)application
            openURL:(NSURL *)url
  sourceApplication:(NSString *)sourceApplication
         annotation:(id)annotation;

// End URL Scheme Handling

//TODO: Check removal
- (void)applicationWillResignActive:(UIApplication *)application;

@end

#pragma mark - APApplicasterController Delegate
/**
 The following protocol represents the Applicaster Controller Delegate.
 The delegate in most applications will be the application delegate as a big part of the functions refer directly to the application loading process
 */

@protocol APApplicasterControllerDelegate<NSObject>

@required
/**
 This function is called when Applicaster's account object finished loading for the respective account ID
 @param applicaster Applicaster controller that loaded the account
 @param accountID of the loaded Account
 At this stage application can (and should) for example do the following operations:
 1. Choose a specific broadcaster
 2. Load content categories 
 */
- (void)applicaster:(APApplicasterController *)applicaster loadedWithAccountID:(NSString *)accountID;

/**
 Applicaster failed to load content category
 @param applicaster Applicaster controller that loaded the account
 @param accountID of the loaded Account
 @param error The error that caused the failure. If the domain of the error is APErrorDomain, the error's <localizedDescription> should be presented.
 In this state the application should either show the error message on the application loading screen, or should re-attemt load after some time.
 */
- (void)applicaster:(APApplicasterController *)applicaster withAccountID:(NSString *)accountID didFailLoadWithError:(NSError *)error;

@optional

/**
 Sets if applicaster controller should manually start listening
 to applicaster activities by calling the method @startActivitiesListener
 @param applicaster The main Applicaster controller.
 @return BOOL if start listening to applicaster activities.
 */
- (BOOL)manuallyStartActivitiesListenerForApplicaster:(APApplicasterController *)applicaster;

/**
 Asks Application delegate if a URL should be allowed to open the application.
 @param applicaster The main Applicaster controller.
 @param aURL The URL used for launching the application.
 */
- (BOOL)applicaster:(APApplicasterController *)applicaster shouldOpenURL:(NSURL*)aURL;

/**
 *  Provides option to override play action from vodItem or channel, 
 *  by overriding its possible to customizate player, item loading and etc.
 *
 *  @param applicaster The main Applicaster controller.
 *  @param playableItem Item that was requested to be played.
 *
 *  @return NO - handle the play action as standard applicaster item. 
 *          YES - custom logic, the player will not be presented nor the item loading logic.
 */
- (BOOL)applicaster:(APApplicasterController *)applicaster overridePlayForPlayableItem:(APModel <APPlayable> *)playableItem;

/**
 *  Present subscription for application that uses subscrption
 *
 @param applicaster The main Applicaster controller.
 @param purchasableItem The item that is being purchased.
 */
- (void)applicaster:(APApplicasterController *)applicaster
showSubscriptionFor:(APPurchasableItem*)subscriptionItem;

/**
 In some cases - an application specific storefront is avilable.
 Implement this method if you would like the application to handle the storefront display of purchasable items
 @param applicaster The main Applicaster controller.
 @param purchasableItem The item that is being purchased.
 */
- (void)applicaster:(APApplicasterController *)applicaster showStoreFrontFor:(APPurchasableItem*)purchasableItem;

/**
 This function is called to update application of the changes in HQME State.
 This should be used instead of reachability tests - as this is done saftley and in a single place.
 This way - The application can handle reload , going into offline mode etc.
 @param applicaster The main Applicaster controller.
 @param hqmeState The new HQME state.
 */
- (void)applicaster:(APApplicasterController *)applicaster changedHQMEState:(APHQMEState)hqmeState;

// URL Scheme Handling

/**
 This method tells the delegate to present a VOD item either in context or modally.
 @param applicaster The shared Applicaster controller.
 @param vodItemID The ID of the VOD item to play.
 @param inContext If YES, we want to traverse through the application's navigation system to display the item. Otherwise we can display it modally or any other, which is easier since it does not involve loading the parent categories.
 */
- (void)applicaster:(APApplicasterController *)applicaster presentVODItemByID:(NSString *)vodItemID inContext:(BOOL)inContext;

/**
 This method tells the delegate to play a VOD item, and present it either in context or modally.
 
 If the delegate does not respond to this method, the Applicaster controller automatically attempts to play a VOD item. To allow this to perform correctly,
 set the current broadcaster through the setCurrentBroadcaster: method.
 @param applicaster The shared Applicaster controller.
 @param vodItemID The ID of the VOD item to present.
 @param inContext If YES, we want to traverse through the application's navigation system to display the item. Otherwise we can display it modally or any other, which is easier since it does not involve loading the parent categories.
 */
- (void)applicaster:(APApplicasterController *)applicaster playVODItemByID:(NSString *)vodItemID inContext:(BOOL)inContext;

/**
 This method tells the delegate to present a category either in context or modally.
 @param applicaster The shared Applicaster controller.
 @param categoryIDs The IDs of the categories to present. The IDs are in hierarchical order, i.e. The first ID is the first category to load, the next ID is the subcategory, and so forth.
 @param inContext If YES, we want to traverse through the application's navigation system to display the item. Otherwise we can display it modally.
 */
- (void)applicaster:(APApplicasterController *)applicaster presentCategoryByIDs:(NSArray *)categoryIDs inContext:(BOOL)inContext;

/**
 This method tells the delegate to present a url either in context or modally.
 @param applicaster The shared Applicaster controller.
 @param url The url should be presented. 
 @param inContext If YES, we want to traverse through the application's navigation system to display the item. Otherwise we can display it modally.
 */
- (void)applicaster:(APApplicasterController *)applicaster presentURL:(NSURL *)url inContext:(BOOL)inContext;

/**
 This method tells the delegate to present a url either in context or modally.
 @param applicaster The shared Applicaster controller.
 @param url The url should be presented.
 @param inContext If YES, we want to traverse through the application's navigation system to display the item. Otherwise we can display it modally.
 @param associatedParameters - additional parameters that might be required when presented modally
 */
- (void)applicaster:(APApplicasterController *)applicaster presentURL:(NSURL *)url inContext:(BOOL)inContext withAdditionalParameters:(NSMutableDictionary *)associatedParameters;

/**
 This method allows the delegate to begin playing a channel.
 
 If the delegate does not respond to this method, the Applicaster controller automatically attempts to play the live channel.  To avoid this behaviour, implement this method and leave it blank.
 @param applicaster The shared Applicaster controller.
 @param channel The channel that needs to be played. The channel will need to be loaded first.
 */
- (void)applicaster:(APApplicasterController *)applicaster playChannel:(APChannel *)channel;

/**
 Note - This method is deprecated - AND WILL NOT BE CALLED.
 If you need extra permissions - request them from the APFacebookSDKClient class individually.
 
 This method allows the delegate to add additional facebook permissions to the facebook client instance.
 
 @param applicaster The shared Applicaster controller.
 @return Array of permissions for Facebook needed by the application (Array of NSStrings).
 */
- (NSArray *)extraFacebookPermissionsWithApplicaster:(APApplicasterController *)applicaster DEPRECATED_ATTRIBUTE;

// End URL Scheme Handling


@end
