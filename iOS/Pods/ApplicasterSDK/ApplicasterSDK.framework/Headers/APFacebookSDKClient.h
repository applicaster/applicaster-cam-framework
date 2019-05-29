//
//  APFacebookSDKClient.h
//  ApplicasterSDK
//
//  Facebook SDK Client - written to properly work with SDK 3.1 and the new active session mechanism
//  This SDK supports and implements old FB object to provide feed dialog operations
//
//  Created by Liviu Romascanu on 9/24/12.
//  Copyright (c) 2012 Applicaster. All rights reserved.
//

#import <Foundation/Foundation.h>

@class FBSDKGraphRequest, FBSDKGraphRequestConnection;

@class APFacebookCommentsObject;
@class APFacebookPostObject;
@class APFBGraphUser;

/** A notification using this name is used to pass on a dictionary of paramaters, to allow calling <openFeedWithDictionary:>. The parameters should be stored as the <code>userInfo</code> of the notification. */
extern NSString * const APFacebookOpenFeedNotification;
/** This notification is called when the facebook feed dialog is successfully sent. */
extern NSString * const APFacebookFeedSentNotification;
/** This notification is called when the facebook feed dialog is opened. */
extern NSString *const APFacebookFeedDidOpenNotification;
/** This notification is called when the facebook feed dialog is closed, regardless of the result. */
extern NSString *const APFacebookFeedDidCloseNotification;
/** This notification is sent when facebook did Login */
extern NSString * const APFacebookDidLoginNotification;
/** This notification is sent when facebook did Logout */
extern NSString * const APFacebookDidLogoutNotification;
/** This notification is sent when facebook didn't manage to Login */
extern NSString * const APFacebookDidNotLoginNotification;

/**
 A Facebook client that can be used to perform a large number of Facebook actions.
 */
@interface APFacebookSDKClient : NSObject

/**
 Facebook App ID
 */
@property (nonatomic, readonly) NSString *facebookAppID;

/**
 Params of a saved dialog request.
 These params are used in case we need to login. When returning to the application - The saved dialog will be displayed
 */
@property (nonatomic, retain) NSMutableDictionary *paramsForDialog;

/**
 @return a shared instance of this class.
 */
+ (APFacebookSDKClient *)sharedInstance;

/**
 This method should be called only once. Calling it more than once will do nothing and return the sharedInstance previously created.
 @param facebookAppID used to initialize the session with
 @param appDisplayName as appears in the facebook developer app page
 @return A new instance of APFacebookSDKClient.
 */
+ (instancetype)facebookSDKWithFacebookAppID:(NSString *)facebookAppID
                           andAppDisplayName:(NSString *)appDisplayName;

//Facebook implementation:

/**
 Close current active session.
 Also clears current token - used for Sign out
 */
- (void)closeSession;

/**
 Handle URL scheme by the facebook sdk
 @return YES if handled , NO otherwise
 */
- (BOOL)application:(UIApplication *)application
            openURL:(NSURL *)url
  sourceApplication:(NSString *)sourceApplication
         annotation:(id)annotation;

/**
 New facebook share method
 @param viewController - display on top if not fastappswitching to facebook app
 @param url - URL to share
 @param title - Share title
 @param description - Short share description
 @param imageURL - Shared Image URL
 */
- (void)shareFromViewController:(UIViewController *)viewController
                        withURL:(NSURL *)url
                      withTitle:(NSString *)title
                withDescription:(NSString *)description
                   withImageURL:(NSURL *)imageURL;

/**
 @return facebook token
 */
- (NSString *)accessToken;

/**
 @return facebook token expiration date
 */
- (NSDate *)expirationDate;

/**
 @return The currently logged in user's Facebook ID.
 */
- (NSString *)userID;

/**
 @return The currently logged in user's Name.
 */
- (NSString *)userName;

/**
 Gets the current Facebook user(ME) info with completion handler
 @param     completionHandler The Completion handler of the get me request returns with user dictionary @see FBGraphUser
 */
- (void)getCurrentUserWithCompletionHandler:(void(^)(APFBGraphUser *user, NSError *error))completion;

/**
 Manually call facebook authorization function
 @param forced - If true - Delete current token and re-authorize.
 */
- (void)authorizeFacebook:(BOOL)forced;

/**
 Manually call facebook authorization function
 @param forced - If true - Delete current token and re-authorize.
 @param completion - The completion that will be called after trying to login to Facebook. The completion will receive YES if the user is loged in to facebook, or NO it isn't. Returnes the error if there is any.
 */
- (void)authorizeFacebook:(BOOL)forced
               completion:(void (^)(BOOL logedIn, NSError *error))completion;

/**
 @return YES if facebook session is valid
 */
