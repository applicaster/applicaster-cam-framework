//
// Created by Anton Kononenko on 3/15/15.
// Copyright (c) 2015 Applicaster LTD. All rights reserved.
//

#import <Foundation/Foundation.h>

@interface NSObject (APSirenAdditions)

/**
*  @b Check if object is Empty:
 
* Not Null. 
 
* If NSString length must be > 0.
 
* If Case NSSArray or NSDictionary count must be > 0.
 
* If Case APSirenEntity or APSirenLink has at least one parameter not nil.
*
* @returns Yes if one of the above is true, otherwise NO
*
* @see APSirenLink
*
* @see APSirenEntity
*/
- (BOOL)isNotEmpty;
@end