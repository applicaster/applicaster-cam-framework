//
//  TongueViewController.h
//  TongueDemo
//
//  Created by OmerV on 11/21/12.
//  Copyright (c) 2012 OmerV. All rights reserved.
//

#import <UIKit/UIKit.h>
#import "APTimedWebViewControllerDelegate.h"

extern NSString * const APTakeOverCallForActionKey;
extern NSString * const APTakeOverBackgroundImageKey;

@class APButton;

@protocol APTakeOverEventViewControllerDelegate <NSObject>
@required

/**
 Updates the delegate when the event finished - either by clicking the close button or ending the activity from the web view
 */
- (void)takeoverEventViewControllerFinished;

/**
 Function called when the takeover viewWillDissappear is called. Implement this method in order to hide takeOver so it will not be shown on the disappearing ViewController.
 */
- (void)takeoverEventViewControllerWillDissappear;

/**
  Function called when the takeover is covered (did dissappear) and the sync / close buttons where not clicked.
 */
- (void)takeoverEventViewControllerDidDissappearAndNotClicked;

@end

@interface APTakeOverEventViewController : UIViewController <APTimedWebViewControllerDelegate>

/**
 user-provided image for the top part of the sync view
 */
@property (weak, nonatomic) IBOutlet UIImageView *syncImageView;

/**
 Close Takeover event button
 */
@property (weak, nonatomic) IBOutlet APButton *closeButton;

/**
 Sync button - customizable
 */
@property (weak, nonatomic) IBOutlet APButton *syncButton;

/**
 Call to action text label
 */
@property (weak, nonatomic) IBOutlet UILabel *callToActionLabel;

/**
 Container view - contains everything but the background
 */
@property (weak, nonatomic) IBOutlet UIView *containerView;

/**
 Bottom rounded corners view (tongue style)
 */
@property (weak, nonatomic) IBOutlet UIView *tongueView;
 
/**
 Delegate - used to properly dismiss the takeover event view controller
 */
@property (nonatomic, weak) NSObject<APTakeOverEventViewControllerDelegate> *delegate;

/**
 Initialize Takeover Event View Controller
 @param Link dictionary - compatible with APTimedWebViewController
 @param button dictionary - used to customize sync button background (masked element) and includes call to action text
 @return APTakeoverEventViewController
 */
- (APTakeOverEventViewController *)initWithLinkDictionary:(NSDictionary *)linkDictionary
                                   andSnyButtonDictionary:(NSDictionary *)buttonDictionary;

/**
 Animate button entrance
 */
- (void)animateTongueEntrance;

/**
 Animate Tongue exit
 */
- (void)animateTongueExit;

/**
 Sync button clicked
 */
- (IBAction)syncButtonClicked:(id)sender;

/**
 Close button clicked
 */
- (IBAction)closeButtonClicked:(id)sender;

/**
 Prepeare to display takeover event view controller
 Loads and processes the background image before updating the handler
 */
- (void)prepeareToDisplayWithCompletionHandler:(void(^)(APTakeOverEventViewController *takeoverEventViewController))handler;

@end
