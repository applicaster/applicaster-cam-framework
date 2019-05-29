//
//  APSocialSharingManager.h
//  Caracol
//
//  Created by Hagit Shemer on 10/8/13.
//  Copyright (c) 2013 Applicaster. All rights reserved.
//

#import <Foundation/Foundation.h>

@class APFacebookSDKClient;

extern NSString * const kAPTwitterSharedDoneNotification;
extern NSString * const kAPTwitterSharedCancelledNotification;

extern NSString * const APShowMailSentNotification;
extern NSString * const kAPMailShareFailedNotification;

@interface APSocialSharingManager : NSObject

@property (nonatomic, strong) APFacebookSDKClient *facebookClient;

+ (APSocialSharingManager *)sharedInstance;

- (void)shareViaNativeShare:(NSString *)text
                  shareLink:(NSURL *)shareLink
      onTopOfViewController:(UIViewController *)viewController
                     sender:(UIView *)sender;

- (void)shareViaTwitter:(NSString *)text
               andImage:(UIImage *)image
                 andURL:(NSURL *)url
  onTopOfViewController:(UIViewController *)viewController
         withCompletion:(void(^)(BOOL result))completion;

- (void)shareViaTwitter:(NSString *)text
      andImageURLString:(NSString *)imageURLString
                 andURL:(NSURL *)url
  onTopOfViewController:(UIViewController *)viewController
         withCompletion:(void(^)(BOOL result))completion;

- (void)shareViaTwitter:(NSString *)text
      andImageURLString:(NSString *)imageURLString
                 andURL:(NSURL *)url
  onTopOfViewController:(UIViewController *)viewController;

/**
 Opens a facebook feed dialog.
 See http://developers.facebook.com/docs/reference/dialogs/feed/ for information about the parameters.
 @param message The initial message entered into the feed.
 @param link The link to the facebook feed.
 @param picture The path to the picture URL.
 @param source The source of the feed.
 @param name The title of the feed.
 @param caption The caption of the feed.
 @param description A description of the feed.
 @returns YES if succeeded opening the dialog or NO otherwise.
 */
- (void)shareViaFacebook:(NSString *)text
       andImageURLString:(NSString *)imageURLString
               andURLStr:(NSString *)urlStr
                 andName:(NSString *)name
              andCaption:(NSString *)caption
          andDescription:(NSString *)description
                      to:(NSString *)to;

/**
 Opens a facebook feed dialog.
 See http://developers.facebook.com/docs/reference/dialogs/feed/ for information about the parameters.
 @param message The initial message entered into the feed.
 @param link The link to the facebook feed.
 @param picture The path to the picture URL.
 @param source The source of the feed.
 @param name The title of the feed.
 @param caption The caption of the feed.
 @param description A description of the feed.
 @returns YES if succeeded opening the dialog or NO otherwise.
 */
- (void)shareViaFacebook:(NSString *)text
       andImageURLString:(NSString *)imageURLString
               andURLStr:(NSString *)urlStr
                 andName:(NSString *)name
              andCaption:(NSString *)caption
          andDescription:(NSString *)description;

/**
 Share via Email
 @param text - string representation of the share text
 @param subject - mail subject
 @param imageURLString - image url to be added to the mail
 @param stringURLString - URL link
 @param linkLabel - Text displayed for the link
 @param viewController - view controller to present upon
 */
- (void)shareViaEmail:(NSString *)text
           andSubject:(NSString *)subject
    andImageURLString:(NSString *)imageURLString
     andLinkURLString:(NSString *)linkUrlString
         andLinkLabel:(NSString *)linkLabel
onTopOfViewController:(UIViewController *)viewController;

/**
 Share via SMS
 @param body - string representation of the share text
 @param recipients - list of recipients
 @param viewController - view controller to present upon
 */
- (void)shareViaSMS:(NSString *)body
         andSubject:(NSArray *)recipients
onTopOfViewController:(UIViewController *)viewController;


/**
 Share on What'sApp (assuming it's installed)
 @discussion
 Using URL scheme built from this knowladge base:
 https://www.whatsapp.com/faq/iphone/23559013
 @param text - text to share
 @param linkURL - will be pasted after text
 */
- (void)shareViaWhatsAppWithText:(NSString *)text
                      andLinkURL:(NSURL *)linkURL;

/**
 Share with URL
 If not signed in - a sign in attempt will be tried - and upon success - sharing will occur
 @param url used for sharing - Image , text and description are taken from the link
 @param text to be filled in the user share portion
 */
- (void)shareViaGooglePlus:(NSString *)prefillText
                    andURL:(NSURL *)url;

/**
 Share On google plus with multiple fields
 Note - Fields will NOT override share data from URL. This is GooglePlus behaviour that cannot be changed
 If not signed in - a sign in attempt will be tried - and upon success - sharing will occur
 @param title - title of the GP share
 @param description - Description of the GPShare
 @param thumbnailURL - Thumbnail to be added
 @param url - URL to be shared
 @param text - to be filled in the user share portion
 */
- (void)shareViaGooglePlus:(NSString *)prefillText
                  andTitle:(NSString *)title
            andDescription:(NSString *)description
           andThumbnailURL:(NSURL *)thumbnailURL
                    andURL:(NSURL *)url;
@end
