//
//  APActionsViewController.h
//  applicaster
//
//  Created by Miri on 7/19/14.
//  Copyright (c) 2014 Applicaster Ltd. All rights reserved.
//

#import <UIKit/UIKit.h>

@interface APACActionsViewController : UIViewController <UICollectionViewDataSource,UICollectionViewDelegate,UICollectionViewDelegateFlowLayout>

/*
 ActionsCollectionView - actions collection view.
 */
@property (nonatomic, weak) IBOutlet UICollectionView *actionsCollectionView;

/*
 TitleLabel - title label.
 */
@property (nonatomic, weak) IBOutlet UILabel *titleLabel;

/*
 DescriptionLabel - description label.
 */
@property (nonatomic, weak) IBOutlet UILabel *descriptionLabel;

/*
 BgImageView - background imageView.
 */
@property (nonatomic, weak) IBOutlet UIImageView *bgImageView;

/*
 LineTitleView - under line title view.
 */
@property (nonatomic, weak) IBOutlet UIView *lineTitleView;

/*
 Top container view.
 */
@property (nonatomic, weak) IBOutlet UIView *topContainerView;

/*
 ActionsArray - array of visible actions.
 */
@property (nonatomic, strong) NSArray *actionsArray;

/*
 Close action screen.
 */
- (IBAction)closeButtonTapped:(id)sender;

@end
