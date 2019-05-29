//
//  UIAlertView+APAdditions.h
//  ApplicasterSDK
//
//  Created by Guy Kogus on 21/02/12.
//  Copyright (c) 2012 Applicaster. All rights reserved.
//

#import <UIKit/UIKit.h>

/**
 Helper category for showing a basic UIAlertView
 */
@interface UIAlertView (APAdditions)

/**
 Shows the most basic of UIAlertViews.
 @param title The string that appears in the receiver’s title bar.
 @param message Descriptive text that provides more details than the title.
 @param cancelButtonTitle The title of the cancel button or nil if there is no cancel button.
 */
+ (void)showAlertWithTitle:(NSString *)title
				   message:(NSString *)message
		 cancelButtonTitle:(NSString *)cancelButtonTitle;

@end
