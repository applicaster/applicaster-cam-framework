//
//  APTimedWebView.h
//  applicaster
//
//  Created by Guy Kogus on 27/06/12.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//

#import <UIKit/UIKit.h>

@class APTimedWebView;

/**
 A protocol for informing the delegate when the web view is tapped.
 */
@protocol APTimedWebViewDelegate <NSObject>

/**
 Called when the web view's <hitTest:withEvent> method was called.
 */
- (void)webViewDidWasHit:(APTimedWebView *)webView;

@end

@interface APTimedWebView : UIWebView

@property(nonatomic,unsafe_unretained) id<APTimedWebViewDelegate> hitDelegate;

@end
