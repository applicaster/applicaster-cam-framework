//
//  APGradientView.h
//  Applicaster Core
//
//  Created by Liviu Romascanu on 5/17/12.
//  Copyright (c) 2012 none. All rights reserved.
//

#import <UIKit/UIKit.h>

typedef enum{
	APGradientViewHorizontal, // Gradient from left to right.
	APGradientViewVertical // Gradient from top to bottom.
} APGradientViewOrientation;

/**
 APGradientView is a view that can be created with a start and end UIColors
 On the rectDraw - a linear top to bottom gradient is created as the background
 */
@interface APGradientView : UIView

//
/**
 Gradient Start Color.
 MUST be RGB color. Set it like this: gradientView.startColor = [UIColor colorWithRGBAHexString:@"00000000"];
 */
@property (nonatomic, retain) UIColor *startColor;

/**
 Gradient End Color
 MUST be RGB color. Set it like this: gradientView.startColor = [UIColor colorWithRGBAHexString:@"00000000"];
 */
@property (nonatomic, retain) UIColor *endColor;

/**
 CGGradient created from the colors
 Changed each time the start / end color are set
 */
@property (nonatomic, assign) CGGradientRef gradient;
/**
 The orientation of the gradient, default is APGradientViewVertical.
 */
@property (nonatomic, assign) APGradientViewOrientation orientation;

/**
 Initialize a new APGradientView
 @param frame The rect for the view
 @param startColor Color to start from
 @param endColor Color to end with
 @return UIView with gradient background
 */
- (id)initWithFrame:(CGRect)frame andStartColor:(UIColor *)startColor andEndColor:(UIColor *)endColor;

/**
 Initialize a new APGradientView
 @param frame The rect for the view
 @param startColor Color to start from
 @param endColor Color to end with
 @param orientation The orientation of the gradient
 @return UIView with gradient background
 */
- (id)initWithFrame:(CGRect)frame andStartColor:(UIColor *)startColor andEndColor:(UIColor *)endColor andOrientation:(APGradientViewOrientation)orientation;

@end
