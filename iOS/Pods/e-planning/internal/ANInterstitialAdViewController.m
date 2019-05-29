/*   Copyright 2013 APPNEXUS INC
 
 Licensed under the Apache License, Version 2.0 (the "License");
 you may not use this file except in compliance with the License.
 You may obtain a copy of the License at
 
 http://www.apache.org/licenses/LICENSE-2.0
 
 Unless required by applicable law or agreed to in writing, software
 distributed under the License is distributed on an "AS IS" BASIS,
 WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 See the License for the specific language governing permissions and
 limitations under the License.
 */

#import "ANInterstitialAdViewController.h"

#import "ANGlobal.h"
#import "ANLogging.h"
#import "UIView+ANCategory.h"
#import "UIWebView+ANCategory.h"

@interface ANInterstitialAdViewController ()
@property (nonatomic, readwrite, strong) NSTimer *progressTimer;
@property (nonatomic, readwrite, strong) NSDate *timerStartDate;
@property (nonatomic, readwrite, assign) BOOL viewed;
@property (nonatomic, readwrite, assign) BOOL originalHiddenState;
@property (nonatomic, readwrite, assign) UIInterfaceOrientation orientation;
@end

@implementation ANInterstitialAdViewController
@synthesize contentView = __contentView;
@synthesize backgroundColor = __backgroundColor;

- (id)init {
    NSBundle *resBundle = ANResourcesBundle();
    if (!resBundle) {
        ANLogError(@"Resource not found. Make sure the AppNexusSDKResources bundle is included in project");
        return nil;
    }
    self = [super initWithNibName:NSStringFromClass([self class]) bundle:resBundle];
    self.originalHiddenState = NO;
    self.orientation = [[UIApplication sharedApplication] statusBarOrientation];
    self.containerView = [UIView new];
    return self;
}

- (void)viewDidLoad {
    if (!self.backgroundColor) {
        self.backgroundColor = [UIColor whiteColor]; // Default white color, clear color background doesn't work with interstitial modal view
    }
    self.progressView.hidden = YES;
    self.closeButton.hidden = YES;
    CGRect containerFrame = adjustAbsoluteRectInWindowCoordinatesForOrientationGivenRect(self.view.frame);
    [self.containerView setFrame:containerFrame];
    [self.view insertSubview:self.containerView atIndex:0];
}

- (void)viewWillAppear:(BOOL)animated {
    [super viewWillAppear:animated];
    self.originalHiddenState = [UIApplication sharedApplication].statusBarHidden;
    [self setStatusBarHidden:YES];
    [self centerContentView];
}

- (void)viewDidAppear:(BOOL)animated {
    [super viewDidAppear:animated];
    if (!self.viewed && ([self.delegate closeDelayForController] > 0.0)) {
        [self startCountdownTimer];
        self.viewed = YES;
    } else {
        [self stopCountdownTimer];
    }
}

- (void)viewWillDisappear:(BOOL)animated {
    [super viewWillDisappear:animated];
    [self setStatusBarHidden:self.originalHiddenState];
    [self.progressTimer invalidate];
}

- (void)startCountdownTimer
{
    self.progressView.hidden = NO;
    self.closeButton.hidden = YES;
    self.timerStartDate = [NSDate date];
    self.progressTimer = [NSTimer scheduledTimerWithTimeInterval:0.01 target:self selector:@selector(progressTimerDidFire:) userInfo:nil repeats:YES];
}

- (void)stopCountdownTimer
{
	[self.progressTimer invalidate];
	[self.progressView setHidden:YES];
    [self.closeButton setHidden:NO];
    [self.view bringSubviewToFront:self.closeButton];
}

- (void)progressTimerDidFire:(NSTimer *)timer
{
	NSDate *timeNow = [NSDate date];
	NSTimeInterval timeShown = [timeNow timeIntervalSinceDate:self.timerStartDate];
    NSTimeInterval closeDelay = [self.delegate closeDelayForController];
	[self.progressView setProgress:(timeShown / closeDelay)];
    
	if (timeShown >= closeDelay && self.closeButton.hidden == YES) {
        [self stopCountdownTimer];
	}
}

