//
//  APComposeViewController.h
//  ApplicasterSDK
//
//  Created by Anton Kononenko on 12/24/14.
//  Copyright (c) 2014 Applicaster. All rights reserved.
//

#import <Social/Social.h>

@interface APComposeViewController : SLComposeViewController

+ (APComposeViewController *)composeViewControllerForServiceType:(NSString *)serviceType;

@end
