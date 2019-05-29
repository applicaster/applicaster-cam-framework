//
//  APJavaScriptListener.h
//  ApplicasterSDK
//
//  Created by Liviu Romascanu on 1/24/12.
//  Copyright (c) 2012 Applicaster. All rights reserved.
//

#import <Foundation/Foundation.h>

/**
 APJavascript Listener Delegate protocol
 */
@protocol APJavaScriptListenerDelegate <NSObject>

/**
 Handle passed on Javascript callback string command and with info inside a dictionary
 @param command string
 @param dictionary containing the javascript fields
 */
- (void)handleJavaScriptCallWithCommand:(NSString *)command andDictionary:(NSDictionary *)dictionary;

@end

/**
 APJavaScript Listener object:
 Initialized with a URL , holds a web view and waits for javascript calls.
 If such happen - they are parsed into dictionaries and passed to the delegate (if set).
 */
@interface APJavaScriptListener : NSObject <UIWebViewDelegate> {
    UIWebView                           *_webView;
    NSString                            *_scheme;
}

/**
 Web view used for the javascript 
 */
@property (nonatomic, retain) UIWebView *webView;

/**
 Delegate - able of handling Javascript calls parsed to dictionary
 */
@property (nonatomic, assign) id <APJavaScriptListenerDelegate> delegate;

/**
 Optional Webview delegate that forwards the current webview delegate calls
 */
@property (nonatomic, assign) id<UIWebViewDelegate> webViewDelegate;


/**
 schema to catch commands on
 */
@property (nonatomic, copy) NSString *scheme;

/**
 Initialize with a URL
 @param url adress for the javascript html.
 @param string to find the calls schema
 @return APJavaScriptListener
 */
- (id)initWithURL:(NSURL *)url andString:(NSString *)string;

/**
 Initialize with a URL and an existing web view.
 Note that the created APJavaScriptListener sets itself as the webview delegate - after it sets the current delegate as its own webViewDelegate.
 It will then continue passing it the webView delegate calls.
 @param url adress for the javascript html.
 @param string to find the calls schema
 @param web view
 @return APJavaScriptListener
 */
- (id)initWithURL:(NSURL *)url andString:(NSString *)string andWebView:(UIWebView *)webView;

@end
