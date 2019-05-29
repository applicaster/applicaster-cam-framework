//
//  AppoxeeViewController.h
//  AppoxeeTest
//
//  Created by sivori on 7/12/10.
//  Copyright 2010 Appoxee. All rights reserved.
//

#import <UIKit/UIKit.h>
#import "AppoxeeDelegate.h"

@class AppoxeeMessage;

@interface AppoxeeManager : NSObject

/**
 * Values to the options dictionary passed to Appoxee at init method
 * Should Appoxee be modal (boolean , YES=modal)
 */
FOUNDATION_EXTERN NSString * const AppoxeeManagerModalParam;

/**
 * If Appoxee isn't modal - select it's view hight (int)
 */
FOUNDATION_EXTERN NSString * const AppoxeeManagerViewHeightParam;

/**
 * 'New mail' sound file name (NSString*)
 */
FOUNDATION_EXTERN NSString * const AppoxeeManagerNewMailSoundFileName;

/**
 * Modal animation type key
 */
FOUNDATION_EXTERN NSString * const AppoxeeManagerViewAnimationTypeParam;
/**
 * Modal animation type possiable values
 */
FOUNDATION_EXTERN NSString * const AppoxeeManagerViewAnimationTypeParam_PageCurl;
FOUNDATION_EXTERN NSString * const AppoxeeManagerViewAnimationTypeParam_VerticalMove;

/**
 * Accessing the Appoxee shared manager
 * @return 'AppoxeeManager' instance.
 */
+ (id) sharedManager;

/**
 Allow Appoxee to automatically clear notifications from the notification center.
 @brief Method will allow Appoxee to automatically clear notifications from the notification center.
 @attention Default state is NO - the developer is responsible for clearing notifications from the notification center.
 @param automatically
 Boolean value which indicate clearing automatically when YES is passed, and manually clearing notifications by the developer the NO is passed.
 */
+ (void)automaticallyClearNotifications:(BOOL)automatically;

/**
 Get the state of clearing notifications automatically.
 @brief Method will get the state of clearing notifications automatically.
 @attention Default state is NO - the developer is responsible for clearing notifications from the notification center.
 @return a boolean value indicating the state, NO for manual, YES for automatic.
 */
+ (BOOL)isNotificationsClearedAutomatically;

/**
 * Connection methods for the AppoxeeManager
 */
- (void) initManagerWithDelegate:(id<AppoxeeDelegate>)d andOptions:(NSDictionary*)options;
/**
 * Activate the Appoxee manager after the user's app has launched
 *
 * @see AppoxeeManagerModalParam
 * @see AppoxeeManagerViewHeightParam
 * @see AppoxeeManagerNewMailSoundFileName
 * @see AppoxeeManagerViewAnimationTypeParam
 * @see AppoxeeManagerViewAnimationTypeParam_PageCurl
 * @see AppoxeeManagerViewAnimationTypeParam_VerticalMove
 */
- (BOOL) managerParseLaunchOptions:(NSDictionary *)launchOptions;
/**
 * Register for remote notifications
 * Should call from '- (void)application:(UIApplication *)application didRegisterForRemoteNotificationsWithDeviceToken:(NSData *)token'
 *
 * @param (NSData *)token that received from Apple delegate.
 */
- (void) didRegisterForRemoteNotificationsWithDeviceToken:(NSData *)token;
/**
 * Alert Appoxee about recieving remote notifications
 * Should call from '- (void)application:(UIApplication *)application didReceiveRemoteNotification:(NSDictionary *)userInfo'
 *
 * @param (NSDictionary *)userInfo that received from Apple delegate.
 */
- (BOOL) didReceiveRemoteNotification:(NSDictionary *)userInfo;
/**
 * Alert Appoxee about recieving local notifications
 * Should call from '- (void)application:(UIApplication *)application didReceiveLocalNotification:(UILocalNotification *)notification'
 *
 * @param (NSDictionary *)userInfo that received from Apple delegate.
 */

-(void)didReceiveLocalNotification:(UILocalNotification *)notification;

- (BOOL)handleActionWithIdentifier:(NSString *)identifier forRemoteNotification:(NSDictionary *)userInfo completionHandler:(void (^)())completionHandler;


/**
 * Modal Version
 * For modal version, asks the Appoxee to show inbox on screen
 */
- (void) show;
/**
 * Show 'More Apps' view controller on screen
 *
 * @return YES on success, No if this feature is disabled on the server.
 */
