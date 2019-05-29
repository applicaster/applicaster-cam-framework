//
//  APImagePicker.h
//  applicaster
//
//  Created by Hagit Shemer on 2/4/14.
//  Copyright (c) 2014 Applicaster Ltd. All rights reserved.
//

@protocol APImagePickerDelegate

@required
/**
 Finished picking Media
 @param info info - dictionary with image under UIImagePickerControllerOriginalImage key
 */
- (void)finishedPickingMediaWithInfo:(NSDictionary *)info;
/**
 Canceled picking media
 */
- (void)pickingMediaCanceled;

@end

#pragma mark -

@interface APImagePicker : NSObject

+ (void)startImagePickerWithDelegate:(id<APImagePickerDelegate>)imagePickerDelegate;

@end
