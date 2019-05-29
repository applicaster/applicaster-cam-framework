//
//  APAtomFeedParser.h
//  applicaster
//
//  Created by Miri on 10/26/14.
//  Copyright (c) 2014 Applicaster Ltd. All rights reserved.
//

#import <Foundation/Foundation.h>

@class APAtomFeed;
@class AFHTTPRequestOperation;

@interface APAtomFeedParser : NSObject

/*
 ParsingComplete - Whether NSXMLParser parsing has completed
 */
@property (nonatomic, assign) BOOL parsingComplete;

/*
 IsFirstElement - Whether element has first - feed.
 */
@property (nonatomic, assign) BOOL isFirstElement;

/*
 */
- (instancetype)initWithAtomFeed:(APAtomFeed *)atomFeed;

/*
 Parse Applicaster Media Atom Feed
 @param: feed - model of atom feed.
 @param: error: if discarded - returns an error with explanation.
 */
- (void)parseOperation:(AFHTTPRequestOperation *)operation
        responseObject:(id)responseObject
 withCompletionHandler:(void (^)(BOOL success, NSError *error))completion;

@end
