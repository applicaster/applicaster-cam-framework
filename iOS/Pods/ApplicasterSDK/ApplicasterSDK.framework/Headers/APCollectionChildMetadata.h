//
//  APCollectionChildMetadata.h
//  applicaster
//
//  Created by Liviu Romascanu on 3/5/14.
//  Copyright (c) 2014 Applicaster Ltd. All rights reserved.
//

#import <Foundation/Foundation.h>

/**
 Child collection metadata object represents metadata that comes on childs of collection objects that are in the contexts of a certain collection
 */
@interface APCollectionChildMetadata : NSObject

/**
 Promotion Name
 */
@property (nonatomic, strong) NSString *promotionName;

/**
 Sub Promotion Name
 */
@property (nonatomic, strong) NSString *subPromotionName;

@end
