//
//  ASIInputStream.h
//  Part of ASIHTTPRequest -> http://allseeing-i.com/ASIHTTPRequest
//
//  Created by Ben Copsey on 10/08/2009.
//  Copyright 2009 All-Seeing Interactive. All rights reserved.
//

#import <Foundation/Foundation.h>

@class APASIHTTPRequest;

// This is a wrapper for NSInputStream that pretends to be an NSInputStream itself
// Subclassing NSInputStream seems to be tricky, and may involve overriding undocumented methods, so we'll cheat instead.
// It is used by ASIHTTPRequest whenever we have a request body, and handles measuring and throttling the bandwidth used for uploading

@interface APASIInputStream : NSObject {
	NSInputStream *stream;
	APASIHTTPRequest *__unsafe_unretained request;
}
+ (id)inputStreamWithFileAtPath:(NSString *)path request:(APASIHTTPRequest *)request;
+ (id)inputStreamWithData:(NSData *)data request:(APASIHTTPRequest *)request;

@property (strong, nonatomic) NSInputStream *stream;
@property (unsafe_unretained, nonatomic) APASIHTTPRequest *request;
@end
