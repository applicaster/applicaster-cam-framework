//
//  APSwitcherView.h
//  applicaster
//
//  Created by dan g / applicaster on 3/18/14.
//  Copyright (c) 2014 Applicaster Ltd. All rights reserved.
//

#import <UIKit/UIKit.h>

@class APSwitcherView;
@protocol APSwitcherViewDelegate <NSObject>

- (void)didSelectLeftButton:(APSwitcherView *)view;
- (void)didSelectRightButton:(APSwitcherView *)view;

@end

@interface APSwitcherView : UIView

@property (nonatomic, strong) UIImageView *triangle;
@property (nonatomic, strong) UIButton *rightSideBtn;
@property (nonatomic, strong) UIButton *leftSideBtn;
@property (nonatomic, strong) UIView *sliderView;
@property (nonatomic, assign) BOOL isSwitcher;
@property (nonatomic, strong) UIColor *colorOfTriangle;
@property (unsafe_unretained, nonatomic) id<APSwitcherViewDelegate>delegate;
@property (nonatomic, strong) UIView *separatorView;
@property (nonatomic, assign) BOOL hasSeparator;
@property (nonatomic, strong) UIColor *backgroundColorOfSwitcher;
@property (nonatomic, assign) BOOL isLineSlider; //slider style - line or full

- (void)rightPressed:(UIButton *)sender;
- (void)leftPressed:(UIButton *)sender;

@end
