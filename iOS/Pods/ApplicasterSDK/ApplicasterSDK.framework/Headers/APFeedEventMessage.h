//
//  APFeedEventMessage.h
//  applicaster
//
//  Created by Liviu Romascanu on 8/1/13.
//  Copyright (c) 2013 Applicaster Ltd. All rights reserved.
//

#import "APFeedStarsEvent.h"

@interface APFeedEventMessage : APFeedStarsEvent

- (id)initWithTextMessage:(NSString *)message andDate:(NSDate *)date;

@end
