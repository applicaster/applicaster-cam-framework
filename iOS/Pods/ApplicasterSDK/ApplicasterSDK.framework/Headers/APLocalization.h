//
//  APLocalization.h
//  ApplicasterSDK
//
//  Created by Tom Susel on 6/17/11.
//  Copyright 2011 Applicaster. All rights reserved.
//

#import <Foundation/Foundation.h>

/**
 A singleton object that manages the framework localization.
 */
@interface APLocalization : NSObject {
}

/**
 Finds the localized version of the string represented by the key.
 @param key The key used to identify the string.
 @param comment A comment describing the string. If no localized string can be found, this is used as the return value.
 @returns The localized string or <code>comment</code> if string was not found in the translation bundle.
 */
NSString* APLocalizedString(NSString *key, NSString *comment);

/**
 @param key - Localization key
 @param comment - Fallback text
 @return Get Localized value with key. If no localized value is found - return the comment value.
 */
- (NSString *)getLocalizedStringWithKey:(NSString *)key
                            withComment:(NSString *)comment;

/**
 Sets the app bundle to be first checked for localization strings. If none are found, will revert to the Applicaster localization bundle.
 @param localizationBundle The app's localization bundle.
 */
- (void)setAppBaseLocalizationBundle:(NSBundle *)localizationBundle;

/**
 Sets the app bundle to be first checked for localization strings. If none are found, will try to check the app basic localization bundle. If non are found, reverts to the Applicaster localization bundle.
 @param localizationBundle The app's localization bundle.
 */
- (void)setAppSpecificLocalizationBundle:(NSBundle *)localizationBundle;

/**
 The current language used for translation (nil if was never set).
 */
@property (nonatomic, copy) NSString  *currentLanguage;

/**
 The singleton instance of APLocalization.
 */
+ (APLocalization*)sharedInstance;

/**
 return if current language is a Rigth to Left language (according to the currently set APLocalization language)
 */
- (BOOL)isRTLLanguage;

/**
 Set current localization language

 @param currentLanguage - the new language to change to.
 @param shouldCache - default is NO. If you set it to YES the language will be device cached and will not be loaded from ApplicasterSettings anymore.
 */
- (void)setCurrentLanguage:(NSString *)currentLanguage
               shouldCache:(BOOL)shouldCache;

@end