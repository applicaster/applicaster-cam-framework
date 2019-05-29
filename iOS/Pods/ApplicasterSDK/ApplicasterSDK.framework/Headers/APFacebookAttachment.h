//
//  APFacebookAttachment.h
//  ApplicasterSDK
//
//  Created by Hagit Shemer on 12/23/13.
//  Copyright (c) 2013 Applicaster. All rights reserved.
//

#import <Foundation/Foundation.h>

/**
 Attachment types
 **/
typedef enum {
    APFacebookAttachmentTypeNone = 0,
    APFacebookAttachmentTypeLink,
    APFacebookAttachmentTypePhoto,
    APFacebookAttachmentTypeVideo
} APFacebookAttachmentType;


@interface APFacebookAttachment : NSObject

/**
 Attachment type
 **/
@property (nonatomic, assign, readonly) APFacebookAttachmentType type;

@end

@interface APFacebookImageAttachment : APFacebookAttachment

/**
 Image URL string or nil if there is no image
 **/
@property (nonatomic, strong, readonly) NSString *imageURLString;

/**
 Image size.
 **/
@property (nonatomic, assign, readonly) CGSize imageSize;

/**
 The atatachment dictionary received in Facebook's post object, it is needed because the basic picture that Facebook gives is very small.
 */
@property (nonatomic, strong, readonly) NSDictionary *attachmentsDictionary;

+ (instancetype)imageAttachmentWithAttachmentsDictionary:(NSDictionary *)attachmentsDictionary;

/**
 Call this method in order to get the original (largest) image URL string. This is a separate call to Facebook.
 */
- (void)originalImageURLStringWithCompletion:(void (^)(NSString *imageURL))completion;

@end

@interface APFacebookLinkAttachment : APFacebookImageAttachment

/**
 Link URL string or nil if there is no link
 **/
@property (nonatomic, strong, readonly) NSString *linkURLString;

+ (instancetype)linkAttachmentWithlinkURLString:(NSString *)linkURLString
                       andAttachmentsDictionary:(NSDictionary *)attachmentsDictionary;

@end

@interface APFacebookVideoAttachment : APFacebookImageAttachment

/**
 Video URL string or nil if there is no video
 **/
@property (nonatomic, strong, readonly) NSString *videoURLString;

+ (instancetype)videoAttachmentWithVideoURLString:(NSString *)videoURLString
                         andAttachmentsDictionary:(NSDictionary *)attachmentsDictionary;

@end
