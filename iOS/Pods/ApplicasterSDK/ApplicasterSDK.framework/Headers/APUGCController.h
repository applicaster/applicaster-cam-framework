//
//  APUGCController.h
//  applicaster
//
//  Created by Guy Kogus on 10/05/12.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <UIKit/UIKit.h>

typedef NS_ENUM(NSUInteger, APUGCResult) {
	APUGCResultCancelled,
    APUGCResultSaved,
    APUGCResultSent,
    APUGCResultFailed
};

typedef NS_ENUM(NSUInteger, APUGCMediaType) {
	APUGCMediaTypeNone	= 0,
	APUGCMediaTypePhoto	= 1 << 0,
	APUGCMediaTypeVideo	= 1 << 1,
	APUGCMediaTypeBoth	= (APUGCMediaTypePhoto | APUGCMediaTypeVideo)
};

@class APUGCController;

/**
 The delegate is only responsible for displaying the action sheet that will be passed back to it. After that, the controller will handle the rest.
 */
@protocol APUGCControllerDelegate <NSObject>

@required
/**
 Informs the delegate that the controller has completed its task and can now be released.
 @param ugcController The controller that has completed its task.
 @param result A flag indicating the result of the UGC submission.
 */
- (void)ugcController:(APUGCController *)ugcController didFinishWithResult:(APUGCResult)result;

@optional

/**
 Allows the delegate to decide if the UGC controller should dismiss any view controllers / popover controllers that it has displayed.
 @param ugcController The controller that wishes to dismiss a view controller / popover controller.
 @param result A flag indicating the result of the UGC submission.
 @return YES if the UGC controller should dismiss view controllers, otherwise return NO.
 */
- (BOOL)shouldDismissUGCController:(APUGCController *)ugcController withResult:(APUGCResult)result;

/**
 The UGC will prepare an action sheet for its delegate to present.
 
 @discussion The action sheet's delegate will be the UGC Controller and can not be changed.
 
 @param ugcController The controller whose action sheet is ready to be displayed.
 @param actionSheet The action sheet to be displayed.
 */
- (void)ugcController:(APUGCController *)ugcController preparedActionSheet:(UIActionSheet *)actionSheet;

@end

/**
 The UGC controller is responsible for sending UGC content. It is sent a UGC message and offers the user a chance to add media content to the e-mail message that it will present.
 */
@interface APUGCController : NSObject

/**
 Returns a UGC Controller that will provide the delegate with an action sheet to present. The action sheet will provide the user the following option:
 1) Send an e-mail
 2) Select a picture/video then send an e-mail.
 3) Take a picture then send an e-mail.
 4) Take a video then send an e-mail.
 5) Cancel
 
 @param delegate The delegate responsible for displaying the action sheet. If no delegate is visible, the controller will attempt to show the action sheet on its own.
 @param recipient The recipient of the e-mail.
 @param subject The subject to place in the e-mail.
 @param message The HTML message that will appear in the final e-mail message.
 @param mediaType A bit-mask of the available media types, being photo/video/both/none.
 @return The new UGC Controller.
 */
+ (APUGCController *)ugcControllerWithDelegate:(id <APUGCControllerDelegate>)delegate
								emailRecipient:(NSString *)recipient
								  emailSubject:(NSString *)subject
								   htmlMessage:(NSString *)message
									 mediaType:(APUGCMediaType)mediaType;

/**
 Tells the UGC controller to show the action sheet.
 */
- (void)showUGCOptions;

/** The delegate responsible for displaying the action sheet. */
@property (nonatomic, unsafe_unretained) id <APUGCControllerDelegate>delegate;
/** The HTML message that will appear in the final e-mail message. */
@property (nonatomic, copy) NSString *emailMessage;
/** The recipient of the e-mail. */
@property (nonatomic, copy) NSString *emailRecipient;
/** The subject to place in the e-mail. */
@property (nonatomic, copy) NSString *emailSubject;
/** A bit-mask of the available source types, being photo/video/both/none. */
@property (nonatomic, assign) APUGCMediaType mediaType;

@end
