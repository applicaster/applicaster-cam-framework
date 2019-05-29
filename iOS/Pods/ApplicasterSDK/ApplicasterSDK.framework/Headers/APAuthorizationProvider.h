//
//  APAuthenticationProvider.h
//  applicaster
//
//  Created by Reuven Levitsky on 6/22/15.
//  Copyright (c) 2013 Applicaster Ltd. All rights reserved.
//

#import <Foundation/Foundation.h>

/**

 */
@interface APAuthorizationProvider : NSObject {

}

/** 
 The dictionary representation of the model. 
 */
@property (nonatomic, strong, readonly) NSDictionary *object;

/** 
 The unique identifier for this model 
 */
@property (nonatomic, strong, readonly) NSString *uniqueID;

/**
 The unique identifier for this model
 */
@property (nonatomic, strong, readonly) NSString *storeFrontTitle;

/**
 The unique identifier for this model
 */
@property (nonatomic, strong, readonly) NSString *urlString;

/**
 The client type is used for us in order to map the right Client class to use for authorization.
 */
@property (nonatomic, strong, readonly) NSString *clientType;

/**
 Initialise the model's object with the given dictionary.
 @param dictionary The JSON model as a dictionary.
 @return The newly created model with the data in the provided dictionary.
 */
- (instancetype)initWithDictionary:(NSDictionary *)dictionary;

@end
