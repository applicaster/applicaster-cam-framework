//
//  APImageView.h
//  applicaster
//
//  Created by Guy Kogus on 12/01/12.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//

#import "UIView+APAnimation.h"
#import <AFNetworking/UIImageView+AFNetworking.h>
#import <FLAnimatedImage_Applicaster/FLAnimatedImageView.h>

@class APAnimation;
/**
 The <code>APImageView</code> uses the APImageLoader to asynchronously load images.
 */
@interface APImageView : FLAnimatedImageView

/** The loading indicator that displays if no placeholder image is available. */
@property (readonly, nonatomic, strong) UIActivityIndicatorView *loadingIndicator;

/** Represent the string of the url the image was initialed with. */
@property (nonatomic, strong) NSString *URLStr;

/**
 Shows animation after the image is loaded.
 @see APAnimation types of animations.
 */
@property (nonatomic, strong) APAnimation *animationAfterLoading;

/**
 Loads the image from url with placeholder while loading.
 @see UIImageView+AFNetworking.h
 @param serverResizeable Defines if the server should resize the image to the object image size.
 */
- (void)setImageWithURL:(NSURL *)url
       placeholderImage:(UIImage *)placeholderImage
        serverResizable:(BOOL)serverResizable;

/**
 Loads the image from url with placeholder while loading.
 @see UIImageView+AFNetworking.h
 @param url
 @param fallbackImage The Image that will be used when if the original image will failed load (can be used for example for cached local image in offline mode).
                      If nil the placeholder will be used. The assumption is that this image is the same type as the original (if gif - gig if png png).
 @param placeholderImage
 @param serverResizable Defines if the server should resize the image to the object image size.
 */
- (void)setImageWithURL:(NSURL *)url
          fallbackImage:(UIImage *)fallbackImage
       placeholderImage:(UIImage *)placeholderImage
        serverResizable:(BOOL)serverResizable;

/**
 Loads the image from url with placeholder while loading.
 @see UIImageView+AFNetworking.h
 @param serverResizeable Defines if the server should resize the image to the object image size.
 @param maskImage Mask Image that will be used to crop the image
 @note Image and Mask Image should be the same size. Mask image should have black and white colors.
 @note White color should be used to hide part of base image
 @note Black color should be used to leave part of base image visible
 */
- (void)setImageWithURL:(NSURL *)url
              maskImage:(UIImage *)maskImage
       placeholderImage:(UIImage *)placeholderImage
        serverResizable:(BOOL)serverResizable;

/**
 Loads the image from url with placeholder while loading.
 @see UIImageView+AFNetworking.h
 @param serverResizeable Defines if the server should resize the image to the object image size.
 @param maskImage Mask Image that will be used to crop the image
 @param fallbackImage The Image that will be used when if the original image will failed load (can be used for example for cached local image in offline mode).
        If nil the placeholder will be used. The assumption is that this image is the same type as the original (if gif - gig if png png).
 @note Image and Mask Image should be the same size. Mask image should have black and white colors.
 @note White color should be used to hide part of base image
 @note Black color should be used to leave part of base image visible
 */
- (void)setImageWithURL:(NSURL *)url
              maskImage:(UIImage *)maskImage
          fallbackImage:(UIImage *)fallbackImage
       placeholderImage:(UIImage *)placeholderImage
        serverResizable:(BOOL)serverResizable;

@end
