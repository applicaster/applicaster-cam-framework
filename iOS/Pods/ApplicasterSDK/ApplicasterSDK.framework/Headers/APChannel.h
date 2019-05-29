//
//  APChannel.h
//  applicaster
//
//  Created by Guy Kogus on 5/01/12.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//

@class  APModelCollection, APProgram;

#import "APPurchasableItem.h"
#import "APPlayable.h"

/**
 APChannel model represents a Live channel.
 
 All Channels come cashed on the APAccount model using [[[APApplicaster sharedInstance] account] channels] after the account is loaded.
 In order to use the correct one - Use UI Tags with the following function from APAccount:
 - (APChannel *)channelByUITag:(NSString *)uiTag;
 
 Channels that were recieved this way include cashed data only - Next program , Metadata and image dictionary.
 
 Channel can also be loaded by ID , for example: 
 <code>
 NSDictionary *dictID = [NSDictionary dictionaryWithObjectsAndKeys:channelID, @"id" , nil];
 NSDictionary *dictChannel = [NSDictionary dictionaryWithObjectsAndKeys:dictID , @"channel", nil];
 channel = [[[APChannel alloc] initWithApplicasterController:[APApplicasterController sharedInstance] dictionary:dictChannel] autorelease];
 </code>
 And load it like any other model with find options or use play directly.
 */
@interface APChannel : APPurchasableItem <APPlayable> {
	BOOL _playOnLoad;
	BOOL _needsPurchaseCheck;
    APModelCollection *_programs;
    
    APProgram *_nextProgram;
    APProgram *_nextLiveProgram;
    APProgram *_currentProgram;
}

#pragma mark - Properties

/**
 Live channel Stream URL
 */
@property (nonatomic, strong, readonly) NSString *streamURL;

/**
 Splash URL
 */
@property (nonatomic, strong, readonly) NSString *splashURL;

/**
 preroll URL
 */
@property (nonatomic, strong, readonly) NSString *prerollURL;

/**
 Channel Name
 */
@property (nonatomic, strong, readonly) NSString *name;

/**
 Web EPG URL
 */
@property (nonatomic, strong, readonly) NSString *epgURL;

/**
 Currently playing program name
 */
@property (nonatomic, strong, readonly) NSString *nowPlaying;

/**
 Next program to be displayed in the channel
 */
@property (nonatomic, strong, readonly) APProgram *nextProgram;

/**
 Current program to be displayed in the channel
 */
@property (nonatomic, strong, readonly) APProgram *currentProgram;

/**
 Next program to be displayed in the channel that is set as Live
 If nextLiveProgram return nil, you should load the method @nextPlayingProgramsWithCompletionHandler:
 */
@property (nonatomic, strong, readonly) APProgram *nextLiveProgram;

/**
 Product identifier for specific channel purchase
 */
@property (nonatomic, strong, readonly) NSArray	*productIdentifiers;

/**
 Default Image URL
 Unlike VOD Items and Categories - APChannel does not implement an image dictionary.
 Instead only a single image exist and should be used
 */
@property (nonatomic, strong, readonly) NSString *defaultImageURL;

/**
 Collection of all programs defined in the CMS
 */
@property (nonatomic, strong, readonly) APModelCollection *programs;

/**
 The Facebook object ID for comments.
 */
@property (unsafe_unretained, readonly) NSString *facebookObjectID;

#pragma mark - APChannel

/**
 Initialize a channel with name.
 As noted previously - this method should be avoided.
 Channels should be used by - [APAccount channelByUITag:<uiTag>]
 @param channelName The channel's name.
 @return APChannel object.
 */
- (id)initWithName:(NSString *)channelName;

/**
 Initialize a channel with ID.
 This method can be usually avoided.
 Channels should be used by - [APAccount channelByUITag:<uiTag>]
 @param channelID The ID of the channel to initialise.
 @return APChannel object
 */
- (id)initWithID:(NSString *)channelID;

/**
 Closes the player
 @param animated Closes the player animated or not animated
 */
- (void)closePlayerAnimated:(BOOL)animated;

/**
 Plays the channel using the new player, 
 showing the the new player with animated presentation
 */
- (void)play;

/**
 Plays the channel using the new player, 
 showing the the new player with animated or non animated presentation
 @param animated Present the new player animated or not animated
 */
- (void)playAnimated:(BOOL)animated;

/**
 Plays the channel using a new stream url.
 @param animated Present the new player animated or not animated
 @param overrideStreamURL the stream url that will be played
 */
- (void)playWithOverrideStreamURL:(NSString *)overrideStreamURL animated:(BOOL)animated;

/**
 Plays the channel using a new stream url.
 By default the player will be presented with animation.
 @param overrideStreamURL the stream url that will be played
 */
- (void)playWithOverrideStreamURL:(NSString *)overrideStreamURL;

/**
 Retrieve all the programs within a given time range.
 @param startDate The starting point of the time range.
 @param endDate The ending point of the time range.
 @param completion The completion handler to be run when the programs are loaded.
 @param forceReload forces method to load from server and not from cache.
*/
- (void)programsFromDate:(NSDate *)startDate
				  toDate:(NSDate *)endDate
			  completion:(void (^)(NSArray *programs))completion
             forceReload:(BOOL)forceReload;
    
/**
 Retrieve all the programs within a given time range.
 @param startDate The starting point of the time range.
 @param endDate The ending point of the time range.
 @param completion The completion handler to be run when the programs are loaded.
 */
- (void)programsFromDate:(NSDate *)startDate
				  toDate:(NSDate *)endDate
			  completion:(void (^)(NSArray *programs))completion;

/**
 Retrieve up to 50 programs at a time using pagination. The programs are sorted from oldest to newest, so that page 0 contains the oldest programs.
 @param pageID The page ID of the programs.
 @param completion The completion block containing the programs from the given page.
 */
- (void)getAllProgramsAtPage:(NSUInteger)pageID
				  completion:(void (^)(NSArray *programs))completion;

/**
 Get the currently playing program for this channel. If the channel's <nextProgram> property has finished, this will load the programs and get the most current one.
 @param completion  The completion handler that will return the latest program.
 */
- (void)nextPlayingProgramWithCompletionHandler:(void (^)(APProgram *program))completion;

/**
 Get the currently playing program for this channel. If the channel's <nextProgram> property has finished, this will load the programs and get the most current one.
 @param completion  The completion handler that will return the latest program.
 @param forceReload  BOOL that forces reload of next playing program.
 */
- (void)nextPlayingProgramWithCompletionHandler:(void (^)(APProgram *program))completion forceReload:(BOOL)forceReload;

    
/**
 Get the next playing programs for this channel. 
 @param completion  The completion handler that will return array of next programs.
 */
- (void)nextPlayingProgramsWithCompletionHandler:(void (^)(NSArray *programs))completion;

/**
 Get the next playing programs for this channel.
 @param completion  The completion handler that will return array of next programs.
 @param forceReload  BOOL that forces reload of next playing program.
*/
- (void)nextPlayingProgramsWithCompletionHandler:(void (^)(NSArray *programs))completion forceReload:(BOOL)forceReload;

/**
 Get the current Live program, or retrive next Live program in case if have no Live program for current time.
 @param completion The completion handler that will return current or next Live program.
 @param forceReload  BOOL that forces reload of next playing program.
*/
- (void)nextLiveProgramWithCompletionHandler:(void (^)(APProgram *program))completion forceReload:(BOOL)forceReload;

@end
