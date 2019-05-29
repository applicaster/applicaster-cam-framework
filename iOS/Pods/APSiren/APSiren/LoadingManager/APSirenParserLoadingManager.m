//
//  APSirenParserLoadingManager.m
//  SirenParser
//
//  Created by Anton Kononenko on 3/10/15.
//  Copyright (c) 2015 Anton Kononenko. All rights reserved.
//

#import "APSirenParserLoadingManager.h"
#import "APSirenParser.h"

@interface APSirenParserLoadingManager () <NSURLSessionDelegate>

@end

@implementation APSirenParserLoadingManager

+(void)loadSirenWithURL:(NSURL *)url
          configuration:(NSURLSessionConfiguration *)sessionConfiguration
      completionHandler:(void (^)(NSError *error, APSirenEntity *rootSirenEntity))completion {
    if (url) {
        [self loadURL:url
        configuration:sessionConfiguration
    completionHandler:^(NSError *error, NSDictionary *JSON) {
        dispatch_async(dispatch_get_main_queue(), ^{
            if (JSON) {
            [APSirenFactory convertJSONToSirenEntity:JSON
                                        parentEntity:nil
                                   completionHandler:^(NSError *convertError, APSirenEntity *rootSirenEntity) {
                                       completion(convertError, rootSirenEntity);
                                   }];
            } else {
                completion (error, nil);
            }
        });
    }];
    } else {
        NSError *error = [NSError errorWithDomain:NSInvalidArgumentException
                                             code:0
                                         userInfo:@{ NSLocalizedDescriptionKey : @"Can not start load Siren JSON without root URL" }];
        completion (error, nil);
    }
}

#pragma mark - Private methods

+(void)loadURL:(NSURL *)url
    configuration:(NSURLSessionConfiguration *)sessionConfiguration
completionHandler:(void (^)(NSError *error, id JSON))completion {
    NSURLSessionConfiguration *configuration = sessionConfiguration;
    if (configuration == nil) {
        configuration = [self sessionConfiguration];
    }
    
    __block APSirenParserLoadingManager *delegate = [APSirenParserLoadingManager new];

    NSURLSession *session = [NSURLSession sessionWithConfiguration:configuration
                                                          delegate:delegate
                                                     delegateQueue:[NSOperationQueue mainQueue]];
    
    __weak typeof(self) weakSelf = self;
    __block NSError *err = nil;

    [[session dataTaskWithURL:url
            completionHandler:^(NSData *data,
                    NSURLResponse *response,
                    NSError *error) {
                NSHTTPURLResponse *res = (NSHTTPURLResponse *)response;
                if (res.statusCode != 200) {
                    err = [NSError errorWithDomain:NSGenericException
                                              code:res.statusCode
                                          userInfo:@{NSLocalizedDescriptionKey: @"Request error. Code is HTTP status code."}];
                    completion(err, nil);
                } else {
                    if (data.length > 0){
                        [weakSelf parseDataToJSON:data
                                completionHandler:completion];
                    } else {
                        err = [NSError errorWithDomain:NSGenericException
                                                  code:res.statusCode
                                              userInfo:@{NSLocalizedDescriptionKey: @"Loaded data is empty"}];
                        completion (err, nil);
                    }
                }
            }] resume];
}

+(void)parseDataToJSON:(NSData *)data
     completionHandler:(void (^)(NSError *error, NSDictionary *JSON))completion {
    NSError *jsonError = nil;
    NSDictionary *jsonDict = [NSJSONSerialization JSONObjectWithData:data options:0 error:&jsonError];
    completion(jsonError, jsonDict);
}

+(NSURLSessionConfiguration *)sessionConfiguration {
    NSURLSessionConfiguration *sessionConfig = [NSURLSessionConfiguration defaultSessionConfiguration];
    return sessionConfig;
}

#pragma mark 

- (void)URLSession:(NSURLSession *)session task:(NSURLSessionTask *)task didReceiveChallenge:(NSURLAuthenticationChallenge *)challenge completionHandler:(void (^)(NSURLSessionAuthChallengeDisposition disposition, NSURLCredential *credential))completionHandler {
    completionHandler(NSURLSessionAuthChallengeUseCredential, [NSURLCredential credentialForTrust:challenge.protectionSpace.serverTrust]);
}

@end
