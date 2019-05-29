//
//  APACScoreNotificationView.h
//  applicaster
//
//  Created by Miri on 8/2/14.
//  Copyright (c) 2014 Applicaster Ltd. All rights reserved.
//

#import <UIKit/UIKit.h>

@interface APACScoreNotificationView : UIView

/*
 ScoreLabel - score label.
 */
@property (nonatomic,weak) IBOutlet UILabel *scoreLabel;

/*
 PlusLabel - plus icon label.
 */
@property (nonatomic,weak) IBOutlet UILabel *plusLabel;

/*
 ActionNameLabel - action name label.
 */
@property (nonatomic,weak) IBOutlet UILabel *actionNameLabel;

@end
