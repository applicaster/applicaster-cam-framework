//
//  APSocialShareSheetViewController.h
//  applicaster
//
//  Created by Liviu Romascanu on 1/27/14.
//  Copyright (c) 2014 Applicaster Ltd. All rights reserved.
//

#import <UIKit/UIKit.h>

/**
 Choose style to be either dark or light
 */
typedef enum{
	APSocialShareSheetStyleLight,
    APSocialShareSheetStyleDark,
} APSocialShareSheetStyle;

@interface APSocialShareSheetViewController : UIViewController <UICollectionViewDataSource, UICollectionViewDelegate>

/**
 Upper background view - including an overlay that darkens and blocks clicks on the rest of the app
 */
@property (unsafe_unretained, nonatomic) IBOutlet UIView *upperBackgroundView;

/**
 Lower background view - Appears black in iOS6 or blurred in iOS 7
 */
@property (unsafe_unretained, nonatomic) IBOutlet UIView *lowerBackgroundView;

/**
 Collection view of share options
 */
@property (unsafe_unretained, nonatomic) IBOutlet UICollectionView *shareSheetCollectionView;

/**
 NSMutable array that has APSocialShareSheetSharingProtocol conforming objects
 */
@property (nonatomic, strong) NSMutableArray *shareMethods;

/**
 Share Text
 */
@property (nonatomic, strong) NSDictionary *shareTextDict;

/**
 Share Subject
 */
@property (nonatomic, strong) NSString *shareSubject;

/**
 Share image
 */
@property (nonatomic, strong) UIImage *shareImage;

/**
 Share image
 */
@property (nonatomic, strong) NSURL *shareImageURLStr;

/**
 Link to share
 */
@property (nonatomic, strong) NSURL *linkURL;

/**
 iOS 7 Cancel Button
 */
@property (unsafe_unretained, nonatomic) IBOutlet UIButton *iOS7CancelButton;

/**
 iOS 6 Cancel Button
 */
@property (unsafe_unretained, nonatomic) IBOutlet UIButton *iOS6CancelButton;

/**
 Present a social sheet as a child view controller on top of a view controller
 @param viewController to present on top as child view controller. This view controller is also used for the blur effect
 @param animated - decides if to show it animated or not
 @param shareText - Text to share using dictionary
 @param shareText - Subject to share
 @param linkURL - Link to share
 @param style - Either dark or light style - Currently only Dark style is implemented
 @discussion
 An example for the share dictionary:
 {
 ShareTextFacebook = share for facebook - optional
 ShareTextTwitter = share for twitter - optional
 ShareTextMail = share for mail - optional
 ShareTextWhatsApp = share for whatsapp - optional
 ShareTextSMS = share for sms - optional
 ShareTextDefault = default share text - mandatory
 }
 */
+ (APSocialShareSheetViewController *)presentSocialViewControllerOnViewController:(UIViewController *)viewController
                                                                         animated:(BOOL)animated
                                                                         withText:(NSDictionary *)shareText
                                                                      withSubject:(NSString *)subject
                                                                         withLink:(NSURL *)linkURL
                                                                        withImage:(NSString *)imageUrlStr
                                                                        withStyle:(APSocialShareSheetStyle)style;


/**
 Present a social sheet as a child view controller on top of a view controller
 @param viewController to present on top as child view controller. This view controller is also used for the blur effect
 @param animated - decides if to show it animated or not
 @param shareText - Text to share using dictionary
 @param linkURL - Link to share
 @param style - Either dark or light style - Currently only Dark style is implemented
 @discussion
 An example for the share dictionary:
 {
 	ShareTextFacebook = share for facebook - optional
 	ShareTextTwitter = share for twitter - optional
 	ShareTextMail = share for mail - optional
 	ShareTextWhatsApp = share for whatsapp - optional
 	ShareTextSMS = share for sms - optional
 	ShareTextDefault = default share text - mandatory
 }
 */
+ (APSocialShareSheetViewController *)presentSocialViewControllerOnViewController:(UIViewController *)viewController
                                                                         animated:(BOOL)animated
                                                                         withText:(NSDictionary *)shareText
                                                                         withLink:(NSURL *)linkURL
                                                                        withImage:(NSString *)imageUrlStr
                                                                        withStyle:(APSocialShareSheetStyle)style;

/**
 Present a social sheet as a child view controller on top of a view controller
 @param viewController to present on top as child view controller. This view controller is also used for the blur effect
 @param animated - decides if to show it animated or not
 @param shareText - Text to share using a dictionary
 @param linkURL - Link to share
 @param style - Either dark or light style - Currently only Dark style is implemented
 @param aditionalSharingOptions - Must be complient with APSocialShareSheetSharingProtocol
 @discussion
 An example for the share dictionary:
 {
 	ShareTextFacebook = share for facebook - optional
 	ShareTextTwitter = share for twitter - optional
 	ShareTextMail = share for mail - optional
 	ShareTextWhatsApp = share for whatsapp - optional
 	ShareTextSMS = share for sms - optional
 	ShareTextDefault = default share text - mandatory
 }
 */
+ (APSocialShareSheetViewController *)presentSocialViewControllerOnViewController:(UIViewController *)viewController
                                                                         animated:(BOOL)animated
                                                                         withText:(NSDictionary *)shareText
                                                                         withLink:(NSURL *)linkURL
                                                                        withStyle:(APSocialShareSheetStyle)style
                                                      withAditionalSharingOptions:(NSMutableArray *)aditionalSharingOptions;

/**
 Cancel button clicked action
 This function will dismiss the social share and remove it from the parent view controller
 */
- (IBAction)cancelButtonClicked:(id)sender;

@end
