//
//  APCoreUtils.h
//  ApplicasterSDK
//
//  Created by Guy Kogus on 8/02/12.
//  Copyright (c) 2012 Applicaster. All rights reserved.
//

#import <Foundation/Foundation.h>

/**
 Core utility methods.
 */
@interface APCoreUtils : NSObject

/**
 Converts a number in string representation to base 32.
 @param number The base 10 number to convert.
 @return number converted to base 32.
 */
+ (NSString *)toBase32:(NSString *)number;

/**
 Converts a string representation to base 64.
 @param string to convert.
 @return base 64 string
 */
+ (NSString *)toBase64:(NSString *)string;

@end
