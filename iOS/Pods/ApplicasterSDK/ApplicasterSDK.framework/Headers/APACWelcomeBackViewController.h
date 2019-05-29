//
//  APACWelcomeBackViewController.h
//  applicaster
//
//  Created by Miri on 7/29/14.
//  Copyright (c) 2014 Applicaster Ltd. All rights reserved.
//

#import <UIKit/UIKit.h>

@interface APACWelcomeBackViewController : UIViewController

/*
 TitleLabel - welcome back title.
 */
@property (nonatomic, weak) IBOutlet UILabel *titleLabel;

/*
 LineTitleView - title under line view.
 */
@property (nonatomic, weak) IBOutlet UIView *lineTitleView;

/*
 SubTitleLabel - sub title label.
 */
@property (nonatomic, weak) IBOutlet UILabel *subTitleLabel;

/*
 DescriptionLabel - description label.
 */
@property (nonatomic, weak) IBOutlet UILabel *descriptionLabel;

/*
 ScoreLabel - score label.
 */
@property (nonatomic, weak) IBOutlet UILabel *scoreLabel;

/*
 WheelImageView - wheel image view.
 */
@property (nonatomic, weak) IBOutlet UIImageView *wheelImageView;

/*
 MarkerImageView - marker image view.
 */
@property (nonatomic, weak) IBOutlet UIImageView *markerImageView;

@end
