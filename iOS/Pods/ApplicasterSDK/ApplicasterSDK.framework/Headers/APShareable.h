//
//  APPlayable.h
//  applicaster
//
//  Created by Tom Susel on 1/11/12.
//  Copyright (c) 2012 Applicaster. All rights reserved.
//

#import <Foundation/Foundation.h>

/**
 A protocol for shareable items.
 */
@protocol APShareable <NSObject>

#pragma mark Required

@required

/**
 Returns the url that is used for sharing.
 If nil is returned, this item is considered to be non-shareable.
 Implement it and returns the correct url if your model is shareable.
 
 @return the share url.
 */
- (NSString *)shareURL;

#pragma mark Optional

@optional



@end
