//
//  APURLRedirect.h
//  applicaster
//
//  Created by Guy Kogus on 16/07/12.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//

#import <Foundation/Foundation.h>

/**
 This class is responsible for performing all the redirect logic to provide the final, correct URL.
 */
@interface APURLRedirect : NSObject

/**
 This method uses the redirects returned by NSURLConnection to find the desired page. If the final page is less than 1Kb in size, it will parse it for JavaScript to see if it redirects using a JavaScript callback.
 @param originURL The starting URL for the redirect.
 @param completionHandler The block that will be returned the final URL of the redirects.
 */
- (void)retrieveFinalURLFor:(NSURL *)originURL withCompletionHandler:(void (^)(NSURL *finalURL))completionHandler;

/**
 Cancels the last retrieval.
 */
- (void)cancel;

@end
