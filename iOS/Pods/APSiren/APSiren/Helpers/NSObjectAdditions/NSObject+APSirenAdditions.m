//
// Created by Anton Kononenko on 3/15/15.
// Copyright (c) 2015 Applicaster LTD. All rights reserved.
//

#import "NSObject+APSirenAdditions.h"
#import "APSirenParser.h"

@implementation NSObject (APSirenAdditions)

- (BOOL)isNotEmpty
{
    return !([self isKindOfClass:[NSNull class]]
            || ([self respondsToSelector:@selector(emptyEntity)] && [(APSirenLinkEntity *)self emptyEntity])
            || ([self respondsToSelector:@selector(length)] && [(NSString *)self length] == 0)
            || ([self respondsToSelector:@selector(count)] && [(NSArray *)self count] == 0));
}

@end