//
//  APSocialShareSheetSharingProtocol.h
//  applicaster
//
//  Created by Liviu Romascanu on 1/30/14.
//  Copyright (c) 2014 Applicaster Ltd. All rights reserved.
//

#import <Foundation/Foundation.h>

/**
 This protocol is used to add sharing options to the share sheet
 */
@protocol APSocialShareSheetSharingProtocol <NSObject>

@required

/**
 UIImage for the cell - Icon of social network / share method
 */
- (UIImage *)imageForCell;

/**
 Share name - name of the social network / share method
 */
- (NSString *)shareName;

@optional

/**
 Share with text , image and link
 @param text used for sharing
 @param image to share - not currently implemented in most sharing options. Can be used in the future to upload an image
 @param linkURL - the link used for the sharing
 */
- (void)shareWithText:(NSString *)text andImageURL:(NSURL *)imageURL andLink:(NSURL *)linkURL;

/**
 Share with text , image and link
 @param text used for sharing
 @param subject for sharing
 @param image to share - not currently implemented in most sharing options. Can be used in the future to upload an image
 @param linkURL - the link used for the sharing
 */
- (void)shareWithText:(NSString *)text andSubject:(NSString *)subject andImageURL:(NSURL *)imageURL andLink:(NSURL *)linkURL;

@end
