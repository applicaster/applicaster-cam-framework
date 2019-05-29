//
//  CREPGDayViewCell.h
//  Caracol
//
//  Created by dan g / applicaster on 7/28/13.
//  Copyright (c) 2013 Applicaster. All rights reserved.
//

@class APEPGDay;
@interface APEPGDayViewCell : UICollectionViewCell

@property (weak, nonatomic) IBOutlet UILabel *upperLbl; //day of the week
@property (weak, nonatomic) IBOutlet UILabel *downLbl; //date

/**
 Cell size
 */
+ (CGSize)cellSize;

/**
 Create string from date and fill up the APEPGDay obj
 */
- (void)setData:(APEPGDay *)day;

@end