- (BOOL)isFacebookSessionValid;

/**
 Request aditional write permissions
 @discussion A new write permission will be actually requested only if it's not in the active session permissions. Otherwise completion block will be called immidiatly.
 @param writePermissions - Array of strings representing facebook write permissions
 @param completion - returning if the permission was granted and an error if one occurs.
 */
- (void)requestNewPublishPermissions:(NSArray *)writePermissions
                          completion:(void (^)(BOOL grantedPermission, NSError *error))completion;

/**
 Request aditional read permissions
 @discussion A new read permission will be actually requested only if it's not in the active session permissions. Otherwise completion block will be called immidiatly.
 @param readPermissions - Array of strings representing facebook read permissions
 @param completion - returning if the permission was granted and an error if one occurs.
 */
- (void)requestNewReadPermissions:(NSArray *)readPermissions
                       completion:(void (^)(BOOL grantedPermission, NSError *error))completion;

- (FBSDKGraphRequest *)requestWithGraphPath:(NSString *)graphPath
                                 withParams:(NSMutableDictionary *)params
                             withHTTPMethod:(NSString *)httpMethod
                      withCompletionHandler:(void (^)(FBSDKGraphRequestConnection *connection, id result, NSError *error))handler;

- (FBSDKGraphRequestConnection*)runFBSDKGraphRequestConnectionWithGraphPath:(NSString *)graphPath
                                              andParameters:(NSDictionary *)params
                                                 HTTPMethod:(NSString *)method
                                          completionHandler:(void (^)(FBSDKGraphRequestConnection *connection, id result, NSError *error))handler;

/**
 Get a user profile image
 @param profileID - ID of a certain user
 @return UIView - actually FBProfilePictureView with square image
 */
- (UIView *)getFacebookProfilePictureWithID:(NSString *)profileID;


/**
 Get a user profile image URL
 @param profileID - ID of a certain user
 @param size - size of the image required

 */
-(NSString*)getFacebookProfileImageUrlStringWithId:(NSString*)profileID andSize:(CGSize)size;


/**
 Get a user profile image URL - Class Method
 @param profileID - ID of a certain user
 @param size - size of the image required
 
 */
+ (NSString*)getFacebookProfileImageUrlStringWithId:(NSString*)profileID andSize:(CGSize)size;


/**
 Get self profile image with completion handler - to get self dictionary
 @param completion handler - returning a UIView - FBProfilePictureView with square image
 */
- (void)getSelfFacebookProfilePictureWithCompletionHandler:(void (^)(UIView *profilePictureView))completion;

/**
 Get profile picture in UIImage
 @param profileID The ID of the user whose picture is being retrieved.
 @param size Size for image - should be square
 @param completion handler that gets back a UIImage
 */
- (void)getFacebookProfilePictureImageWithID:(NSString *)profileID andSize:(CGSize)size andCompletionHandler:(void (^)(UIImage *profilePictureImage))completion;

/**
 Get your own profile picture in UIImage
 @param size Size for image - should be square
 @param completion Handler that gets back a UIImage
 */
- (void)getSelfFacebookProfilePictureImageWithSize:(CGSize)size andCompletionHandler:(void (^)(UIImage *profilePictureImage))completion;


/**
 Get profile picture in UIImage
 @param profileID The ID of the user whose picture is being retrieved.
 @param completion handler that gets back a UIImage
 */
- (void)getFacebookProfilePictureImageWithID:(NSString *)profileID andCompletionHandler:(void (^)(UIImage *profilePictureImage))completion;

/**
 Get your own profile picture in UIImage
 @param completion handler that gets back a UIImage
 */
- (void)getSelfFacebookProfilePictureImageWithCompletionHandler:(void (^)(UIImage *profilePictureImage))completion;

/**
 Post a feed on Facbook id
 @param idString - Facebook ID
 @param params - Dictionary that inculde's facebook parameters - https://developers.facebook.com/docs/reference/api/post/
 @param handler - Handler that at the end gets back YES if the post completed or NO if it failed.
 */
- (void)postFeedInID:(NSString *)idString withFacebookParams:(NSDictionary *)params withCompletionHandler:(void (^)(BOOL completed))handler;

#pragma mark - Facebook OpenGraph

/**
 Get posts for a page between startDate to endDate.
 @param facebookPageID facebook page ID.
 @param startDate only returns posts which were created after this date - if nil - default will be 30 days back from current date.
 @param endDate only returns posts that were created before the endDate - if nit - default is current date.
 @param filterFriends If YES, shows only the results of the user's friends. Otherwise shows all posts.
 @param handler A completion block to receive the results of the request.
 */
