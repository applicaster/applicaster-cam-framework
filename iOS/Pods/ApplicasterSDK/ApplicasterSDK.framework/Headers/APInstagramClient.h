//
//  APInstagramClient.h
//  ApplicasterSDK
//
//  Created by Liviu Romascanu on 3/9/15.
//  Copyright (c) 2015 Applicaster. All rights reserved.
//

#import <Foundation/Foundation.h>

@class APInstagramPagination;
static NSString *const APInstagramClientDidLogin = @"APInstagramClientDidLogin";

/**
 Applicaster Instagram client
 Based on https://instagram.com/developer/
 */
@interface APInstagramClient : NSObject

/**
 Instagram Client ID
 */
@property (nonatomic, strong) NSString *clientID;

/**
 Access token - saved in the keychain
 token can be set to nil to delete from the keychain and will be deleted in case client ID changes.
*/
@property (nonatomic, strong) NSString *token;

/**
 App URL Scheme prefix
 */
@property (nonatomic, strong) NSString *urlSchemePrefix;

/**
 Shared instance
 Call this only after you have called setupSharedInstanceWithClientID:andURLSchemePrefix:
 */
+ (APInstagramClient *)sharedInstance;

/**
 Setup shared instance
 @param clientID - Instagram API Client ID
 @param urlSchemePrefix - App url scheme prefix
 */
+ (void)setupSharedInstanceWithClientID:(NSString *)clientID
                     andURLSchemePrefix:(NSString *)urlSchemePrefix;

/**
 @return YES if user is logged in - by checking the existence of a token
 */
- (BOOL)isLoggedIn;

/**
 Login to Instagram using Safari and provided URL Scheme Prefix
 */
- (void)loginToInstagramUsingSafari;

/**
 Logout
 */
- (void)logoutFromInstagram;

/**
 URL Scheme handling function
 @return YES only if handled the URL Scheme
 */
- (BOOL)application:(UIApplication *)application
            openURL:(NSURL *)url
  sourceApplication:(NSString *)sourceApplication
         annotation:(id)annotation;

/**
 Get the most recent media published by a user. May return a mix of both image and video types.
 @param userID - Instagram User ID - NOT name!
 @param minimumDate - Optional - Provide only media items newer then this date
 @param minimumMediaID - Optional - Only return Images newer then this media ID
 @param numberOfItems - The number of items to return
 @param succes - Success block returning Pagination Info and array of media items
 @param failure - Failure block returning Error of what went wrong
 */
- (void)getUserRecentMediaWithUserID:(NSString *)userID
                            withDate:(NSDate *)minimumDate
                  withMinimumMediaID:(NSString *)minimumMediaID
                   withNumberOfItems:(NSInteger)numberOfItems
                         withSuccess:(void (^)(APInstagramPagination *paginationInfo, NSArray *mediaArray))success
                         withFailure:(void (^)(NSError *error))failure;

/**
 Search for media in a given area. The default time span is set to 5 days.
 The time span must not exceed 7 days.
 Defaults time stamps cover the last 5 days.
 Can return mix of image and video types.
 @param latitude - Latitude of the center search coordinate. If used, lng is required.
 @param longitude - Longitude of the center search coordinate. If used, lat is required.
 @param Distance - Distance in meters - Recommended - 1000 (1KM) Maximum - 5000 (5KM).
 @param succes - Success block returning Pagination Info and array of media items
 @param failure - Failure block returning Error of what went wrong
 */
- (void)getMediaByLocationWithLatitude:(NSString *)latitude
                         withLongitude:(NSString *)longitude
                          withDistance:(NSString *)distance
                              withDate:(NSDate *)minimumDate
                    withMinimumMediaID:(NSString *)minimumMediaID
                           withSuccess:(void (^)(APInstagramPagination *paginationInfo, NSArray *mediaArray))success
                           withFailure:(void (^)(NSError *error))failure;

/**
 Get a list of recently tagged media. 
 Note that this media is ordered by when the media was tagged with this tag, rather than the order it was posted. 
 Use the max_tag_id and min_tag_id parameters in the pagination response to paginate through these objects. 
 Can return a mix of image and video types.
 @param tag - Hash Tag without the # sign
 @param minimumMediaID - Optional - Only return Images newer then this media ID
 @param numberOfItems - The number of items to return
 @param succes - Success block returning Pagination Info and array of media items
 @param failure - Failure block returning Error of what went wrong
 */
- (void)getTagRecentMediaWithTagName:(NSString *)tag
                  withMinimumMediaID:(NSString *)minimumMediaID
                   withNumberOfItems:(NSInteger)numberOfItems
                         withSuccess:(void (^)(APInstagramPagination *paginationInfo, NSArray *mediaArray))success
                         withFailure:(void (^)(NSError *error))failure;

/**
 Add or remove like from a media
 @param mediaID - To add like parameter to
 @param shouldLike - YES to add like , NO to remove like
 @param success - success complition block - no information returned
 @param failure - faliure completion block - return error
 */
- (void)likeMediaWithID:(NSString *)mediaID
             shouldLike:(BOOL)shouldLike
            withSuccess:(void (^)())success
            withFailure:(void (^)(NSError *error))failure;

@end
