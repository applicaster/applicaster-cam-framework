//
//  APACActionViewCell.h
//  applicaster
//
//  Created by Miri on 7/19/14.
//  Copyright (c) 2014 Applicaster Ltd. All rights reserved.
//

#import <UIKit/UIKit.h>
#import "APImageView.h"

extern NSString *const kAPACActionViewCell;

@interface APACActionViewCell : UICollectionViewCell

/*
 ActionImage - image of action.
 */
@property (nonatomic, weak) IBOutlet APImageView *actionImage;

/*
 ActionTitle - title of action.
 */
@property (nonatomic, weak) IBOutlet UILabel *actionTitle;

/*
 ActionScore - score of action.
 */
@property (nonatomic, weak) IBOutlet UILabel *actionScore;

/*
 maxLabel - "max" label.
 */
@property (nonatomic, weak) IBOutlet UILabel *maxLabel;

/*
 PlusLabel - plus icon label.
 */
@property (nonatomic, weak) IBOutlet UILabel *plusLabel;

/*
 ActionsData - actions dictionary.
 */
@property (nonatomic, weak) NSDictionary *actionsData;

@end
