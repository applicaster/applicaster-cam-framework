//
//  APImageFromDataLoader.h
//  ApplicasterSDK
//
//  Created by Guy Kogus on 11/10/12.
//  Copyright (c) 2012 Applicaster. All rights reserved.
//

#import <Foundation/Foundation.h>

/**
 Most of the time, calling [UIImage imageWithData:...] directly is enough. This operation, however, can take upwards of 0.1 seconds, which can have a serious affect when scrolling in a table view.
 */
@interface APImageFromDataLoader : NSObject

/** A property indicating if the operation was cancelled. */
@property (readonly, getter = isCancelled) BOOL cancelled;

/**
 Cancels the image loading. The [UIImage imageWithData:...] method can't be stopped, but once it's finished the image will be unused and destroyed.
 Once the loader is cancelled it is unusable and should be destroyed. The original completion handler is not called if the loading is cancelled.
 */
- (void)cancel;

/**
 Generates an image on a background thread and, if the loader is not cancelled, sends the new image to the completion handler.
 The completion handler will always be called on the main thread. This is done because, for the most part, images are used in UI.
 
 @param data The data from which to generate the image.
 @param completion The completion handler that will receive the generated image. This must not be nil.
 @return The loader object. You would only want to keep a reference to this if the completion handler is cancellable.
 
 @exception NSInternalInconsistencyException Thrown if the completionHandler parameter is nil.
 */
+ (APImageFromDataLoader *)imageLoaderWithData:(NSData *)data completionHandler:(void (^)(UIImage *image))completion;

@end
