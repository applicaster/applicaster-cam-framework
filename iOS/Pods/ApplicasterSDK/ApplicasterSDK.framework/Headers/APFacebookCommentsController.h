//
//  APFacebookCommentsController.h
//  ApplicasterSDK
//
//  Created by Liviu Romascanu on 10/9/12.
//  Copyright (c) 2012 Applicaster. All rights reserved.
//

#import <Foundation/Foundation.h>

@class APFacebookCommentsDataSource, APFacebookCommentsView, APFacebookSDKClient;

/**
 The Facebook comments controller is a view controller that will often be displayed as a child view controller. It handles all the Facebook login operations on its own, so it simply needs to be added and hidden/shown as appropriate, using <commentsShowing> to check its status.
 */
@interface APFacebookCommentsController : UIViewController <UITableViewDelegate , UITableViewDataSource>

@property (nonatomic, strong) APFacebookSDKClient *facebookClient;
/** The ID of the Facebook open graph object whose comments will be displayed. */
@property (nonatomic, copy) NSString *facebookObjectID;
@property (nonatomic, strong) APFacebookCommentsView *facebookCommentsView;

@property (nonatomic, strong) NSArray *posts;
 
@property (nonatomic, strong) UIView *refreshHeaderView;
@property (nonatomic, strong) UILabel *refreshLabel;
@property (nonatomic, strong) UIImageView *refreshArrow;
@property (nonatomic, strong) UIActivityIndicatorView *refreshSpinner;

@property (nonatomic, assign) BOOL filterFriends;

/**
 Initialise a new Facebook comments controller using a given Facebook SDK, which handles all the login operations, and the Facebook open graph object ID.
 @param client The Facebook SDK client.
 @param facebokObjectID The ID of the Facebook open graph object whose comments will be displayed.
 @return A new Facebook comments controller.
 */
- (id)initWithFacebookSDK:(APFacebookSDKClient *)client
              andObjectID:(NSString *)facebookObjectID;

/**
 Load the posts of the current <FacebookObjectID>.
 @param handler An optional completion handler.
 @param filterFriends If YES, loads the posts of the user's friends. Otherwise loads all posts.
 */
- (void)loadPostsWithCompletionHandler:(void (^)(UIView *commentsView))handler fromFriends:(BOOL)filterFriends;

/**
 Checks if the comments are visible or not.
 @return YES if the comments have been displayed, NO otherwise.
 */
- (BOOL)commentsShowing;

/**
 Animates out the comments to the standard width.
 */
- (void)showComments;

/**
 Hides the comments to the right of the screen.
 */
- (void)hideComments;

/**
 This clever little method performs a number of steps. Firstly, it performs all the required validation, being that the view controller can receive child view controllers and that the Facebook object ID is not empty.
 <p>
 The <parentViewController>'s child view controllers are then traversed to see if a Facebook comments controller is available. If it is not, a new one is created. The controller then loads/shows/hides as is necessary, including reloading the comments if a new Facebook object ID is passed to an existing controller.
 
 @param parentViewController The view controller to which the Facebook comments controller will be added as a child. Must not be <code>nil</code>.
 @param client The Facebook SDK client that is responsible for handling all login. Must not be <code>nil</code>.
 @param facebookObjectID The ID of the Facebook open graph object whose comments are being displayed.
 @return If pre-iOS 5 or the Facebook object ID is invalid, returns <code>nil</code>. If it was created, the new Facebook comments controller, else it returns the reused controller.
 */
+ (APFacebookCommentsController *)toggleFacebookCommentsControllerAsChildOfViewController:(UIViewController *)parentViewController
																			withSDKClient:(APFacebookSDKClient *)client
																		 facebookObjectID:(NSString *)facebookObjectID;

@end
