//
//  APEPGDay.h
//  Caracol
//
//  Created by dan g / applicaster on 7/28/13.
//  Copyright (c) 2013 Applicaster. All rights reserved.
//

@interface APEPGDay : NSObject

@property (nonatomic, strong) NSString *dayName;
@property (nonatomic, strong) NSString *dayDate;

/**
 
 */
@property (nonatomic, strong) NSDate *date;
@property (nonatomic, strong) NSString *locale;

/**
 initialize new day with custom locale or default (from SDK)
 @param day - the right NSDate
 @param localStr - the required localr for example:@"es_CR"
 */
- (id)initWithDay:(NSDate *)day andLocal:(NSString *)localStr;

@end
