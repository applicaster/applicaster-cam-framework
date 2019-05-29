//
//  APBanner.h
//  applicaster
//
//  Created by Guy Kogus on 24/01/12.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//

#import <Foundation/Foundation.h>

/**
 An Applicaster banner defined in the CMS.
 */
@interface APBanner : NSObject

/** The banner's unique ID. */
@property (nonatomic, strong, readonly) NSString *bannerID;
/** The URL for the banner's image sized 1024x66. */
@property (nonatomic, strong, readonly) NSURL *largePortraitImageURL;
/** The URL for the banner's image sized 768x66. */
@property (nonatomic, strong, readonly) NSURL *smallPortraitImageURL;
/** The URL for the banner's image sized 480x32. */
@property (nonatomic, strong, readonly) NSURL *largeLandscapeImageURL;
/** The URL for the banner's image sized 320x50. */
@property (nonatomic, strong, readonly) NSURL *smallLandscapeImageURL;
/** This is an identifier to indicate how the link URL should be opened - portrait, landscape or external */
@property (nonatomic, strong, readonly) NSString *webViewType;
/** The ID of the category to open when the banner is pressed. */
@property (nonatomic, strong, readonly) NSString *categoryID;
/** The URL to open in a web view when the banner is pressed. */
@property (nonatomic, strong, readonly) NSURL *linkURL;
/** Indicates whether or not the banner shows during video playback. */
@property (nonatomic, readonly) BOOL showOnVideo;


/**
 Initialise a new banner object.
 @param object The dictionary with the banner's parameters.
 @return A banner object.
 */
- (id)initWithJSONObject:(id)object;

/**
 Helper method for returning an autoreleased banner.
 @param object The dictionary with the banner's parameters.
 @return A banner object.
 */
+ (id)bannerForJSONObject:(id)object;

@end
