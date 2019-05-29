//
//  APProgramsProxy.h
//  ProgramsApp
//
//  Created by Tom Susel on 3/6/12.
//  Copyright (c) 2012 Applicaster. All rights reserved.
//

#import <UIKit/UIKit.h>

@class APChannel;
@class APCategory;

/**
 The programs proxy offers a way to load programs within a given time range. Programs will be loaded from the server on a per-day basis. The proxy will use then be able to load the required days to provide programs within a given date range.
 */
@interface APProgramsProxy : NSObject

+ (APProgramsProxy *)sharedProxy;

/**
 Retrieves an array of programs.
 @param channel - The channel from which we will load the programs.
 @param startTime - The minimum time. The a program would be returned if it's end time is after the start time.
 @param endTime - The local maximum time, a program would be returned if it's start time is before the end time.
 @param completion - The block that is called once the programs for the specified range is ready. The programs array may be nil in case of failure. The block may be called instantly in case the programs are already cached.
 @param forceReload forces method to load from server and not from cache.

*/
- (void)programsFromChannel:(APChannel *)channel
			  withStartDate:(NSDate *)startDate
				 andEndDate:(NSDate *)endDate
			dailyCompletion:(void (^)(NSArray *programs))completion
                forceReload:(BOOL)forceReload;
    

/**
 Retrieves an array of programs.
 @param channel - The channel from which we will load the programs.
 @param startTime - The minimum time. The a program would be returned if it's end time is after the start time.
 @param endTime - The local maximum time, a program would be returned if it's start time is before the end time.
 @param completion - The block that is called once the programs for the specified range is ready. The programs array may be nil in case of failure. The block may be called instantly in case the programs are already cached.
 */
- (void)programsFromChannel:(APChannel *)channel
			  withStartDate:(NSDate *)startDate
				 andEndDate:(NSDate *)endDate
			dailyCompletion:(void (^)(NSArray *programs))completion;

/**
 Retrieve up to 50 programs at a time using pagination. The programs are sorted from oldest to newest, so that page 0 contains the oldest programs.
 @param channel The channel whose programs are being searched.
 @param pageID The page ID of the programs.
 @param completion The completion block containing the programs from the given page.
 */
- (void)getAllProgramsForChannel:(APChannel *)channel
						  AtPage:(NSUInteger)pageID
					  completion:(void (^)(NSArray *programs))completion;

/**
 Retrieves programs that are connected to the show in particular date with pages.
 Each page can contains up to 50 items. The dateד should be passed timeless and in local time.
 @param fromDate The date that we want to receive the programs from this date.
 @param inDate The date that we want to receive the programs.
 @param atPage The page number.
 @param completion The completion handler to be run when the programs are loaded
 with params of requested model, array of the programs and BOOL of has next page or not.
 @param forceReload forces method to load from server and not from cache.
 */
- (void)programsForShowCategory:(APCategory *)showCategory
                       fromDate:(NSDate *)fromDate
                         inDate:(NSDate *)inDate
                         atPage:(NSUInteger)pageNumber
                     completion:(void (^)(APCategory *model, NSArray *programs, BOOL nextPage))completion
                    forceReload:(BOOL)forceReload;

/**
 Loads all programs that are connected to the show within a given time range.
 The dates should be passed timeless and in local time.
 @param startDate The starting point of the time range.
 @param endDate The ending point of the time range.
 @param completion The completion handler to be run when the programs are loaded
 with params of requested model and array of the programs.
 @param forceReload forces method to load from server and not from cache.
 */
- (void)programsForShowCategory:(APCategory *)showCategory
                      startDate:(NSDate *)startDate
                        endDate:(NSDate *)endDate
                     completion:(void (^)(APCategory *model ,NSArray *programs))completion
                    forceReload:(BOOL)forceReload;

@end
