//
//  APBackgroundPromotedDTCell.h
//  applicaster
//
//  Created by Irit Yablon on 11/17/11.
//  Copyright (c) 2011 Applicaster. All rights reserved.
//

#import <UIKit/UIKit.h>

@class APVodItem;
@class APImageView;

@interface APBackgroundPromotedDTCell : UICollectionViewCell
@property (nonatomic, strong) IBOutlet UILabel        *titleLabel;
@property (nonatomic, strong) IBOutlet UILabel        *descriptionLabel;
@property (nonatomic, strong) IBOutlet UIImageView    *freeStripImageView;
@property (nonatomic, strong) IBOutlet APImageView    *imageView;

-(void)setItem:(APVodItem *)item withImageName:(NSString *)imageName atIndex:(NSInteger)index;

@end
