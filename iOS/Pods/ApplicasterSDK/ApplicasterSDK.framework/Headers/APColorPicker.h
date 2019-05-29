//
//  APColorPicker.h
//  APColorPicker
//
//  Created by Guy Kogus on 3/6/09.
//  Copyright 2009 Applicaster Ltd. All rights reserved.
//

#import <Foundation/Foundation.h>

@interface APColorPicker : NSObject

+ (UIColor*)getPixelColorAtLocation:(CGPoint)point forImage:(UIImage *)image;

@end
