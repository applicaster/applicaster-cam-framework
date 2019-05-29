  //
//  APNativePlayerViewController.h
//  applicaster
//
//  Created by Hagit Shemer on 9/15/13.
//  Copyright (c) 2013 Applicaster Ltd. All rights reserved.
//

@interface APNativePlayerViewController : MPMoviePlayerViewController

@property (nonatomic, strong) UIView *overly;
@property (nonatomic, strong) UIImageView *imageLoading;
@property (nonatomic, strong) UIActivityIndicatorView *spinner;

- (id)initWithContentURL:(NSURL *)url andOverly:(UIView *)overlay;

@end
