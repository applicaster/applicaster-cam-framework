//
//  APSocialActionView.h
//  ApplicasterSDK
//
//  Created by Liviu Romascanu on 7/2/12.
//  Copyright (c) 2012 Applicaster. All rights reserved.
//

#import <UIKit/UIKit.h>

@protocol APSocialActionViewDelegate <NSObject>

- (void)didSelectActionIndex:(NSInteger)index;

@end

@interface APSocialActionView : UIView <UITableViewDataSource , UITableViewDelegate>

@property (nonatomic, retain) NSArray *imageArray;
@property (nonatomic, retain) NSObject <APSocialActionViewDelegate> *delegate;
@property (strong, nonatomic) IBOutlet UITableView *actionsTable;
@property (unsafe_unretained, nonatomic) IBOutlet UIImageView *playerDropdownTopImageView;
@property (unsafe_unretained, nonatomic) IBOutlet UIImageView *playerDropdownMiddleImageView;
@property (unsafe_unretained, nonatomic) IBOutlet UIImageView *playerDropdownBottomImageView;

- (APSocialActionView *)initWithImageList:(NSArray *)array;

@end
