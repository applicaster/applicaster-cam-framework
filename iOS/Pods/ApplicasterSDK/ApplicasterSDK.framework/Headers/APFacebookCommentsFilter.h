//
//  APFacebookCommentsFilter.h
//  ApplicasterSDK
//
//  Created by Miri Vecselboim on 11/11/12.
//  Copyright (c) 2012 Applicaster. All rights reserved.
//

#import <Foundation/Foundation.h>

@protocol APFacebookCommentsFilterDelegate <NSObject>

-(void)filterChangedToFriends:(BOOL)_friends;

@end


@interface APFacebookCommentsFilter : UIView <UIScrollViewDelegate>

@property (nonatomic, retain) IBOutlet UIButton *publicButton;
@property (nonatomic, retain) IBOutlet UIButton *friendsOnlyButton;
@property (nonatomic, retain) IBOutlet UIImageView *selectionImage;
@property (nonatomic, assign) id delegate;

-(IBAction)publicButtonTapped;
-(IBAction)friendsOnlyButtonTapped;

-(void)showFilterView:(BOOL)show;
-(BOOL)filterViewIsVisible;

@end
