//
//  APReachabilityManager.h
//  ApplicasterSDK
//
//  Created by dan g / applicaster on 1/17/13.
//  Copyright (c) 2013 Applicaster. All rights reserved.
//

#import <Foundation/Foundation.h>

/**
 The following Enum represents the possible states of HQME
 */
typedef enum{
	APHQMEStateInitial,     /**< The state where the application has just started and no network operation have yet to be tried */
	APHQMEStateOnline,			/*< The application is online and works agains the Applicaster server. In this state the models are pulled from online JSONs */
	APHQMEStateOffline,		/**< The device works offline agains the local server. In this state the models are pulled from the local file system */
	APHQMEStateUnavailable,	/**< This state is reached when opening the application for the first time in offline state. In this case - the basic models needed to load the application (like account) are not avilable. */
}APHQMEState;

@interface APReachabilityManager : NSObject

@property (nonatomic, assign) APHQMEState state;

+ (APReachabilityManager *)sharedInstance;

/**
HQME can customize state due to limited connectivity from online to offline
 the state is NOT the same state as APReachability provides.
 @return the HQME state
 */
- (APHQMEState)getHqmeStateFromHqmeManager;

/**
 Set the HQME state to the same state as HQME manger declared
 */
- (void)setHqmeStateInAPReachabilityManager:(APHQMEState)state;

@end
