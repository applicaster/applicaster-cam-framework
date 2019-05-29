//
// Created by Anton Kononenko on 3/16/15.
// Copyright (c) 2015 Applicaster LTD. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <APSiren/NSObject+APSirenAdditions.h>

@interface NSArray (APSirenAdditions)
/**
* Create new sorted array of objects of the expected class from array of objects
*
*  @param array     Non-sorted array
*  @param expectedClass Kind of class to sort
*
*  @returns an array of objects, all of the same required class and not empty, if resultant array is empty, return nil
*/
+(NSArray *)arrayWithArray:(NSArray *)array
    expectedClassInObjects:(Class)expectedClass;
/**
* Check if Array has string inside
*
*  @param string
*
*  @returns Yes if string found otherwise NO
*/
-(BOOL)existsString:(NSString *)string;
@end