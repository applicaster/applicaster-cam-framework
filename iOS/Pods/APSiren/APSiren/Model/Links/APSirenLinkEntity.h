//
//  APSirenLinkEntity.h
//  SirenParser
//
//  Created by Anton Kononenko on 3/12/15.
//  Copyright (c) 2015 Anton Kononenko. All rights reserved.
//

#import <Foundation/Foundation.h>

@interface APSirenLinkEntity : NSObject <NSCoding>

@property (nonatomic, strong) NSString *title;
@property (nonatomic, strong) NSArray  *relations;
@property (nonatomic, strong) NSString *hRef;

#pragma mark - Helpers methods

/**
 *  Check if all parameters are nil
 *
 *  @return Bool value. Yes in case nil, otherwise NO
 */
-(BOOL)emptyEntity;

@end