- (void)getPostsFromPageWithID:(NSString *)facebookPageID
                      fromDate:(NSDate*)startDate
                        toDate:(NSDate*)endDate
                 filterFriends:(BOOL)filterFriends
          andCompletionHandler:(void (^)(NSArray *postsArray))handler;

/**
 Get posts for a page between startDate to endDate.
 @param facebookPageID facebook page ID.
 @param startDate only returns posts which were created after this date - if nil - default will be 30 days back from current date.
 @param endDate only returns posts that were created before the endDate - if nit - default is current date.
 @param limit max number of posts to return. If limit is < 0 - there will be no limitation of the number of posts received.
 @param filterFriends If YES, shows only the results of the user's friends. Otherwise shows all posts. Doesn't work well with limit, so don't limit if filterFriends=YES.
 @param handler A completion block to receive the results of the request.
 */
- (void)getPostsFromPageWithID:(NSString *)facebookPageID
                      fromDate:(NSDate*)startDate
                        toDate:(NSDate*)endDate
            limitNumberOfPosts:(long)limit
                 filterFriends:(BOOL)filterFriends
          andCompletionHandler:(void (^)(NSArray *postsArray))handler;

/**
 Get all the friend of the current session's Facebook user.
 
 @param completion the completion that is called when the loading is finished. usersArray contains objects of type (NSMutableDictionary<FBGraphUser> *)
 */
- (void)getFacebookFriendsWithCompletion:(void (^)(NSArray *friendsArray))completion;

/**
 Add or remove the currently logged-in user's "like" to/from the given post.
 @param postId the id of the post to add to or remove from
 @param likes whether to "like" (YES) or "unlike" (NO) the post
 @param completion completion handler that receives YES if operation completed successfuly and NO otherwise
 */
- (void)performLikeForPostWithId:(NSString *)postId
                           likes:(BOOL)likes
                      completion:(void (^)(BOOL success))completion;

/**
 Creates a post to a given page by the currently logged-in user
 @param postText the post text to add
 @param image - image to add to the post; can be null
 @param pageID the ID of the page to post on
 @param completion completion handler that receives YES if operation completed successfuly and NO otherwise
 */
- (void)createPost:(NSString *)postText
         withImage:(UIImage *)image
     forPageWithID:(NSString *)pageID
        completion:(void (^)(NSString *resultPostId, NSError *error))completion;

/**
 Creates a post to a given page by the currently logged-in user
 @param postText the post text to add
 @param image - image to add to the post; can be null
 @param link - link url in string to add to the post - Note - Link is posted only if there is no image
 @param pageID the ID of the page to post on
 @param completion completion handler that receives YES if operation completed successfuly and NO otherwise
 @discussion Note - We will post a link - only if there is no image. If there is an image - link is not posted.
 */
- (void)createPost:(NSString *)postText
         withImage:(UIImage *)image
          withLink:(NSString *)link
     forPageWithID:(NSString *)pageID
        completion:(void (^)(NSString *resultPostId, NSError *error))completion;

/**
 Add a comment to a given post by the currently logged-in user
 @param commentText the comment to add
 @param image - image to add to the comment; can be null
 @param postId the ID of the post to attach the comment to
 @param completion completion handler that receives YES if operation completed successfuly and NO otherwise
 */
- (void)createComment:(NSString *)commentText
            withImage:(UIImage *)image
         onPostWithId:(NSString *)postId
           completion:(void (^)(NSString *resultCommentId, NSError *error))completion;

/**
 Get updated data for a post
 @param post
 @param completion A completion block that receives the post object returned
 */
- (void)getUpdatedPost:(APFacebookPostObject *)post
            completion:(void (^)(APFacebookPostObject *post))completion;

/**
 Get the largest image that the Facebook photo object with the given id has.
 @param photoID The Facebook Photo object's id.
 @param completion completion that will be called with the URL if success, or nil otherwise.
 */
- (void)getLargestImageURLForPhotoID:(NSString *)photoID
                          completion:(void (^)(NSString *largestImageURL))completion;

#pragma mark - Session permissions
/**
 Current active session permissions
 @return Array of strings of the current permissions.
 */
- (NSArray *)sessionPermissions;

/**
 Current active session declined permissions
 @return Array of strings of declined permissions of the current active session.
 */
- (NSArray *)sessionDeclinedPermissions;

/**
 Check if a certain permission has been granted
 @param permission - facebook permision string
 @return YES if the permission is granted on the current active session
 */
- (BOOL)hasGranted:(NSString *)permission;

/**
 Check if an entire array of permissions is granted in the current session
 @param permissionArray - aray of facebook permison strings
 @return YES if all the permissions are granted on the current active session
 */
- (BOOL)hasGrantedArray:(NSArray *)permissionsArray;
@end
