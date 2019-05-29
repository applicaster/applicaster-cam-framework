//
//  APPlayerAudioOnlyView.h
//  ApplicasterSDK
//
//  Created by Tom Susel on 1/22/12.
//  Copyright (c) 2012 Applicaster. All rights reserved.
//

#import <UIKit/UIKit.h>

@interface APPlayerAudioOnlyView : UIView

/**
 The message label.
 Use this handle to localize the message.
 */
@property (strong, nonatomic) IBOutlet UILabel *messageLabel;

/**
 Creates and returns an initizlized audio only view.
 After initializing the instance, the method would localize the message.
 */
+ (id)audioOnlyView;

@end
