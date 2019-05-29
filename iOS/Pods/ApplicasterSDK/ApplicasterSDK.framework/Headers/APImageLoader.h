//
//  APImageLoader.h
//  ApplicasterSDK
//
//  Created by Guy Kogus on 19/01/12.
//  Copyright (c) 2012 Applicaster. All rights reserved.
//

#import <Foundation/Foundation.h>

/**
 A loader for asynchronously loading images.
 */
@interface APImageLoader : NSObject

/**
 Uses the AFNetworking UIImageView category to load images quickly and efficiently.
 
 Asynchronously loads an image in the following order.
 
 1. From memory if it exists in cache.
 2. Else from the disk if it is stored on the hard drive.
 3. Else from the internet.
 
 @param url The url location of the image.
 @param success A block to be executed if the image is loaded successfully.
 @param failure A block object to be executed if the image fails to load.
 */
- (void)loadImageWithURL:(NSURL *)url
				 success:(void (^)(UIImage *image))success
				 failure:(void (^)(NSError *error))failure;

- (void)loadImageWithURLWithCachedInformation:(NSURL *)url
				 success:(void (^)(UIImage *image,BOOL isCached))success
				 failure:(void (^)(NSError *error))failure;

/**
 Cancel the current image loading. If the loading is cancelled, neither the success nor the failure callback blocks will be executed.
 */
- (void)cancel;

@end