- (void)willAnimateRotationToInterfaceOrientation:(UIInterfaceOrientation)interfaceOrientation duration:(NSTimeInterval)duration
{
	[UIView animateWithDuration:duration animations:^{
        [self centerContentView];
	}];
}

- (void)centerContentView {
    CGFloat contentWidth = self.contentView.frame.size.width;
    CGFloat contentHeight = self.contentView.frame.size.height;
    CGFloat centerX = (self.containerView.bounds.size.width - contentWidth) / 2;
    CGFloat centerY = (self.containerView.bounds.size.height - contentHeight) / 2;
    
	self.contentView.frame = CGRectMake(centerX, centerY, contentWidth, contentHeight);
}
/*
- (void)setContentView:(UIView *)contentView {
	if (contentView != __contentView) {
        if ([__contentView isKindOfClass:[UIWebView class]]) {
            UIWebView *webView = (UIWebView *)__contentView;
            [webView stopLoading];
            [webView setDelegate:nil];
        }

        [__contentView removeSubviews];
        [__contentView removeFromSuperview];
        [self.containerView removeSubviews];
        
        if (contentView != nil) {
            if ([contentView isKindOfClass:[UIWebView class]]) {
                UIWebView *webView = (UIWebView *)contentView;
                [webView removeDocumentPadding];
                [webView setMediaProperties];
            }
            
            [self.containerView addSubview:contentView];
        }
        
        __contentView = contentView;
    }
}
 */

- (void)setContentView:(UIView *)contentView {
    if (contentView != __contentView) {
        if ([__contentView isKindOfClass:[UIWebView class]]) {
            UIWebView *webView = (UIWebView *)__contentView;
            [webView stopLoading];
            [webView setDelegate:nil];
        }
        
        [__contentView removeFromSuperview];
        __contentView = contentView;
        
        [self.view insertSubview:__contentView
                    belowSubview:self.progressView];
        __contentView.translatesAutoresizingMaskIntoConstraints = NO;
        [__contentView an_constrainWithFrameSize];
        [__contentView an_alignToSuperviewWithXAttribute:NSLayoutAttributeCenterX
                                             yAttribute:NSLayoutAttributeCenterY];
    }
}

-(void)setBackgroundColor:(UIColor *)backgroundColor
{
    __backgroundColor = backgroundColor;
    self.view.backgroundColor = __backgroundColor;
    self.containerView.backgroundColor = __backgroundColor;
}

- (IBAction)closeAction:(id)sender
{
	[self.delegate interstitialAdViewControllerShouldDismiss:self];
}

// hiding the status bar in iOS 7
- (BOOL)prefersStatusBarHidden {
    return YES;
}

// hiding the status bar pre-iOS 7
- (void)setStatusBarHidden:(BOOL)hidden {
    [[UIApplication sharedApplication] setStatusBarHidden:hidden withAnimation:UIStatusBarAnimationNone];
}

// locking orientation in iOS 6+
- (BOOL)shouldAutorotate {
    return NO;
}

- (UIInterfaceOrientationMask)supportedInterfaceOrientations {
    switch (self.orientation) {
        case UIInterfaceOrientationLandscapeLeft:
            return UIInterfaceOrientationMaskLandscapeLeft;
        case UIInterfaceOrientationLandscapeRight:
            return UIInterfaceOrientationMaskLandscapeRight;
        case UIInterfaceOrientationPortraitUpsideDown:
            return UIInterfaceOrientationMaskPortraitUpsideDown;
        default:
            return UIInterfaceOrientationMaskPortrait;
    }
}

// locking orientation in pre-iOS 6
- (BOOL)shouldAutorotateToInterfaceOrientation:(UIInterfaceOrientation)interfaceOrientation {
    return NO;
}

@end

