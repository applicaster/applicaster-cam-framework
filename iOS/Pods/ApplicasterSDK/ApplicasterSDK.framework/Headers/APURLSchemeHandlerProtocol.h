//
//  APURLSchemeHandlerProtocol.h
//  applicaster
//
//  Created by dan g / applicaster on 4/27/14.
//  Copyright (c) 2014 Applicaster Ltd. All rights reserved.
//


#import <Foundation/Foundation.h>

/**
 This protocol is used to handle url scheme for submoduls in SDK (example:feed-2-iOS)
 */
@protocol APURLSchemeHandlerProtocol <NSObject>

@required

/**
 Share with text and link
 @param timelineID - the timeline id
 */
- (void)openURL:(NSMutableDictionary *)params;

@optional


@end
