//
//  APSocialPlayerControlsView.h
//  ApplicasterSDK
//
//  This class was created inheriting from Player Controls in order to represent Opengraph player with activities from the Player controls
//  Make sure you set APFacebookClient after initializing and using the +playerControls method to get the controls
//
//  Created by Liviu Romascanu on 6/28/12.
//  Copyright (c) 2012 Applicaster. All rights reserved.
//
#import "APSocialActionView.h"
#import "APPlayerControlsView.h"

@class APFacebookSDKClient;
// Notifications for actions occurring.
extern NSString *const APSocialPlayerShareButtonPressedNotification;

// Keys used for the setting up the action dictionaries in <actionsArray>.
extern NSString *const APSocialPlayerControlsImagePrefixKey;
extern NSString *const APSocialPlayerControlsActionCommandKey;
extern NSString *const APSocialPlayerControlsTextKey;
extern NSString *const APSocialPlayerControlsActionPostedKey;

/**
 These are the social player controls that display the Open Graph actions available during video playback.
 <p>
 <h3>Subclassing notes:</h3>
 The only methods that need to be overridden for subclassing are <createActionsArray> and <imagesBundle>. <imagesBundle> will normally return [NSBundle mainBundle], while <createActionsArray> will return an array of dictionaries, as given in the documentation example.
 */
@interface APSocialPlayerControlsView : APPlayerControlsView <APSocialActionViewDelegate>

/**
 Native Share Facebook button
 */
@property (strong, nonatomic) IBOutlet UIButton *shareButton;

/**
 Social Action button
 */
@property (strong, nonatomic) IBOutlet UIButton *socialActionButton;

/**
 Social Action dropdown view
 */
@property (strong, nonatomic) APSocialActionView *socialActionView;


/**
 Image array supplied for the social action dropdown view
 */
@property (strong, nonatomic) NSArray *imageArray;

/**
 Actions Array - including dictionaries for each action
 */
@property (strong, nonatomic) NSArray *actionsArray;

/**
 facebook client - should be set right after initialization
 */
@property (strong, nonatomic) APFacebookSDKClient *facebookClient;

/**
 Current playing item publicPageURLPath
 */
@property (strong, nonatomic) NSString *publicPageURLPath;

/**
 BOOL value representing the equivalent NSUSerDefaults value to check if user opted in
 */
@property (assign, nonatomic) BOOL isUserOptedIn;

/**
 label used for toast message
 */
@property (strong, nonatomic) IBOutlet UILabel *toastLabel;
/**
 pop up message of instructions for the watch action
 */
@property (nonatomic, strong) IBOutlet UIView *instructionsView;

/**
 box selection for instructionsView
 */
@property (nonatomic, strong) IBOutlet UIButton *boxSelectionButton;

/**
 canel button of instructionsView
 */
@property (nonatomic, strong) IBOutlet UIButton *cancelButton;

/**
 backgroung of instructionsView
 */
@property (nonatomic, strong)IBOutlet UIImageView *backgroungInstructionsView;

/**
 Get an instance of the player controls from nib
 @return APPlayerControlsView initialized from nib
 */
+ (APSocialPlayerControlsView *)playerControls;

/**
 Share button click action
 @param sender The caller of this method.
 */
- (IBAction)shareButtonClicked:(id)sender;

/**
 Action button clicked action
 @param sender The caller of this method.
 */
- (IBAction)actionButtonClicked:(id)sender;

/**
 Method used to announce playing of a new item
 @param url of the public page of the relevant item
 */
- (void)playbackStartedWithPublicPageURL:(NSString *)url;

/**
 Method called when playback of a current item is ended - either from the done button or from the item finishing its playtime
 */
- (void)playbackEnded;

/**
 Post facebook OG activity
 @param action Action key.
 */
- (void)postFacebookOpenGraphActivityWithAction:(NSString *)action;

/**
 Post facebook OG activity and display relevant toast
 @param action Action key.
 @param name Action name.
 */
- (void)postFacebookOpenGraphActivityWithAction:(NSString *)action andActionName:(NSString *)name;

/**
 Create the initial hard coded action array, saved to <actionsArray>. The array must contain dictionaries of actions, e.g. such as
 <code>
 [NSMutableDictionary dictionaryWithObjectsAndKeys:
 @"social_player_cry",			APSocialPlayerControlsImagePrefixKey,
 @"og_itsontv:cry_with",		APSocialPlayerControlsActionCommandKey,
 [@"Cry" withKey:@"Cry"],		APSocialPlayerControlsTextKey,
 [NSNumber numberWithBool:NO],	APSocialPlayerControlsActionPostedKey,
 nil];
 </code>
 */
- (void)createActionsArray;

/**
 Performs watch action after 10 seconds
 */
- (void)showWatchAction;

@end
