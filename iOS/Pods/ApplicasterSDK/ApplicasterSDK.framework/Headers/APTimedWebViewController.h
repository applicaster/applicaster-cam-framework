//
//  APTimedWebViewController.h
//  applicaster
//
//  Created by Liviu Romascanu on 1/29/12.
//  Copyright (c) 2012 none. All rights reserved.
//

#import <UIKit/UIKit.h>

@class APTimedWebVCCallbackHandler;
@class APTimedWebView;
@protocol APTimedWebViewControllerDelegate;

#define kAPTimedWebViewDefaultExposureTime 6.0

extern NSString *const APTimedWebViewControllerOrientationKey;
extern NSString *const APTimedWebViewControllerCloseButtonKey;
extern NSString *const APTimedWebViewControllerControlsKey;
extern NSString *const APTimedWebViewControllerFullScreenKey;
extern NSString *const APTimedWebViewControllerEnableZoomKey;
extern NSString *const APTimedWebViewControllerMediaPlaybackRequiersUserActionKey;
extern NSString *const APTimedWebViewControllerOpenExternalKey;
extern NSString *const APTimedWebViewControllerURLKey;
extern NSString *const APTimedWebViewControllerExposureTimeKey;
extern NSString *const APTimedWebViewControllerTransitionKey;

/**
 Links starting with this prefix would be opened externally (i.e. safari).
 The external prefix will be removed and then opened externally if possible.
 */
#define kAPTimedWebViewExternalWebPrefix @"external:"

/**
 Posted when the view controller is dismissed.
 */
extern NSString * const APTimedWebViewControllerWillDismissNotification;

/**
 Posted when the web view finished loading.
 */
extern NSString * const APTimedWebViewControllerWebViewDidLoadNotification;

/**
 Posted when the web view fails to load.
 */
extern NSString * const APTimedWebViewControllerWebViewFailedLoadNotification;

@protocol APTimedWebViewControlelrInnerWebViewController

@required
- (void)openRequest:(NSURLRequest*)request;

@end

/**
 This is a standard web view controller that is displayed modally.
 */
@interface APTimedWebViewController : UIViewController <UIWebViewDelegate>{
	//UI
	IBOutlet UIButton                       *_closeButton;
	IBOutlet UIActivityIndicatorView        *spinner;
	
	//Logic
	BOOL                                    _shouldLoadURL;
	BOOL                                    _shouldAutoDismiss;
	BOOL                                    _isWebViewLoaded;
	BOOL                                    _didWebViewLoadFail;
    BOOL                                    _isLoading;
	NSUInteger                              _loadCount;
	double                                  _exposureTime;
    IBOutlet UIButton                       *_nextButton;
    IBOutlet UIButton                       *_prevButton;
    
    NSDictionary                            *_params;
    
    id <APTimedWebViewControllerDelegate>   __unsafe_unretained _delegate;
    
    APTimedWebVCCallbackHandler             *_handler;
}

@property (nonatomic, readonly) APTimedWebView *webView;


@property (nonatomic, strong) void (^dismissHandler)(APTimedWebViewController *webViewController);

/**
 urlPath The urlPath that will be loaded or is loaded in the webView
 */
@property (nonatomic, readonly) NSURL *urlPath;

/**
 BOOL value that returns YES if webview is loaded.
 Note - Web View is considered loaded once it finished loading the first page and is ready to display / displaying.
 */
@property (nonatomic, readonly) BOOL isWebViewLoaded;

/**
 BOOL value that returns YES if webview did fail loading
 */
@property (nonatomic, readonly) BOOL didWebViewLoadFail;

/**
 BOOL value that is webview is currently loading
 */
@property (nonatomic, readonly) BOOL isLoading;

/**
 Close button
 */
@property (nonatomic, strong) UIButton *closeButton;

/**
 Initialization params used by initWithParams
 */
@property (nonatomic, strong) NSDictionary *params;

/**
 This allows for setting the close button image. Only sizing and positioning can not be changed.
 */
@property (nonatomic, strong) UIImage *closeButtonImage;

/**
 Use this property to set whether or not to show the Forward and Back buttons. Default value is YES.
 */
@property (nonatomic, assign) BOOL showNavigationControls;


/**
 This bitmask defines the allowed interface orientations. See <UIInterfaceOrientations> for the interface orientations that can be combined using the C bitwise OR operation.
 */
@property (nonatomic, assign) UIInterfaceOrientationMask allowedInterfaceOrientations;

/**
 The <APPreloadViewControllerDelegate> is responsible for handling the end of the preload.
 */
@property (nonatomic, unsafe_unretained) id<APTimedWebViewControllerDelegate> delegate;

/**
 The loading spinner.
 */
@property (nonatomic, strong) UIActivityIndicatorView *spinner;

/**
 Callback handler to listen to close events
 */
@property (nonatomic, strong)APTimedWebVCCallbackHandler *listener;

/**
 External URL to open after dismiss
 */
@property (nonatomic, readonly, strong) NSURL *externalURLAfterDismiss;

/**
 initialize with URL for infinite exposure time
 @param url Target URL address to load.
 @return APTimedViewController
 */
- (id)initWithURL:(NSURL *)url;


/**
 initialize with URL and set exposure time
 @param url Target URL address to load.
 @param exposureTime Exposure time - double. 0 for infinite.
 @return APTimedViewController
 */
- (id)initWithURL:(NSURL *)url exposureTime:(double)exposureTime;

/**
 Initialize with a Params Dictionary
 @param params A dictionary of parameters using the predefined keys.
 @return APTimedViewController
 */
- (id)initWithDictionary:(NSDictionary *)params;

/**
 Initialize with an HTML string. The string will be loaded straight away, so there will be no need to call <loadTargetURL>.
 
 @param htmlString The HTML string to load into the web view.
 @return A new APTimedWebViewController instance.
 */
- (id)initWithHTMLString:(NSString *)htmlString;

/**
 Returns an autoreleased timed web view controller.
 @param url Target URL address to load.
 @param exposureTime Exposure time - double. 0 for infinite.
 @return The new web view controller.
 */
+ (id)timedWebViewControllerForURL:(NSURL *)url exposureTime:(double)exposureTime;

/**
 Returns the exposure time.
 By default value is <code>kAPTimedWebViewDefaultExposureTime</code>.
 By default this is the minimum time that would pass between viewDidAppear and the dismissal of the view controller.
 @return The exposure time.
 */
- (double)exposureTime;

/**
 Dismisses the view when tapped.
 */
- (IBAction)closeButtonTapped;

/**
 Dismisses this view controller.
 Wither dismisses modal or pops from navigation accordingly.
 */
- (void)dismissViewController;

-(IBAction)webViewGoBack;
-(IBAction)webViewGoForward;

- (void)loadTargetURL;

- (void)stringByEvaluatingJavaScriptFromString:(NSString *)string;

@end
