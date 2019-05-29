//
// Created by Anton Kononenko on 3/16/15.
// Copyright (c) 2015 Applicaster LTD. All rights reserved.
//

#import "NSArray+APSirenAdditions.h"


@implementation NSArray (APSirenAdditions)

+(NSArray *)arrayWithArray:(NSArray *)array
    expectedClassInObjects:(Class)expectedClass {
    NSArray *retVal = nil;
    NSMutableArray *sortedArray = [NSMutableArray new];

    for (NSObject *object in array) {
        if ([object isKindOfClass:expectedClass] &&
                [object isNotEmpty]) {
            [sortedArray addObject:object];
        }
    }
    if ([sortedArray isNotEmpty]) {
        retVal = [sortedArray copy];
    }
    return retVal;
}

-(BOOL)existsString:(NSString *)string {
    BOOL retVal = NO;
    for (NSString *currentString in self) {
        if ([string isEqualToString:currentString]) {
            retVal = YES;
            break;
        }
    }
    return retVal;
}

@end