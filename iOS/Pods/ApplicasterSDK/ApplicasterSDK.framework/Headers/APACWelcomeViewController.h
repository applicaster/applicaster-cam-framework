//
//  APACWelcomeView.h
//  applicaster
//
//  Created by Miri on 7/21/14.
//  Copyright (c) 2014 Applicaster Ltd. All rights reserved.
//

#import <UIKit/UIKit.h>
#import "APImageVIew.h"

@interface APACWelcomeViewController : UIViewController

/*
 Get start button.
 */
@property (nonatomic, weak) IBOutlet APImageView *backgroundImageView;

/*
 Get start button.
 */
@property (nonatomic, weak) IBOutlet UIButton *getStartBtn;

/*
 Login to facebook button.
 */
@property (nonatomic, weak) IBOutlet UIButton *loginFBBtn;

@end