- (BOOL) showMoreAppsViewController;
/**
 * Show 'Feedback' view controller on screen
 *
 * @return YES on success, No if this feature is disabled on the server.
 */
- (BOOL) showFeedbackViewController;
/**
 * You can choose whether to show the MoreApps button on Appoxee's inbox or not.
 *
 * @param show = YES to enable the button on the Inbox, show = NO to diabled it.
 * Default value = YES
 */
- (void) showMoreAppsOnInbox:(BOOL)show; // default value is YES
/**
 * You can choose whether to show the Feedback button on Appoxee's inbox or not.
 *
 * @param show = YES to enable the button on the Inbox, show = NO to diabled it.
 * Default value = YES
 */
- (void) showFeedbackOnInbox:(BOOL)show; // default value is YES

/**
 * Non-Modal Version
 * you can change the view controller's center point and specify it's height using 'AppoxeeManagerViewHeightParam'.
 * Don't change the geometry of the getAppoxeeViewController.view element (ie : frame,bounds,transform etc)
 * On iPad's app TEHRE IS NO SUPPORT FOR NON-MODAL INBOX CONTROLLERS
 *  If you want to create a custom inbox for your iPad app, please use the "-(NSArray *)getInboxMessages".
 *
 * @return UIViewController representing Appoxee's mailbox
 */
- (UIViewController *) getAppoxeeViewController;

- (UIViewController *)getAppoxeeMoreAppsViewController;

- (UIViewController *)getAppoxeeFeedbackViewController;


/**
 * Ask the Appoxee to recalculate the unread messages badge. This will initiate a call to 'AppoxeeNeedsToUpdateBadge' in the Appoxee delegate.
 */
- (void) recalculateUnreadMessagesBadge;

/**
 * Use to resize the ViewController when hiding/showing the status bar
 */
-(void)statusBar:(BOOL)status :(UIViewController*)rootVC;

/**
 Set a Custom Inbox Flag
 @brief Method will set application as using Custom Inbox
 @param isCustom
 a BOOL value indication if we are using a Custom Inbox
 @discussion Use This method when you are adopting or creating a Custom Inbox. Setting the BOOL to YES will only enable the display of a Custom Inbox, thus making any call to [AppoxeeManager sharedManager] show]; to NOT show the Default Inbox.
 */
-(void)setUsingCustomInbox:(BOOL)isCustom;

/**
 Get the Custom Inbox Flag
 @return a Boolean indicating if Custom Inbox is enabled.
 */
-(BOOL)getUsingCustomInboxFlag;

/**
 * You can choose whether to show the Custom inbox or not.
 *
 * @param show = YES to enable the button on the Inbox, show = NO to diabled it.
 * Default value = YES
 */
- (void) showCustomInbox:(BOOL)show; // default value is YES




//////////////////////////////////////////////////////////////////////////////////
//////////////////////////////    Badge Methods     //////////////////////////////
//////////////////////////////////////////////////////////////////////////////////
/**
 * Utility methods which paint a nice badge on a selected view.
 */
- (void) addBadgeToView:(UIView *)badgeView badgeText:(NSString *)badgeText badgeLocation:(CGPoint)badgeLocation;
- (void) addBadgeToView:(UIView *)badgeView badgeText:(NSString *)badgeText badgeLocation:(CGPoint)badgeLocation shouldFlashBadge:(BOOL)shouldFlashBadge;
- (void) addBadgeToView:(UIView *)badgeView badgeText:(NSString *)badgeText badgeLocation:(CGPoint)badgeLocation shouldFlashBadge:(BOOL)shouldFlashBadge withFontSize:(float)fontSize;



//////////////////////////////////////////////////////////////////////////////////
//////////////////////////////    Custom Inbox      //////////////////////////////
//////////////////////////////////////////////////////////////////////////////////
/**
 * 
 * Inbox Messages Methods - using for creating custom inbox UIViewController
 *
 * @return NSArray of AppoxeeMessage Objects
 * @see AppoxeeMessage.h
 */
- (NSArray *) getInboxMessages; // return NSArray of AppoxeeMessage Objects (check AppoxeeMessage.h)
/**
 * Open Appoxee Message on Modal view
 *
 * @param AppoxeeMessage Object
 * @see AppoxeeMessage.h
 */
- (void) openAppoxeeMessage:(AppoxeeMessage *)appoxeeMessage;
/**
 * Delete Appoxee Message
 *
 * @param AppoxeeMessage Object
 * @see AppoxeeMessage.h
 */
- (void) deleteAppoxeeMessage:(AppoxeeMessage *)appoxeeMessage;


