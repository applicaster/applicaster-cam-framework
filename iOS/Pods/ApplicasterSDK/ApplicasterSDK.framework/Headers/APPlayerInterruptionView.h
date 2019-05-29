//
//  APPlayerInterruptionView.h
//  applicaster
//
//  Created by Tom Susel on 2/2/12.
//  Copyright (c) 2012 Applicaster. All rights reserved.
//

#import <UIKit/UIKit.h>

#import "APPlayerInterruptionViewProtocol.h"
#import "APModel.h"

@class APItemList;
/**
 A view that is presented when the player is interrupted.
 This is the default view used by the <code>APPlayerController</code>.
 */
@interface APPlayerInterruptionView : UIView <APModelObserver, UICollectionViewDelegate, UICollectionViewDataSource,APPlayerInterruptionViewProtocol>

@property (nonatomic, strong) IBOutlet UICollectionView *collectionView;
@property (nonatomic, strong) IBOutlet UIView *buttonsContainerView;
@property (nonatomic, strong) IBOutlet UIView *promotedItemsView;
@property (nonatomic, strong) IBOutlet UIView *captureButtonsContainerView;
@property (nonatomic, strong) APItemList *promotedItems;

+ (void)setPromotedVODItemCellImageName:(NSString *)imageName;

@end

/**
 A view with the old interruption view name.
 Used for bckward compatibility.
 */
@interface APBackgroundVideoView : APPlayerInterruptionView
@end
