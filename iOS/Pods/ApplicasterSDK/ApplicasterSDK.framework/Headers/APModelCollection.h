//
//  APCollection.h
//  applicaster
//
//  Created by Tom Susel on 12/13/10.
//  Copyright 2010 __MyCompanyName__. All rights reserved.
//

#import <Foundation/Foundation.h>

@class APModelCollection;

/**
 @header
 APModellCollectionDelegate
 */
@protocol APModelCollectionDelegate <NSObject>

@optional
- (void)collectionDidFinishedLoading:(APModelCollection*)aCollection;
- (void)collection:(APModelCollection*)aCollection didFailWithError:(NSError*)error;

@end

/**
 @header
 APModelCollection
 @discussion
 APModelCollection is a class that given an APModell class will enable loading a list of that model.
 (Index function in the server as opposed to Show when loading a single model)
 This is a renaming of APCollection
 */
@interface APModelCollection : NSObject
{
	Class _targetClass;
    NSMutableDictionary *_findOptions;
}

/**
 Model Collection Delegate
 */
@property (nonatomic, unsafe_unretained) id<APModelCollectionDelegate> delegate;

/**
 Is The Model collection loading
 */
@property (nonatomic, readonly) BOOL isLoading;

/**
 Is the model collection loaded
 */
@property (nonatomic, readonly) BOOL isLoaded;

/**
 The actual Array of the models
 */
@property (nonatomic, strong, readonly) NSArray *collection;

/**
 Find options for the route
 */
@property (nonatomic, strong, readonly) NSMutableDictionary *findOptions;

/**
 Init with the class of the objects
 */
- (id)initWithClass:(Class)aClass;

/**
 Load with specific params and route options
 */
- (void)loadWithParameters:parameters routeOptions:routeOptions;

/**
 Load - will use the model class route options
 */
- (void)load;

/**
 Load the collection with completionBlock.
 @param completionBlock The completionBlock is called when the loading is done. The completion block will return the self object @see APCollection, and if the loading is failed it will return nil.
 @discussion
 You can now mix the use of the block and the delegate method. Both will get called
 */
- (void)loadWithCompletionBlock:(void (^)(APModelCollection *object))completionBlock;
@end
