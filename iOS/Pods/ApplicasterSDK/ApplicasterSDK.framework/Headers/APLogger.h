//
//  APLogger.h
//  ApplicasterSDK
//
//  Created by Liviu Romascanu on 12/26/13.
//  Copyright (c) 2013 Applicaster. All rights reserved.
//

#import <CocoaLumberjack/DDLog.h>

@class DDFileLogger;
/**
 APLogger is now based on lumberjack.
 Logger start method will do the following:
 1. Start ASL - printing logs to the device console
 2. When available - start Debug terminal logging
 3. Write logs into files in a cyclic manner - 10 files 100kb each
 4. Add a formatter that uses the Applicaster format - please look at APLoggerFormatter for more info on that
 
 @discussion:
 If you would like to see console logs in color please follow this guide:
 https://github.com/CocoaLumberjack/CocoaLumberjack/wiki/XcodeColors
 Everything is set up in the code to print:
 * Errors in red
 * Warnings in Orange
 But be sure you first download and do the configuration of the plugin (not the code which is in place) first.
 */
@interface APLogger : NSObject {
    
}

/**
 File logger - for use with support mail
 */
@property (nonatomic, strong) DDFileLogger *fileLogger;

/**
 Singleton method to get logger shared instance
 */
+ (instancetype)sharedInstance;

/**
 Start and setup logger
 */
- (void)startLogger;

/**
  + *  Get the log content with a maximum byte size
  + *  @param maxSize maximum byte size allowed
  + *  @return string of the logger with maximum byte size.
  + */
- (NSString *)logFilesContentWithMaxSize:(NSInteger)maxSize;


@end

/**
 Macros and definitions used by APLogger from Lumberjack
 */

#define LOG_FLAG_ERROR    (1 << 0)  // 0...00001
#define LOG_FLAG_WARN     (1 << 1)  // 0...00010
#define LOG_FLAG_INFO     (1 << 2)  // 0...00100
#define LOG_FLAG_DEBUG    (1 << 3)  // 0...01000
#define LOG_FLAG_VERBOSE  (1 << 4)  // 0...10000


#ifdef DEBUG
static const int ddLogLevel = LOG_LEVEL_VERBOSE;
#else
static const int ddLogLevel = LOG_LEVEL_WARN;
#endif


#define LOG_LEVEL_OFF     0
#define LOG_LEVEL_ERROR   (LOG_FLAG_ERROR)                                                                          // 0...00001
#define LOG_LEVEL_WARN    (LOG_FLAG_ERROR | LOG_FLAG_WARN)                                                          // 0...00011
#define LOG_LEVEL_INFO    (LOG_FLAG_ERROR | LOG_FLAG_WARN | LOG_FLAG_INFO)                                          // 0...00111
#define LOG_LEVEL_DEBUG   (LOG_FLAG_ERROR | LOG_FLAG_WARN | LOG_FLAG_INFO | LOG_FLAG_DEBUG)                         // 0...01111
#define LOG_LEVEL_VERBOSE (LOG_FLAG_ERROR | LOG_FLAG_WARN | LOG_FLAG_INFO | LOG_FLAG_DEBUG | LOG_FLAG_VERBOSE)      // 0...11111

#define LOG_ERROR    (LOG_LEVEL_DEF & LOG_FLAG_ERROR)
#define LOG_WARN     (LOG_LEVEL_DEF & LOG_FLAG_WARN)
#define LOG_INFO     (LOG_LEVEL_DEF & LOG_FLAG_INFO)
#define LOG_DEBUG    (LOG_LEVEL_DEF & LOG_FLAG_DEBUG)
#define LOG_VERBOSE  (LOG_LEVEL_DEF & LOG_FLAG_VERBOSE)

#define LOG_ASYNC_ENABLED YES

