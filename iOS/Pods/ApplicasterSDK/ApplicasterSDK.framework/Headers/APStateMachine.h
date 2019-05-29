//
//  APStateMachine.h
//  APStateMachine
//
//  Created by Guy Kogus on 28/12/11.
//  Copyright (c) 2011 __MyCompanyName__. All rights reserved.
//

#import <Foundation/Foundation.h>

@class APStateMachineConfiguration;
/** This exception is raised when a state machine attempts to perform an event while it is in transition. */
extern NSString *const kAPStateMachineInTransitionException;
/** This exception is raised when a state machine attempts to perform an event unavailable from its current state. */
extern NSString *const kAPStateMachineCannotPerformEventException;

@class APStateMachine;

/**
 The delegate protocol allows the state machine's target to know when it is transitioning between different states. All protocol methods are optional.
 
 [shouldPerformEvent]([APStateMachineDelegate stateMachine:shouldPerformEvent:fromState:toState:withArguments:]) should return NO if the target is not ready to perform the event.
 
 [shouldLeaveState]([APStateMachineDelegate stateMachine:shouldLeaveState:toState:afterEvent:withArguments:]) should return NO if it will asynchronously inform the state machine when it is ready to complete the transition to the new state. This is done by invoking the [transition]([APStateMachine transition]) method.
 
 The order of protocol methods is:
 
 1. shouldPerformEvent
 2. didEnterState
 3. didChangeState
 4. didPerformEvent
 5. shouldLeaveState
 */
@protocol APStateMachineDelegate <NSObject>

@optional

/**
 This method is called before the event is performed and checks if the target is ready to perform it.
 @param stateMachine The target's state machine.
 @param event The name of the event about to be called.
 @param from The current state.
 @param to The next potential state.
 @param arguments An optional dictionary of arguments that were originally passed in to the performEvent:withArguments: method.
 @return YES if the target can continue with the event, NO otherwise.
 */
- (BOOL)stateMachine:(APStateMachine *)stateMachine
  shouldPerformEvent:(NSString *)event
		   fromState:(NSString *)from
			 toState:(NSString *)to
	   withArguments:(NSDictionary *)arguments;

/**
 This method is called once we are ready to enter the new state.
 @param stateMachine The target's state machine.
 @param event The name of the event about to be called.
 @param from The current state.
 @param to The next state.
 @param arguments An optional dictionary of arguments that were originally passed in to the performEvent:withArguments: method.
 */
- (void)stateMachine:(APStateMachine *)stateMachine
	   didEnterState:(NSString *)from
			 toState:(NSString *)to
		  afterEvent:(NSString *)event
	   withArguments:(NSDictionary *)arguments;

/**
 This method is called between the enterState and didEvent callbacks.
 @param stateMachine The target's state machine.
 @param event The name of the event about to be called.
 @param from The current state.
 @param to The next state.
 @param arguments An optional dictionary of arguments that were originally passed in to the performEvent:withArguments: method.
 */
- (void)stateMachine:(APStateMachine *)stateMachine
  didChangeFromState:(NSString *)from
			 toState:(NSString *)to
		  afterEvent:(NSString *)event
	   withArguments:(NSDictionary *)arguments;

/**
 This method is called after we have changed from one state to the next.
 @param stateMachine The target's state machine.
 @param event The name of the event about to be called.
 @param from The current state.
 @param to The next state.
 @param arguments An optional dictionary of arguments that were originally passed in to the performEvent:withArguments: method.
 */
- (void)stateMachine:(APStateMachine *)stateMachine
	 didPerformEvent:(NSString *)event
		   fromState:(NSString *)from
			 toState:(NSString *)to
	   withArguments:(NSDictionary *)arguments;

/**
 This method is called once the state machine is ready to move on to the next state.
 If it returns NO the inTransition value is set to YES. We will not allowing transitioning to the next state until the [transition]([APStateMachine transition]) method is called.
 @param stateMachine The target's state machine.
 @param from The original state.
 @param to The new state.
 @param event The name of the event that was called.
 @param arguments An optional dictionary of arguments that were originally passed in to the performEvent:withArguments: method.
 @return YES if the target is ready to complete the event, NO if we want to wait asynchronously to complete the transition.
 */
- (BOOL)stateMachine:(APStateMachine *)stateMachine 
	shouldLeaveState:(NSString *)from
			 toState:(NSString *)to
		  afterEvent:(NSString *)event
	withArguments:(NSDictionary *)arguments;

@end

/**
 State machines are used for monitoring the behaviour of an object. It allows developers to define how they want objects to behave in a clearly defined manner.
 
 State machines are defined by creating an <APStateMachineConfiguration> object and calling the [stateMachineWithConfiguration:delegate:]([APStateMachine stateMachineWithConfiguration:delegate:]) method.
 
 ### ASYNCHRONOUS BEHAVIOUR
 
 Sometimes the object may want to leave the state machine 'in transition' between one state and another. For example, if we are waiting for a view to complete an animation, we will call the event in the animation block, and then call the <transition> method in the finish block.
 The object must also return NO in the [stateMachine:shouldLeaveState:toState:afterEvent:withArguments:](APStateMachineDelegate stateMachine:shouldLeaveState:toState:afterEvent:withArguments:) method in the <APStateMachineDelegate> protocol.
 */
@interface APStateMachine : NSObject

/** The object for which this state machine is being created. */
@property (readonly, unsafe_unretained) id <APStateMachineDelegate> delegate;
/** The current state of the machine. */
@property (readonly, copy) NSString *currentState;
/** YES if the state machine is in transition, NO otherwise. */
@property (readonly, assign, getter = isInTransition) BOOL inTransition;

/**
 Perform the given event.
 @param event The event being performed.
 @param arguments An optional dictionary of arguments that will be passed on to the callback methods.
 @exception kAPStateMachineInTransitionException If the state machine is in transition while we're trying to perform another event.
 @exception kAPStateMachineCannotPerformEventException If the state machine can not perform the event from its current state.
 */
- (void)performEvent:(NSString *)event withArguments:(NSDictionary *)arguments;

/**
 This is a convenience method that calls
 <code>[self performEvent:event withArguments:nil]</code>
 @param event The event being performed.
 */
- (void)performEvent:(NSString *)event;

/**
 Checks if the state machine is in the given state.
 @param state The name of the state we're looking for.
 @return YES if we're in the current state. NO otherwise.
 */
- (BOOL)is:(NSString *)state;

/**
 Checks if we can perform the event by ensuring that there is a to state from the current state and that we are not in transition.
 @param eventName The name of the event.
 @return YES if we can perform this event, NO otherwise.
 */
- (BOOL)can:(NSString *)eventName;

/**
 This is a convenience method that returns <code>![self can:eventName]</code>
 @param eventName The name of the event.
 @return NO if we can perform this event, YES otherwise.
 */
- (BOOL)cannot:(NSString *)eventName;

/**
 This method alternates between being in transition and finished transition. It is used for asynchronously letting the state machine move from one state to the next.
 */
- (void)transition;

/**
 Returns a state machine with the given initial configuration.
 @param cfg The configuration defining the state machine.
 @param delegate The object for which this state machine is being created.
 @return The new state machine.
 */
+ (APStateMachine *)stateMachineWithConfiguration:(APStateMachineConfiguration *)cfg delegate:(id <APStateMachineDelegate>)delegate;

@end
