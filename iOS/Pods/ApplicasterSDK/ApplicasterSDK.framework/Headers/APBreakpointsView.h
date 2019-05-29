//
//  APBreakpointsView.h
//  ModularAppSDK
//
//  Created by user on 03/02/2016.
//  Copyright © 2016 Applicaster. All rights reserved.
//

#import <UIKit/UIKit.h>
/* this class is define new control that contains points that is displayed by breakpoints array per duration*/

@interface APBreakpointsView : UIView

- (void)setDuration:(NSInteger)duration;
- (void)setBreakpointsArray:(NSArray *)array;

//setter and getter to break point image
- (void)setBreakpointImage:(UIImage *)image;
- (UIImage *)breakpointImage;

- (void)setUnselectedBreakpointAtIndex:(NSInteger)index;
- (void)setSelectedBreakpointAtIndex:(NSInteger)index;

@end
