//
// Created by Anton Kononenko on 3/22/15.
// Copyright (c) 2015 Applicaster LTD. All rights reserved.
//

#import <Foundation/Foundation.h>

@interface NSDictionary (APSirenAdditions)

/**
*  Retrieve object from NSDictionary for expected class.
*
*  @param key           Will used to get value from json
*  @param expectedClass Checks if retrieved value is kind of expected class
*
*  @returns an Object from NSDictionary if it is of expected class and not empty otherwise returns nil
*/
- (id)objectForKey:(NSString *)key
     expectedClass:(Class)expectedClass;

/**
Adds to the receiving dictionary the entries from another dictionary.
If both dictionaries contain the same key, the receiving dictionary’s previous value object for that key is overridden.
Support in multi-level dictionaries: If both the receiving dictionary and otherDictionary contain the same key with a dictionary as a value,
the values of that dictionary which exist only at the receiving dictionary will remain untouched. All other values will be overridden.

@param: otherDictionary
*/
- (NSDictionary *)combineDictionaryWithDictionary:(NSDictionary *)otherDictionary;
@end