#define LOG_ASYNC_ERROR    ( NO && LOG_ASYNC_ENABLED)
#define LOG_ASYNC_WARN     (YES && LOG_ASYNC_ENABLED)
#define LOG_ASYNC_INFO     (YES && LOG_ASYNC_ENABLED)
#define LOG_ASYNC_DEBUG    (YES && LOG_ASYNC_ENABLED)
#define LOG_ASYNC_VERBOSE  (YES && LOG_ASYNC_ENABLED)

#define DDLogError(frmt, ...)   LOG_OBJC_MAYBE(LOG_ASYNC_ERROR,   LOG_LEVEL_DEF, LOG_FLAG_ERROR,   0, frmt, ##__VA_ARGS__)
#define DDLogWarn(frmt, ...)    LOG_OBJC_MAYBE(LOG_ASYNC_WARN,    LOG_LEVEL_DEF, LOG_FLAG_WARN,    0, frmt, ##__VA_ARGS__)
#define DDLogInfo(frmt, ...)    LOG_OBJC_MAYBE(LOG_ASYNC_INFO,    LOG_LEVEL_DEF, LOG_FLAG_INFO,    0, frmt, ##__VA_ARGS__)
#define DDLogDebug(frmt, ...)   LOG_OBJC_MAYBE(LOG_ASYNC_DEBUG,   LOG_LEVEL_DEF, LOG_FLAG_DEBUG,   0, frmt, ##__VA_ARGS__)
#define DDLogVerbose(frmt, ...) LOG_OBJC_MAYBE(LOG_ASYNC_VERBOSE, LOG_LEVEL_DEF, LOG_FLAG_VERBOSE, 0, frmt, ##__VA_ARGS__)

#define DDLogCError(frmt, ...)   LOG_C_MAYBE(LOG_ASYNC_ERROR,   LOG_LEVEL_DEF, LOG_FLAG_ERROR,   0, frmt, ##__VA_ARGS__)
#define DDLogCWarn(frmt, ...)    LOG_C_MAYBE(LOG_ASYNC_WARN,    LOG_LEVEL_DEF, LOG_FLAG_WARN,    0, frmt, ##__VA_ARGS__)
#define DDLogCInfo(frmt, ...)    LOG_C_MAYBE(LOG_ASYNC_INFO,    LOG_LEVEL_DEF, LOG_FLAG_INFO,    0, frmt, ##__VA_ARGS__)
#define DDLogCDebug(frmt, ...)   LOG_C_MAYBE(LOG_ASYNC_DEBUG,   LOG_LEVEL_DEF, LOG_FLAG_DEBUG,   0, frmt, ##__VA_ARGS__)
#define DDLogCVerbose(frmt, ...) LOG_C_MAYBE(LOG_ASYNC_VERBOSE, LOG_LEVEL_DEF, LOG_FLAG_VERBOSE, 0, frmt, ##__VA_ARGS__)


#define APLoggerError(frmt, ...)   LOG_OBJC_MAYBE(LOG_ASYNC_ERROR,   LOG_LEVEL_DEF, LOG_FLAG_ERROR,   0, frmt, ##__VA_ARGS__)
#define APLoggerWarn(frmt, ...)    LOG_OBJC_MAYBE(LOG_ASYNC_WARN,    LOG_LEVEL_DEF, LOG_FLAG_WARN,    0, frmt, ##__VA_ARGS__)
#define APLoggerInfo(frmt, ...)    LOG_OBJC_MAYBE(LOG_ASYNC_INFO,    LOG_LEVEL_DEF, LOG_FLAG_INFO,    0, frmt, ##__VA_ARGS__)
#define APLoggerDebug(frmt, ...)   LOG_OBJC_MAYBE(LOG_ASYNC_DEBUG,   LOG_LEVEL_DEF, LOG_FLAG_DEBUG,   0, frmt, ##__VA_ARGS__)
#define APLoggerVerbose(frmt, ...) LOG_OBJC_MAYBE(LOG_ASYNC_VERBOSE, LOG_LEVEL_DEF, LOG_FLAG_VERBOSE, 0, frmt, ##__VA_ARGS__)

#