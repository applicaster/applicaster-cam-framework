//
// Created by Anton Kononenko on 3/22/15.
// Copyright (c) 2015 Applicaster LTD. All rights reserved.
//

#import "NSDictionary+APSirenAdditions.h"
#import "NSObject+APSirenAdditions.h"

@implementation NSDictionary (APSirenAdditions)

- (id)objectForKey:(NSString *)key
               expectedClass:(Class)expectedClass {
    id retVal = nil;
    if ([self[key] isNotEmpty]) {
        NSObject *retrievedObject = self[key];
        if ([retrievedObject isKindOfClass:expectedClass] && [retrievedObject isNotEmpty]) {
            retVal = retrievedObject;
        }
    }
    return retVal;
}

- (NSDictionary *)combineDictionaryWithDictionary:(NSDictionary *)otherDictionary {
    NSMutableDictionary *retVal = [NSMutableDictionary dictionaryWithDictionary:self];
    for (id key in otherDictionary) {
        id value = otherDictionary[key];
        if ([value isKindOfClass:[NSDictionary class]]) {
            NSDictionary *internalDict = retVal[key];
            if (internalDict == nil) {
                [retVal setValue:value forKey:key];
            }
            else {
                NSDictionary *internalDictCopy = [internalDict mutableCopy];
                internalDictCopy = [internalDictCopy combineDictionaryWithDictionary:value];
                [retVal setValue:internalDictCopy forKey:key];
            }
        }
        else {
            [retVal setValue:value forKey:key];
        }
    }
    return [retVal copy];
}

@end
