//
//  APTimedWebViewControllerDelegate.h
//  applicaster
//
//  Created by Liviu Romascanu on 2/7/12.
//  Copyright (c) 2012 none. All rights reserved.
//

#import <Foundation/Foundation.h>

@class APTimedWebViewController;

/**
 The delegate is responsible for handling all the responses of of a web view's loading and appearance/disappearance.
 There is also the option to handle UGC submission using the <timedWebViewController:shouldSubmitHTMLMessage:> callback.
 */
@protocol APTimedWebViewControllerDelegate <NSObject>

@optional
/**
 This callback method indicates when the webview content has finished loading. Some times we want to wait until all content is loaded before displaying, while others may want to show a loading screen.
 
 Note - this will only be called the first time the web page finished loading.
 @param timedVC The <APTimedWebViewController> that has finished loading its content.
 */
- (void)timedWebViewControllerDidFinishLoadingContent:(APTimedWebViewController *)timedVC;

/**
 This callback method indicates when the webview content has failed loading. This method is called when the last request fails (web view may contain serverl requests). 
 Note - Webview maybe loaded partly but last request declares failure.  
 @param timedVC The <APTimedWebViewController> that has failed loading its content.
 */
- (void)timedWebViewControllerDidFailedLoadingContent:(APTimedWebViewController *)timedVC;

/**
 This callback allows delegates to be passed information from online forms, and to decide if they will take over the form submission or allow the website to handle it itself.
 
 @param timedVC The <APTimedWebViewController> whose web view is submitting a form.
 @param message The evaluated value of calling the JavaScript function getFormValues()
 @return YES if the web view should continue processing the form submission, NO if the delegate wishes for the view controller to be dismissed.
 */
- (BOOL)timedWebViewController:(APTimedWebViewController *)timedVC shouldSubmitHTMLMessage:(NSString *)message;

/**
 This method is called when the timed webviewcontroller did appear.
 This can be used to determin when it was dismissed
 @param timedVC The <APTimedWebViewController> that has finished the appearing animation.
 */
- (void)timedWebViewDidAppear:(APTimedWebViewController *)timedVC;

/**
 This method is called when the timed webviewcontroller did Disappear.
 This can be used to determin when it was dismissed
 @param timedVC The <APTimedWebViewController> that has finished the disappearing animation.
 */
- (void)timedWebViewDidDisappear:(APTimedWebViewController *)timedVC;

/**
 This method is called when the timed webviewcontroller wants to open external url.
 Implement this method to overwrite the defualt implementation.
 @param timedVC The <APTimedWebViewController> that want to open the external url.
 @param url     The url that the webview wants to open extenally
 */
- (void)timedWebViewController:(APTimedWebViewController *)timedVC openExternalURL:(NSURL *)url;

/**
 This method is called when the preload content has finished viewing.
 
 There are 3 reasons for this method to be called:<p>
 - An image has displayed for 6 seconds.<p>
 - A video has finished playing.<p>
 - The web page preload has been dismissed.<p>
 This will also be called if any of the preload content types failed to load.
 @param timedVC The <APTimedWebViewController> that has finished displaying its content.
 */
- (void)timedWebViewControllerFinished:(APTimedWebViewController *)timedVC;

@end
