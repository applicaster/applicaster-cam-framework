//
//  CREPGProgramCell.h
//  Caracol
//
//  Created by dan g / applicaster on 7/28/13.
//  Copyright (c) 2013 Applicaster. All rights reserved.
//

@class APImageView, APProgram;

@interface APEPGProgramCell : UICollectionViewCell

@property (weak, nonatomic) IBOutlet APImageView *aImage;
@property (weak, nonatomic) IBOutlet UILabel *aNameLbl;
@property (weak, nonatomic) IBOutlet UILabel *aDescriptionLbl;
@property (weak, nonatomic) IBOutlet UILabel *aTimeLbl;
@property (weak, nonatomic) IBOutlet UIButton *reminderBtn;
@property (strong, nonatomic) APProgram *program;

- (void)setCellWithProgram:(APProgram *)program;
- (void)updateReminderButton;
- (void)reminderBtnPressed;
@end
