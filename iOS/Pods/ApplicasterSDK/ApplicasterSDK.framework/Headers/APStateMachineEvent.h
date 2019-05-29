//
//  APStateMachineEvent.h
//  APStateMachine
//
//  Created by Guy Kogus on 28/12/11.
//  Copyright (c) 2011 __MyCompanyName__. All rights reserved.
//

#import <Foundation/Foundation.h>

/**
 An event defines a list of transitions, by containing the initial states and the final state after the named event has been completed.
 */
@interface APStateMachineEvent : NSObject

/** The name of the event. */
@property (copy, readonly) NSString *name;
/** The states from which the event can be called. */
@property (strong, readonly) NSArray *fromStates;
/** The state after the event has been executed. */
@property (copy, readonly) NSString *toState;

/**
 Initialise an event with an initial configuration.
 @param name The name of the event. Can not be nil or empty.
 @param fromStates An array of the names of each possible from state.
 @param toState The name of the state after the event.
 @return The initialised event.
 */
- (id)initWithName:(NSString *)name fromStates:(NSArray *)fromStates toState:(NSString *)toState;

/**
 Get an event with an initial configuration.
 @param name The name of the event. Can not be nil or empty.
 @param fromStates An array of the names of each possible from state.
 @param toState The name of the state after the event.
 @return The created event.
 */
+ (id)eventWithName:(NSString *)name fromStates:(NSArray *)fromStates toState:(NSString *)toState;

/**
 Get an event with an initial configuration.
 @param name The name of the event. Can not be nil or empty.
 @param fromState The original state.
 @param toState The name of the state after the event.
 @return The created event.
 */
+ (id)eventWithName:(NSString *)name fromState:(NSString *)fromState toState:(NSString *)toState;

@end
