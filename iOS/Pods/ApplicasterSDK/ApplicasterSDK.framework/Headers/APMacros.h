//
//  APMacros.h
//  ApplicasterSDK
//
//  Created by Liviu Romascanu on 1/22/12.
//  Copyright (c) 2012 Applicaster. All rights reserved.
//

#define IS_NOT_NULL(val) (val && ((NSNull*)val != [NSNull null]))
#define STRING_OR_NA(str) (str ? str : @"N/A")

#define AP_EXTERN_STRING_CONST(constant_name) extern NSString *constant_name;
#define AP_STRING_CONST(constant_name) NSString *constant_name = @#constant_name;

#define AP_SYNTHESIZE_DATA_ATTRIBUTE(attr_name, attr_type, attr_key) \
- (attr_type *)attr_name { \
if ([_object isKindOfClass:[NSDictionary class]] == NO) return nil;\
id ret = [(NSDictionary *)_object objectForKey:attr_key];\
if (ret && [attr_type class] == [NSString class] && [ret respondsToSelector:@selector(stringValue)])\
ret = [ret stringValue];\
if (IS_NOT_NULL(ret) == NO) return nil;\
return ret; \
}

#define AP_REGISTER_COMMAND(command_class) [self registerCommand:k##command_class commandClassRef:[command_class class]]
#define AP_INT2STR(i) [NSString stringWithFormat:@"%d", i]

#define SAFE_NOTIFICATION_NAME(notification_name) x_##notification_name

#define SAFE_REGISTER_NOTIFICATION(notification_name, selector_name, notification_object) \
NSString * SAFE_NOTIFICATION_NAME(notification_name) = *(NSString**)dlsym(RTLD_DEFAULT, #notification_name); \
if (SAFE_NOTIFICATION_NAME(notification_name) != nil) { \
[[NSNotificationCenter defaultCenter] addObserver:self \
selector:selector_name \
name:SAFE_NOTIFICATION_NAME(notification_name) \
object:notification_object]; \
}

#define SAFE_REMOVE_NOTIFICATION(notification_name, notification_object) \
NSString * SAFE_NOTIFICATION_NAME(notification_name) = *(NSString**)dlsym(RTLD_DEFAULT, #notification_name); \
if (SAFE_NOTIFICATION_NAME(notification_name) != nil) { \
[[NSNotificationCenter defaultCenter] removeObserver:self \
name:SAFE_NOTIFICATION_NAME(notification_name) \
object:notification_object]; \
}

/**
 Returns YES if iPad, NO otherwise
 */
#define IS_IPAD() ([[UIDevice currentDevice] userInterfaceIdiom] == UIUserInterfaceIdiomPad)
#define IS_568H() ([UIScreen mainScreen].bounds.size.height == 568.0 || [UIScreen mainScreen].bounds.size.width == 568.0)
#define IS_RETINA() ([UIScreen mainScreen].scale == 2.0)
#define IS_iOS_7() ([[[UIDevice currentDevice] systemVersion] floatValue] >= 7.0)

#define SCREEN_WIDTH UIInterfaceOrientationIsLandscape([UIApplication sharedApplication].statusBarOrientation) ? (IS_IPAD() ? 1024.0 : (IS_568H() ? 568.0 : 480.0)) : (IS_IPAD() ? 768.0 : 320.0)
#define SCREEN_HEIGHT UIInterfaceOrientationIsLandscape([UIApplication sharedApplication].statusBarOrientation) ? (IS_IPAD() ? 768.0 : 320.0) : (IS_IPAD() ? 1024.0 : (IS_568H() ? 568.0 : 480.0))
#define SCREEN_SIZE CGSizeMake(SCREEN_WIDTH, SCREEN_HEIGHT)