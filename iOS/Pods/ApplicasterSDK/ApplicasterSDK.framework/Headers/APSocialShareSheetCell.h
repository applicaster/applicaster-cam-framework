//
//  APSocialShareSheetCell.h
//  applicaster
//
//  Created by Liviu Romascanu on 1/30/14.
//  Copyright (c) 2014 Applicaster Ltd. All rights reserved.
//

#import <UIKit/UIKit.h>

@interface APSocialShareSheetCell : UICollectionViewCell
/**
 Image used for the share option image
 */
@property (unsafe_unretained, nonatomic) IBOutlet UIImageView *imageView;

/**
 Text used for the share option name
 */
@property (unsafe_unretained, nonatomic) IBOutlet UILabel *shareMethodNameLabel;

@end
