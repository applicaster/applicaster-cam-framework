//
//  APButton.h
//  applicaster
//
//  Created by Tom Susel on 2/6/11.
//  Copyright 2011 __MyCompanyName__. All rights reserved.
//

#import <Foundation/Foundation.h>

extern NSString * const kAPButtonIsLoadedNotification;
 
/**
 This is a button that takes a url path to load as the background image.
 */
@interface APButton : UIButton

/** The URL path for the background image. */
@property (nonatomic, copy) NSString *urlPath;

/** The loading spinner. */
@property (nonatomic, readonly) UIActivityIndicatorView *loadingIndicator;

/**
 Asynchronously loads an image from the given URL.
 @param url The URL of the desired image.
 */
- (void)setImageWithURL:(NSURL *)url;

/**
 Asynchronously loads an image from the given URL.
 @param url The URL of the desired image.
 @param placeholderImage The placeholder image to be used while loading/on failure.
 */
- (void)setImageWithURL:(NSURL *)url
       placeholderImage:(UIImage *)placeholderImage;

/**
 Asynchronously loads an image from the given URL.
 @param url The URL of the desired image.
 @param placeholderImage The placeholder image to be used while loading/on failure.
 @param isBackground
 */
- (void)setImageWithURL:(NSURL *)url
       placeholderImage:(UIImage *)placeholderImage
      isBackgroundImage:(BOOL)isBackground;

/**
 Asynchronously loads an image from the given URL. Uses button image and places an aspect fill image
 @param url The URL of the desired image.
 @param placeholderImage The placeholder image to be used while loading/on failure.
 */
- (void)setAspectFillImageWithURL:(NSURL *)url placeholderImage:(UIImage *)placeholderImage;

/**
 Asynchronously loads an image from the given URL. Uses button image and places an aspect fill image
 the only different between this method and "setAspectFillImageWithURL" is that this image is not the background
 @param url The URL of the desired image.
 @param placeholderImage The placeholder image to be used while loading/on failure.
 @param size the image size
 @param showSpinner - boolean indicates weather loading indicator is diplayed.
 */
- (void)setImageOnButtonWithURL:(NSURL *)url placeholderImage:(UIImage *)placeholderImage showSpinner:(BOOL)isSpinner imageSize:(CGSize)size;

/**
 Asynchronously loads an image from the given URL. Uses button image and places an aspect fill image
 the only different between this method and "setAspectFillImageWithURL" is that this image is not the background
 @param url The URL of the desired image.
 @param placeholderImage The placeholder image to be used while loading/on failure.
 @param size the image size
 */
- (void)setImageOnButtonWithURL:(NSURL *)url placeholderImage:(UIImage *)placeholderImage imageSize:(CGSize)size;

/**
 Execute this block once the user taps and releases inside the button
 @param the block to execute
 */
- (void)setHandlerBlock:(void(^)(void))handlerBlock;

@end
