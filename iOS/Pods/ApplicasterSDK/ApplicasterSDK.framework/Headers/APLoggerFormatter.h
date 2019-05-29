//
//  APLoggerFormatter.h
//  ApplicasterSDK
//
//  Created by Liviu Romascanu on 12/26/13.
//  Copyright (c) 2013 Applicaster. All rights reserved.
//

#import <Foundation/Foundation.h>

/**
 This implementation of DDLogFormatter protocol is used for formatting messages the "Applicaster way":
 yyyy/MM/dd HH:mm:ss timezone  [Log Level] - [File name:line Function name] Log Message
 */
@interface APLoggerFormatter : NSObject <DDLogFormatter>
{
    int atomicLoggerCount;
    NSDateFormatter *threadUnsafeDateFormatter;
}

@end