//////////////////////////////////////////////////////////////////////////////////
//////////////////////////////      Tags API        //////////////////////////////
//////////////////////////////////////////////////////////////////////////////////
/**
 * Add tags to device
 *
 * @param tagsToAdd - NSArray of NSStrings of the selected tags
 * @param tagsToRemove - NSArray of NSStrings of the selected tags
 *
 * @return YES on success, NO if failed
 */
-(BOOL) addTagsToDevice:(NSArray *)tagsToAdd andRemove:(NSArray *)tagsToRemove;
/**
 * Add tags to device
 * And remove tags from device
 * @param tags - NSArray of NSStrings of the selected tags
 *
 * @return YES on success, NO if failed
 */
-(BOOL) addTagsToDevice:(NSArray *)tags;
/**
 * And remove tags from device
 * @param tags - NSArray of NSStrings of the selected tags
 *
 * @return YES on success, NO if failed
 */
-(BOOL) removeTagsFromDevice:(NSArray*)tags;
/**
 * Get device's tag list from the server
 *
 * @return NSArray of NSStrings
 */
-(NSArray *) getDeviceTags;
/**
 * Get App's tag list from the server
 *
 * @return NSArray of NSStrings
 */
-(NSArray *) getTagList;
/**
 * Clear tags local cache
 */
-(void) clearTagsCache;


//////////////////////////////////////////////////////////////////////////////////
//////////////////////////////      Aliases API     //////////////////////////////
//////////////////////////////////////////////////////////////////////////////////
/**
 * Set device alias
 *
 * @return YES on success, NO if failed
 */
-(BOOL) setDeviceAlias:(NSString*)alias; 
/**
 * Remove device alias
 *
 * @return YES on success, NO if failed
 */
-(BOOL) removeDeviceAlias;  
/**
 * Get device alias
 *
 * @return YES on success, NO if failed
 */
-(NSString *) getDeviceAlias;
/**
 * Clear alias local cache
 */
-(void) clearAliasCache;



//////////////////////////////////////////////////////////////////////////////////
//////////////////////////////    Key-Value API     //////////////////////////////
//////////////////////////////////////////////////////////////////////////////////
/**
 * Assign key value to device
 *
 * @param NSDictionary - each record has key & value
 *
 * @return YES on success, NO if failed
 *
- (BOOL) assignKeyValueToDevice:(NSDictionary*)dict; 
**
 * Remove keys from device
 *
 * @param NSArray of NSString (keys)
 *
 * @return YES on success, NO if failed
 *
- (BOOL) removeKeysOnDevice:(NSArray *)keys; 
**
 * Get device value according to key
 *
 * @param NSString (key)
 *
 * @return YES on success, NO if failed
 *
- (NSString *) getDeviceKeyValue:(NSString *)key;
**
 * Get key list
 *
 * @return NSArray of NSString (keys)
 *
- (NSArray *) getKeyList;  
*/

//////////////////////////////////////////////////////////////////////////////////
//////////////////////////////    Device Info       //////////////////////////////
//////////////////////////////////////////////////////////////////////////////////
/**
 * Get Device Os Name
 */
- (NSString *) getDeviceOsName;
/**
 * Get Device Os Number
 */
- (NSString *) getDeviceOsNumber;
/**
 * Get Hardware Type
 */
- (NSString *) getHardwareType;
/**
 * Get Device Country
 */
- (NSString *) getDeviceCountry;
/**
 * Get Device Activations
 */
- (int) getDeviceActivations;
/**
 * Get Device inApp Payment
 * 
 * @return nil if not set yet.
 */
- (NSDecimalNumber *) getInAppPayment;
/**
 * Get Num Products Purchased
 */
- (int) getNumProductsPurchased;
/**
 * Increase inApp payment and number of product purchased
 *
 * @param payment (NSDecimalNumber *) 
 * @param numPurchased (int)
 */
- (BOOL) increaseInAppPayment:(NSDecimalNumber*)payment andNumPurchased:(NSDecimalNumber*)numPurchased;
/**
 * Increase number of product purchased
 *
 * @param numPurchased (int)
 */
- (BOOL) increaseNumProductPurchased:(NSDecimalNumber*)payment;

-(NSString*)getApplicationID;

-(int)getInboxFlag;

-(int)getCustomInboxFlag;

-(NSString*)getDeviceUniqueID;

-(int)getFeedbackFlag;

-(int)getMoreAppsFlag;


//////////////////////////////////////////////////////////////////////////////////
//////////////////////////////    Push Managment    //////////////////////////////
//////////////////////////////////////////////////////////////////////////////////

