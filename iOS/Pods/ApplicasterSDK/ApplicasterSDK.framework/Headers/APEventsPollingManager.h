//
//  APEventsPollingManager.h
//  ApplicasterSDK
//
//  Created by Hagit Shemer on 2/24/14.
//  Copyright (c) 2014 Applicaster Ltd. All rights reserved.
//


@protocol APEventsPollingManager <NSObject>

/**
 Call when should start polling events
 **/
- (void)startPollingEvents;

/**
 Call when should stop polling events
 **/
- (void)stopPollingEvents;

/**
 Call when should reevaluate events.
 @param metadataDictionary - contains all relevant parameters.
 **/
-(void)updateMetadataWithDictionary:(NSDictionary *)metadataDictionary;

@end
