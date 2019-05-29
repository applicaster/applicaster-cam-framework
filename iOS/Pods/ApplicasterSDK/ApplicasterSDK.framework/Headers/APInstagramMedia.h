//
//  APInstagramMedia.h
//  ApplicasterSDK
//
//  Created by Liviu Romascanu on 3/10/15.
//  Copyright (c) 2015 Applicaster. All rights reserved.
//

#import "APInstagramModel.h"

@class APInstagramCommentsCollection, APInstagramLikesCollection, APInstagramImage, APInstagramVideo, APInstagramCaption, APInstagramLocation, APInstagramUser;
typedef NS_ENUM(NSInteger, APInstagramMediaType) {
    APInstagramMediaTypeImage,
    APInstagramMediaTypeVideo,
    APInstagramMediaTypeUnknown
};


@interface APInstagramMedia : APInstagramModel

/**
 Unique ID
 */
@property (nonatomic, weak, readonly) NSString *uniqueID;

/**
 Array of # Tags in the caption for this media item.
 Array of strings
 */
@property (nonatomic, weak, readonly) NSArray *tags;

/**
 Filter name
 */
@property (nonatomic, weak, readonly) NSString *filter;

/**
 Link for the item on Instagram
 */
@property (nonatomic, weak, readonly) NSString *linkURLString;

/**
 Media Type
 @return Either Image , Video or Unknown (in case of future media types)
 */
- (APInstagramMediaType)mediaType;

/**
 @return APInstagramLocation - Containing place name , ID , latitude and longitude
 */
- (APInstagramLocation *)location;

/**
 Comments collection
 */
- (APInstagramCommentsCollection *)commentsCollection;

/**
 Likes Collection
 */
- (APInstagramLikesCollection *)likesCollection;

/**
 Creation date
 */
- (NSDate *)createdAt;

/**
 Dictionary of image keys and APInstagramImage values
 Common Keys:
 low_resolution
 thumbnail
 standard_resolution
 */
- (NSDictionary *)imagesDictionary;

/**
 Dictionary of video keys and APInstagramVideo values
 Common Keys:
 low_resolution
 standard_resolution
 low_bandwidth - optional - doesnt always exist
 */
- (NSDictionary *)videoDictionary;

/**
 Media shortcuts - Low resolution image
 */
- (APInstagramImage *)lowResolutionImage;
/**
 Media shortcuts - Thumbnail image
 */
- (APInstagramImage *)thumbnailImage;

/**
 Media shortcuts - Standard image
 */
- (APInstagramImage *)standardImage;

/**
 Media shortcuts - Low resolution video
 */
- (APInstagramVideo *)lowResolutionVideo;

/**
 Media shortcuts - Standard resolution video
 */
- (APInstagramVideo *)standardResolutionVideo;

/**
 Media shortcuts - Low Bandwidth video
 */
- (APInstagramVideo *)lowBandwidthVideo;

/**
 @return Array of APInstagramUserInPhoto which contains user location in photo and APInstagramUser object
 */
- (NSArray *)usersInPhoto;

/**
 @return Media Item caption
 */
- (APInstagramCaption *)caption;

/**
 @return YES if the current login user has liked the content
 */
- (BOOL)userHasLiked;

/**
 @return Instagram user that posted this media item
 */
- (APInstagramUser *)user;

@end
