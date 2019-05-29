//
//  APUnhittableView.h
//  ApplicasterSDK
//
//  Created by Guy Kogus on 17/07/12.
//  Copyright (c) 2012 Applicaster. All rights reserved.
//

#import <UIKit/UIKit.h>

/**
 This type of view will never return itself in a hittest, regardless of its state. This is extremely useful for container views.
 */
@interface APUnhittableView : UIView

@end
