//
//  APTodayViewController.h
//  applicaster
//
//  Created by Liviu Romascanu on 9/7/14.
//  Copyright (c) 2014 Applicaster Ltd. All rights reserved.
//

#import <UIKit/UIKit.h>
@class APAccount, APModelCollection, APBroadcaster, APItemList;

@interface APTodayEPGVODViewController : UIViewController <UICollectionViewDataSource>
@property (strong, nonatomic) IBOutlet UICollectionView *comingUpCollection;
@property (strong, nonatomic) IBOutlet UICollectionView *primeTimeCollection;
@property (strong, nonatomic) IBOutlet UICollectionView *promotedVideosCollection;

@property (nonatomic, strong) APAccount *account;
@property (nonatomic, strong) APModelCollection *programs;
@property (nonatomic, strong) APBroadcaster *broadcaster;
@property (nonatomic, strong) APItemList *promotedItemList;


/**
 This must be overriden at the inherited instance level in order to properly communicate with the Applicaster server.
 For security reasons - please do NOT put this value in a PLIST or a header
 @return Applicaster API Secret Key
 */
- (NSString *)applicasterSecretKey;

- (void)setupApplicaster;

@end
