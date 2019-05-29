//
//  APShareMoment.h
//  ApplicasterSDK
//
//  Created by Daniel Shein on 2/4/13.
//  Copyright (c) 2013 Applicaster. All rights reserved.
//

#import <UIKit/UIKit.h>
@import MessageUI;

@class APFacebookSDKClient;

@interface APCaptureMoment : UIView <MFMailComposeViewControllerDelegate>

@property (nonatomic, copy) NSString *publicPageUrl;
@property (nonatomic, assign) NSTimeInterval startPosition, endPosition;
@property (nonatomic, strong) void(^completionBlock)(BOOL didShare);

@property (nonatomic, strong) IBOutlet UIView *backgroundView, *promptView;
@property (nonatomic, strong) IBOutlet UILabel *shareLabel;
@property (nonatomic, strong) IBOutlet UIButton *closeButton;
@property (nonatomic, strong) IBOutlet UIButton *facebookButton;
@property (nonatomic, strong) IBOutlet UIButton *twitterButton;
@property (nonatomic, strong) IBOutlet UIButton *emailButton;
@property (nonatomic, strong) NSDictionary *analyticsDictionary;

/**
 Initialise a new Capture a Moment view.
 @param newViewController The root view controller above which sharing view controllers will be displayed.
 @param newFacebookClient The Facebook client through which sharing is done.
 @param reshare YES if this is a reshare of an already-captured video, NO if it is an original recording.
 */
+(id)captureViewWithRootViewController:(UIViewController *)newViewController
                  andFacebookSdkClient:(APFacebookSDKClient *)newFacebookClient
                               reshare:(BOOL)reshare;

-(IBAction)close:(id)sender;

-(IBAction)emailShare:(id)sender;
-(IBAction)facebookShare:(id)sender;
-(IBAction)twitterShare:(id)sender;

@end
