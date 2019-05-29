//
//  APSirenParserLoadingManager.h
//  SirenParser
//
//  Created by Anton Kononenko on 3/10/15.
//  Copyright (c) 2015 Anton Kononenko. All rights reserved.
//

#import <Foundation/Foundation.h>

@class APSirenEntity;

@interface APSirenParserLoadingManager : NSObject

/**
 *  Load and Parse Siren JSON from URL with session configuration
 *
 *  @param url Link to Siren JSON
 *  @param sessionConfiguration Custom configuration for NSURLSession
 *  @param completion   Has two params. 1. Error: not nil if there was a problem was during loading. 2. Converted root APSirenEntity instance, nil if empty or has Errors
 *  @note  If sessionConfiguration is nil, NSURLSession will use default configuration
 */
+(void)loadSirenWithURL:(NSURL *)url
          configuration:(NSURLSessionConfiguration *)sessionConfiguration
      completionHandler:(void (^)(NSError *error, APSirenEntity *rootSirenEntity))completion;
@end
