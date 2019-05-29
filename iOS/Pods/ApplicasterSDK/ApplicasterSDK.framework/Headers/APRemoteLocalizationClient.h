//
//  APRemoteLocalizationClient.h
//  ApplicasterSDK
//
//  Created by Liviu Romascanu on 4/1/15.
//  Copyright (c) 2015 Applicaster. All rights reserved.
//

#import <Foundation/Foundation.h>

extern NSString * const APRemoteLocalizationDidUpdateNotification;

@interface APRemoteLocalizationClient : NSObject
/**
 Localization dictionary built in the following way:
 {
 "en" =>
    {
        key = value;
    }
 }
 */
@property (nonatomic, strong) NSMutableDictionary *localizationDictionary;

/**
 Current language - 2 letters code
 */
@property (nonatomic, strong, readonly) NSString *currentLanguage;

/**
 Legacy mode - if this is turned on - the app will fall back to APLocalization mechanism in case there is no remotely configured value.
 */
@property (nonatomic, assign) BOOL legacyMode;

/**
 Applicaster Accounts system ID
 */
@property (nonatomic, copy) NSString *accountsID;

/**
 Singleton method
 @return The shared remote localization client.
 */
+ (instancetype)sharedInstance;

/**
 Load language by code from Zapp
 @param languageCode - two letters language code
 @param forceReload - Force reloading the localization
 @param success - success completion block
 @param failure - failure completion block with error
 */
- (void)loadLanguage:(NSString *)languageCode
         forceReload:(BOOL)forceReload
          withSucces:(void (^)(void))success
         withFailure:(void (^)(NSError *error))failure;

/**
 Set the current language and load it if needed
 @param currentLanguage - Two letters language code
 @param success - Successfully set the current language
 @param failure - Failed to set the current language - probably due to network error
 */
- (void)setCurrentLanguage:(NSString *)currentLanguage
                withSucces:(void (^)(void))success
               withFailure:(void (^)(NSError *error))failure;

/**
 Get localization key for value if available
 @param key - localization key
 @param languageCode - two letters language code
 @return localized value if available
 */
- (NSString *)getLocalizationValueForKey:(NSString *)key
                             forLanguage:(NSString *)languageCode;

/**
 Get localization key for value
 @param key - localization key
 @param comment - return the original string if no localization was found
 @return localized value if available
 */
- (NSString *)getLocalizationValueForKey:(NSString *)key
                             withComment:(NSString *)comment;

/**
 return if current language is a Rigth to Left language (according to the currently set APLocalization language)
 */
- (BOOL)isRTLLanguage;

@end

@interface NSString (APRemoteLocalization)

/**
 Calls <code>APLocalizedString(localizationKey,self)</code>
 Example of use: <code>[@"The sentence to be localized" withKey:@"APExampleSentence"]</code>
 @param localizationKey The key to be checked in the localization table.
 @return The localized string that matches the localization key.
 */
- (NSString*)withKey:(NSString*)localizationKey;

@end