/**
 * Determines whether push is enabled.
 * Returns
 * True if push is enabled, false otherwise
 **/
- (BOOL) isPushEnabled;

/**
 * Determines whether sound is enabled.
 * Returns
 * A boolean indicated whether sound is enabled.
 **/
- (BOOL) isSoundEnabled;

/**
 * Determines whether badge is enabled.
 * Returns
 * A boolean indicating whether badge is enabled
 **/
- (BOOL) isBadgeEnabled;

/**
 * Determines whether Inbox is enabled.
 * Returns
 * A boolean indicating whether Inbox is enabled
 **/
- (BOOL) isInboxEnabled;

/**
 * Determines whether CoPPA was Shown.
 * Returns
 * A boolean indicating whether CoPPA was Shown
 **/
- (BOOL) isCoppaShown;

/**
 * set Push Message Enable YES/NO
 */
- (void) setPushEnabled:(BOOL)enabled;  // default is YES

/**
 * set Push Sound Enable YES/NO
 */
- (void) setSoundEnabled:(BOOL)enabled; // default is YES

/**
 * set Push Badge Enable YES/NO
 */
- (void) setBadgeEnabled:(BOOL)enabled; // default is YES

/**
 * set Inbox Enable YES/NO
 */
- (void) setInboxEnabled:(BOOL)enabled; // default is YES

/**
 * set Dates info to server
 */
- (BOOL) setDateFields:(NSMutableDictionary*)datesDict;

/**
 * set Numeric Fields to server
 */
- (BOOL) setNumericFields:(NSMutableDictionary*)numericValuesDict;
/**
 * inc Numeric Fields to server
 */
- (BOOL) incNumericFields:(NSMutableDictionary*)numericValuesDict;

/**
 * set String Fields to server
 */
- (BOOL) setStringFields:(NSMutableDictionary*)stringValuesDict;

/**
 * get Notification status from iOS
 */
- (UIRemoteNotificationType) getNotificationStatus;

/**
 * Set Quiet Time (no push messages between hours
 */
- (void) setQuietTime:(NSString*)startTimeParam endTime:(NSString*)endTimeParam;

/**
 * Get Splash Screen image link from Server
 */
- (NSString*) getSplashScreen; //Splash Screen from Server

/**
 *Get "Powered By" image link from Server
 */
- (NSString*) getPoweredByImageLink;

/**
 *Get Quiet Time Start
 */
-(NSString*)getQuietTimeStart;

/**
 *Get Quiet Time End
 */
-(NSString*)getQuietTimeEnd;

/**
 * OptOut Badge (Future)
 */
-(void)optOutBadge:(BOOL)flag;

/**
 * OptOut Sound (Future)
 */
-(void)optOutSound:(BOOL)flag;

/*
 *SplashScreen
 */
-(void)SplashScreen;




/**
 * OptOut Inbox
 */
-(void)optOutInbox:(BOOL)flag;

/**
 * OptOut Push
 */
-(void)optOutPush:(BOOL)flag;

-(void)optOutQuietTime;


//////////////////////////////////////////////////////////////////////////////////
//////////////////////////////     Localization     //////////////////////////////
//////////////////////////////////////////////////////////////////////////////////
/*
 *Configures the local language of the SDK.
 *Example for received parameters: en/he/fr.
 *The default language incase that nothing sent or the language file is not exists is English (en).
 *To create new language file, please add txt file named "en.txt" (instead of en, use the proper localized language) to the project, and make sure there are values for all the keys. the full key list appears at the example.txt file.
*/
- (void)configureAppoxeeForLocale:(NSString*)theLocale;

////////////////////// V3 ////////////////////////////
-(NSString*)getAttribute:(NSString*)param;

/**
 * get a custom field by it's key.
 */
- (NSString *)getCustomFieldByKey:(NSString *)key;

-(NSArray*)setAttributeWithDict:(NSMutableDictionary*)param andKey:(NSString*)keyParam;

///////////////////// URL //////////////////////////
-(NSString*)getServerV3URL;
-(NSString*)getGateKeeperURL;
-(NSString*)getServerV2URL;
-(NSString*)getMoreAppsURL;
-(NSString*)getFeedbackURL;
-(NSString*)getDeviceDefURL;
-(NSString*)getDeviceAdsURL;

/////////////////////// iOS 8 Compatibility for push Registration /////////////////

- (void)disableFeedbackAndMoreApps:(BOOL)shouldDisable;

@end

