//
//  APTakeoverCallbackHandler.h
//  applicaster
//
//  Created by Liviu Romascanu on 11/25/12.
//  Copyright (c) 2012 Applicaster Ltd. All rights reserved.
//

#import "APCallbackHandler.h"
#import "APTakeOverEventViewController.h"

@interface APTakeoverCallbackHandler : APCallbackHandler <APTakeOverEventViewControllerDelegate>

/**
 Takeover event view controller
 Used to display view controller with sync button
 */
@property (nonatomic, strong) APTakeOverEventViewController *takeOverEventViewController;

/**
 Pause listen to applicaster activities.
 */
- (void)pauseActivitiesListener;

/**
 Resume listen to applicaster activities.
 */
- (void)resumeActivitiesListener;

@end
