//
//  APDefaultPlayerLoadingView.h
//  applicaster
//
//  Created by Tom Susel on 1/18/12.
//  Copyright (c) 2012 Applicaster. All rights reserved.
//
#import "APLoadingView.h"

@interface APDefaultPlayerLoadingView : UIView <APLoadingView>{
    UIActivityIndicatorView *_activityIndicator;
    UILabel                 *_messageLabel;
}

@end
