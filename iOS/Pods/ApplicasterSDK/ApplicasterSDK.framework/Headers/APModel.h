//
//  APModel.h
//  applicaster
//
//  Created by Guy Kogus on 5/01/12.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//

#import <Foundation/Foundation.h>

#import "APStateMachine.h"

extern NSString *const APModelDidFinishLoadingNotification;
extern NSString *const APModelDidFailLoadingNotification;

#pragma mark - State machine events

extern NSString *const kAPModelStateInitial;
extern NSString *const kAPModelStateLoading;	// For loading from file/cache
extern NSString *const kAPModelStateDownloading;
extern NSString *const kAPModelStateLoaded;
extern NSString *const kAPModelStateFailed;

extern NSString *const kAPModelEventDownload;
extern NSString *const kAPModelEventLoadLocally;
extern NSString *const kAPModelEventLoadFailed;
extern NSString *const kAPModelEventLoadSucceeded;

/**
 The model observer will be sent notifications when a model has finished or failed loading.
 The model will be sent as the notification's <code>object</code>.
 */
@protocol APModelObserver <NSObject>
@optional
- (void)modelDidFinishLoadingNotification:(NSNotification *)notification;
- (void)modelDidFailLoadingNotification:(NSNotification *)notification;

@end


@protocol APUICustomizationProtocol <NSObject>

@optional

/**
 the color for the model
 */
@property (nonatomic, strong, readonly) NSString *modelColor;

@end

/**
 if the model has no model color, 
 but the color exist at the show category / top level category
 */
@protocol APUICustomizationExtendedProtocol <APUICustomizationProtocol>

@optional

/**
 The color from the show category
 */
@property (nonatomic, copy, readonly) NSString *modelShowCategoryColor;

/**
 The color from the top level category
 */
@property (nonatomic, copy, readonly) NSString *modelTopLevelCategoryColor;

@end


/**
 This is the basic class for all Applicaster business logic.
 */
@interface APModel : NSObject <APStateMachineDelegate>
{
	@protected
	id _object;
}

/** The unique identifier for this model within the given broadcaster. */
@property (nonatomic, copy, readonly) NSString *uniqueID;
/** This dictionary stores the extra parameters created on the CMS for this model. */
@property (strong, readonly) NSDictionary *extensionsDictionary;
/** The unique tag for this model. */
@property (nonatomic, strong, readonly) NSString *uiTag;

/** The dictionary representation of the model. */
@property (nonatomic, strong, readonly) id object;
/** The parametrs that will be used to search for the model in the online library. */
@property (nonatomic, strong, readonly) NSMutableDictionary *findOptions;

/** The state machine handling this model. */
@property (nonatomic, strong) APStateMachine *stateMachine;

@property (nonatomic, strong) NSDictionary *topLevelDictionary;

/**
 Returns a dictionary containing Image names as keys and URLs as values
 */
@property (unsafe_unretained, readonly) NSDictionary *imagesDictionary;

@property (readonly) NSTimeInterval loadTimeout;

/**
 Returns the name of the model key in the json objects that are populated.
 @return The JSON model key.
 */
+ (NSString *)jsonModelName;

/**
 Provides a path to the resource URL.
 @param routeOptions A dictionary of options that will be added to the query.
 @return The absolute URL path.
 */
+ (NSString *)resourceRoute:(NSDictionary *)routeOptions;

/**
 Initialise the model's object with the given dictionary.
 @param dictionary The JSON model as a dictionary.
 @return The newly created model with the data in the provided dictionary.
 */
- (id)initWithDictionary:(NSDictionary *)dictionary;

/**
 Initialise the model with the unique identifier required to find the object in the broadcaster's library.
 @param uniqueID The unique identifier of the object.
 @return A model that needs to be loaded.
 */
- (id)initWithUniqueID:(NSString *)uniqueID;

/**
 Set the model's object using the given dictionary.
 @param dictionary The JSON model as a dictionary.
 */
- (void)setObjectWithDictionary:(NSDictionary *)dictionary;

/**
 Not sure what this does...
 @return The ownership key.
 */
- (NSString*)ownershipKey;

/**
 Load the model.
 If we are offline and HQME is supported, we will attempt to load this from file. Otherwise we will load this from the URL provided by the resourceRoute: method.
 */
- (void)load ;

/**
 Load the model with completion handler.
 If we are offline and HQME is supported, we will attempt to load this from file. Otherwise we will load this from the URL provided by the resourceRoute: method.
 @param completion The completion block that is called when the load is completed with success of fail bool and the loaded model (if successful)
 */
- (void)loadWithCompletionHandler:(void (^)(BOOL success, APModel *model))completion;

/**
 Load the model with completion handler.
 If we are offline and HQME is supported, we will attempt to load this from file. Otherwise we will load this from the URL provided by the resourceRoute: method.
 @param completion The completion block that is called when the load is completed with success of fail bool and the loaded model (if successful)
 @param headersDict - You can send a dictionary (String, String) that will be added as headers to the HTTP request in case the model is loading from the server.
 */
- (void)loadWithCompletionHandler:(void (^)(BOOL success, APModel *model))completion
              withHTTPHeadersDict:(NSDictionary *)headersDict;

/**
 Cancel loading of the model. This will set the model to be in the failed state.
 */
- (void)cancel;

/**
 @return YES if the model is currently loading, NO otherwise.
 */
- (BOOL)isLoading;

/**
 @return YES if the model has successfully loaded, NO otherwise.
 */
- (BOOL)isLoaded;

/**
 @return YES if the model did fail loading the previous attempt, NO otherwise.
 */
- (BOOL)didFailLoading;

/**
 Adds an observer for when the model has finished/failed to load.
 @param observer The observer who conforms to the <APModelObserver> protocol.
 */
- (void)addLoadingObserver:(id <APModelObserver>)observer;

/**
 Removes the observer for responding to when the model has finished/failed to load.
 @param observer The observer who conforms to the <APModelObserver> protocol.
 */
- (void)removeLoadingObserver:(id <APModelObserver>)observer;

/**
 Returns a string URL of the model.
 @param name of the image from the image dictionary.
 @return image string URL
 */
- (NSString *)imageNamed:(NSString*)name;

/**
 Compares to models.
 @param otherModel The other model to compare to.
 @return YES if models are equal, NO if not.
 */
- (BOOL)isEqualToModel:(APModel *)otherModel;

//@property (readonly) NSDictionary *extensionsDictionary;
//@property (nonatomic, readonly) NSString *uiTag;
//
//- (BOOL)isCollection;
//- (NSArray*)allItems;
//
//- (id)initWithApplicasterController:(APApplicasterController *)controller;
//- (id)initWithApplicasterController:(APApplicasterController *)controller dictionary:(NSDictionary *)dictionary;
//-(id)initWithApplicasterController:(APApplicasterController *)controller uniqueID:(NSString *)uniqueID;
//
////TODO: use setter instead - which was generated by object
////Liviu - added in order to use from the HQMEApplicasterDataStore


/**
 Check if an object has offline content - this is done by checking the dictionary
 @return YES if has offline content , no otherwise
 */
- (BOOL)hasOfflineContent;

- (void)loadLocally;

/**
 This method resets the state machine and set the initial state to be kAPModelStateInitial.
 */
- (void)resetStateMachine;

@end
