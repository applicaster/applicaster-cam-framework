//
//  APInstagramModel.h
//  ApplicasterSDK
//
//  Created by Liviu Romascanu on 3/10/15.
//  Copyright (c) 2015 Applicaster. All rights reserved.
//

#import <Foundation/Foundation.h>

@interface APInstagramModel : NSObject {
    NSDictionary *_object;
}

/**
 Object Dictionary from JSON
 */
@property (nonatomic, readonly, strong) NSDictionary *object;

/**
 Initialization method using an object dictionary
 */
- (instancetype)initWithDictionary:(NSDictionary *)objectDictionary;

@end
