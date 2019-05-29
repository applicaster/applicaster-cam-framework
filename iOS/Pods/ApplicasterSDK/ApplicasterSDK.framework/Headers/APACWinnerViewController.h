//
//  APACWinnerViewController.h
//  applicaster
//
//  Created by Miri on 8/4/14.
//  Copyright (c) 2014 Applicaster Ltd. All rights reserved.
//

#import <UIKit/UIKit.h>

/*
 Currently the winner screen does'nt appear, in the future it will open by push
 */

@interface APACWinnerViewController : UIViewController

/*
 WinnerPopupView - winner popup view.
 */
@property (nonatomic, weak) IBOutlet UIView *winnerPopupView;

/*
 CongratulationsLabel - congratulations label.
 */
@property (nonatomic, weak) IBOutlet UILabel *congratulationsLabel;

/*
 CongratulationsUnderLineView - congratulations under line view.
 */
@property (nonatomic, weak) IBOutlet UIView *congratulationsUnderLineView;

/*
 WinnerNameLabel - winner name label.
 */
@property (nonatomic, weak) IBOutlet UILabel *winnerNameLabel;

/*
 UnderLineWinnerNameView - under line view of winner name.
 */
@property (nonatomic, weak) IBOutlet UIView *underLineWinnerNameView;

/*
 YouWonLabel - "You won" label.
 */
@property (nonatomic, weak) IBOutlet UILabel *youWonLabel;

/*
 RankLabel - rank label.
 */
@property (nonatomic, weak) IBOutlet UILabel *rankLabel;

/*
 CollectPrizeButton - collect prize button.
 */
@property (nonatomic, weak) IBOutlet UIButton *collectPrizeButton;

/*
 CloseButton - close button.
 */
@property (nonatomic, weak) IBOutlet UIButton *closeButton;

/*
 bgImageView - background imageView.
 */
@property (nonatomic, weak) IBOutlet UIImageView *bgImageView;

/*
 Collect prize - open support mail.
 */
-(IBAction)collectPrizeButtonPress:(id)sender;

/*
 Close the winner screen.
 */
-(IBAction)closeButtonPress:(id)sender;

@end
