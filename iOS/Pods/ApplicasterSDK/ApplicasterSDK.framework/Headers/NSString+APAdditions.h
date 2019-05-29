//
//  NSString+APAdditions.h
//  ApplicasterSDK
//
//  Created by Guy Kogus on 8/01/12.
//  Copyright (c) 2012 Applicaster. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <UIKit/UIKit.h>
/**
 Additions taken from Three20.
 */
@interface NSString (APAdditions)

/**
 * Determines if the string contains only whitespace and newlines.
 */
- (BOOL)isWhitespaceAndNewlines;

/**
 * Determines if the string is empty or contains only whitespace.
 *
 * @deprecated - Use isNotEmptyOrWhiteSpaces instead.
 */
- (BOOL)isEmptyOrWhitespace __attribute__((deprecated));

/**
 * Determines if the string contains characters other than whitespaces.
 */
- (BOOL)isNotEmptyOrWhiteSpaces;

/**
 * Parses a URL query string into a dictionary.
 * @param encoding The required string encoding.
 * @return The query dictionary.
 */
- (NSDictionary*)queryDictionaryUsingEncoding:(NSStringEncoding)encoding;

/**
 * Parses a string, adds query parameters to its query, and re-encodes it as a new string.
 * @param query The query dictionary.
 * @return The new string with the queries appended.
 */
- (NSString*)stringByAddingQueryDictionary:(NSDictionary*)query;

/**
 * Appends the Right to Left Mark character to the begining of the text. It makes the text be RTL even if the original text started with English letters.
 * @return The new string with the Right to Left Mark character appended to the begining of the text.
 */
- (NSString*)rtlString;

/**
 * Calculate the md5 hash of this string using CC_MD5.
 *
 * @return md5 hash of this string
 */
- (NSString*)md5Hash;

/**
 Return a reversed version of the string.
 @return The string in reverse.
 */
- (NSString *)reversed;

/**
 Returns a string that is used for analytics.
 @return string after all ' ' were changed to '-', no accents and special characters. 
 */
- (NSString *)analyticsString;

/**
 Turns a JSON URL - Like in notifications to a JSON valid string.
 That string can be then turned into a dictionary with any json parser.
 The need for this was raised due to the fact the previous parsing did not work when jsons had more then one level of nesting
 @param queryString string from the URL
 @return valid JSON string
 */
+ (NSString *)queryJsonStringWithJsonedUrl:(NSString *)queryString;


/**
 Capitlize first letters in each sentence.
 @return capitlized sentence
 */
- (NSString *)stringByCapitalizingSentence;

/**
 Returns the height of the text when contained in the given label.
 @param label name of the label item for which the height is being computed
 @return the computed height (float) of the label
 */
- (CGFloat)heightForTextInLabel:(UILabel *)label;

/**
 Returns the height of the text when contained in the given label.
 @param label name of the label item for which the height is being computed
 @param maxHeight the max height you allow the label to have.
 @return the computed height (float) of the label
 */
- (CGFloat)heightForTextInLabel:(UILabel *)label
                      maxHeight:(CGFloat)maxHeight;

/**
 Returns the height of the text when contained in the given label but limits the number of characters
 @param label name of the label item for which the height is being computed
 @param maximumCharacters maximum number of characters in the label's text that is allowed
 @return the computed height (float) of the label
 */
- (CGFloat)heightForTextInLabel:(UILabel *)label maximumCharacters:(NSUInteger)maximumCharacters;

/**
 Returns the width of the text when contained in the given label.
 @param label name of the label item for which the width is being computed.
 @return the computed width (float) of the label
 */
- (CGFloat)widthForTextInLabel:(UILabel *)label;

/**
 Returns the width of the text when contained in the given label.
 @param label name of the label item for which the width is being computed.
 @param maxWidth the max width you allow the label to have.
 @return the computed width (float) of the label
 */
- (CGFloat)widthForTextInLabel:(UILabel *)label
                      maxWidth:(CGFloat)maxWidth;

/**
 This method uses a regular expression pattern to find a value within the receiver.
 the value is found using case Insensitive Comparison
 @param index The index of the capture range in the given pattern.
 @param pattern The regular expression pattern to search in the string.
 @return The value of the captured range.
 */
- (NSString *)valueAtRangeIndex:(NSUInteger)index ofRegExPattern:(NSString *)pattern;
@end
