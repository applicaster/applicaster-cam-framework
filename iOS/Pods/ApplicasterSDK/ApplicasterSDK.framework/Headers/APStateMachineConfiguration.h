//
//  APStateMachineConfiguration.h
//  APStateMachine
//
//  Created by Guy Kogus on 28/12/11.
//  Copyright (c) 2011 __MyCompanyName__. All rights reserved.
//

#import <Foundation/Foundation.h>

@class APStateMachine;

/**
 This is the initial configuration used to define a state machine. 
 */
@interface APStateMachineConfiguration : NSObject

/** The initial state of the state machine. */
@property (copy, readonly) NSString *initialState;
/** The possible events the state machine can perform. The objects in this array are of type APStateMachineEvent. */
@property (strong, readonly) NSArray *events;

/**
 Initialise the configuration to have a given state and a list of possible events.
 
 The state can not be nil or an empty string.
 
 @param state The initial state of the machine.
 @param events An array of APStateMachineEvent objects. An exception will be raised if any other types of objects exist.
 @return An initialised APStateMachineConfiguration object.
 */
- (id)initInitialState:(NSString *const)state
			withEvents:(NSArray *)events;

@end
