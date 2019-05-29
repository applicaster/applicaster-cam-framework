//
//  CREPGCollectionViewCell.h
//  Caracol
//
//  Created by dan g / applicaster on 7/23/13.
//  Copyright (c) 2013 Applicaster. All rights reserved.
//

@interface APEPGCollectionViewCell : UICollectionViewCell <UICollectionViewDataSource, UICollectionViewDelegate>

@property (weak ,nonatomic) IBOutlet UICollectionView *collectionViewVerical;
@property (nonatomic, copy, readonly) NSArray *programs;

/**
 Set nib from application rather than the APPlicasterUIKIt
 */
+ (void)setCustomNibForProgram:(NSString *)customNib;

/**
 *  Set line spacing in collection view flow layout
 *
 *  @param lineSpacing - The new line spacing in collection view flow layout.
 */
+ (void)setProgramsLineSpacing:(CGFloat)lineSpacing;

/**
 *  Set section insets for the collection view flow layout
 *
 *  @param sectionInsets - The new section inset for the collection view flow layout.
 */
+ (void)setSectionInsets:(UIEdgeInsets)sectionInsets;

/**
 
 */
- (void)setData:(NSArray *)programs;
- (void)setItemsWidth:(CGFloat)width;
- (void)scrollCollectionToTop;

@end
