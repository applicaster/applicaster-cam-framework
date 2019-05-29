/*
 This file is part of APRater.
 
 Copyright (c) 2010, Arash Payan
 All rights reserved.
 
 Permission is hereby granted, free of charge, to any person
 obtaining a copy of this software and associated documentation
 files (the "Software"), to deal in the Software without
 restriction, including without limitation the rights to use,
 copy, modify, merge, publish, distribute, sublicense, and/or sell
 copies of the Software, and to permit persons to whom the
 Software is furnished to do so, subject to the following
 conditions:
 
 The above copyright notice and this permission notice shall be
 included in all copies or substantial portions of the Software.
 
 THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
 EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES
 OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
 NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT
 HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY,
 WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
 FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR
 OTHER DEALINGS IN THE SOFTWARE.
 */
/*
 * APRater.h
 * APRater
 *
 * Created by Arash Payan on 9/5/09.
 * http://arashpayan.com
 * Copyright 2010 Arash Payan. All rights reserved.
 */

#import <Foundation/Foundation.h>
#import <UIKit/UIKit.h>

extern NSString *const kAPRaterFirstUseDate;
extern NSString *const kAPRaterUseCount;
extern NSString *const kAPRaterSignificantEventCount;
extern NSString *const kAPRaterCurrentVersion;
extern NSString *const kAPRaterRatedCurrentVersion;
extern NSString *const kAPRaterDeclinedToRate;

/*
 Place your Apple generated software id here.
 */
#define APRater_APP_ID				301377083

/*
 Your app's name.
 */
#define APRater_APP_NAME				[[[NSBundle mainBundle] infoDictionary] objectForKey:@"CFBundleDisplayName"]

/*
 This is the message your users will see once they've passed the day+launches
 threshold.
 */
#define APRater_MESSAGE				[NSString stringWithFormat:@"If you enjoy using %@, would you mind taking a moment to rate it? It won't take more than a minute. Thanks for your support!", APRater_APP_NAME]

/*
 This is the title of the message alert that users will see.
 */
#define APRater_MESSAGE_TITLE			[NSString stringWithFormat:@"Rate %@", APRater_APP_NAME]

/*
 The text of the button that rejects reviewing the app.
 */
#define APRater_CANCEL_BUTTON			@"No, Thanks"

/*
 Text of button that will send user to app review page.
 */
#define APRater_RATE_BUTTON			[NSString stringWithFormat:@"Rate %@", APRater_APP_NAME]

/*
 Text for button to remind the user to review later.
 */
#define APRater_RATE_LATER			@"Remind me later"

/*
 Users will need to have the same version of your app installed for this many
 days before they will be prompted to rate it.
 */
#define APRater_DAYS_UNTIL_PROMPT		10		// double

/*
 An example of a 'use' would be if the user launched the app. Bringing the app
 into the foreground (on devices that support it) would also be considered
 a 'use'. You tell APRater about these events using the two methods:
 [APRater appLaunched:]
 [APRater appEnteredForeground:]
 
 Users need to 'use' the same version of the app this many times before
 before they will be prompted to rate it.
 */
#define APRater_USES_UNTIL_PROMPT		20		// integer

/*
 A significant event can be anything you want to be in your app. In a
 telephone app, a significant event might be placing or receiving a call.
 In a game, it might be beating a level or a boss. This is just another
 layer of filtering that can be used to make sure that only the most
 loyal of your users are being prompted to rate you on the app store.
 If you leave this at a value of -1, then this won't be a criteria
 used for rating. To tell APRater that the user has performed
 a significant event, call the method:
 [APRater userDidSignificantEvent:];
 */
#define APRater_SIG_EVENTS_UNTIL_PROMPT	-1	// integer

/*
 Once the rating alert is presented to the user, they might select
 'Remind me later'. This value specifies how long (in days) APRater
 will wait before reminding them.
 */
#define APRater_TIME_BEFORE_REMINDING		1	// double

/*
 'YES' will show the APRater alert everytime. Useful for testing how your message
 looks and making sure the link to your app's review page works.
 */
#define APRater_DEBUG				NO

@interface APRater : NSObject <UIAlertViewDelegate> {
    
	UIAlertView		*ratingAlert;
    NSInteger       _days;
    NSInteger       _activations;
    NSString        *_appleID;    
}

@property(nonatomic, retain) UIAlertView *ratingAlert;
@property (nonatomic, assign) NSInteger days;
@property (nonatomic, assign) NSInteger activations;
@property (nonatomic, retain) NSString *appleID;

/*
 DEPRECATED: While still functional, it's better to use
 appLaunched:(BOOL)canPromptForRating instead.
 
 Calls [APRater appLaunched:YES]. See appLaunched: for details of functionality.
 */
+ (void)appLaunched;

/*
 Tells APRater that the app has launched, and on devices that do NOT
 support multitasking, the 'uses' count will be incremented. You should
 call this method at the end of your application delegate's
 application:didFinishLaunchingWithOptions: method.
 
 If the app has been used enough to be rated (and enough significant events),
 you can suppress the rating alert
 by passing NO for canPromptForRating. The rating alert will simply be postponed
 until it is called again with YES for canPromptForRating. The rating alert
 can also be triggered by appEnteredForeground: and userDidSignificantEvent:
 (as long as you pass YES for canPromptForRating in those methods).
 */
+ (void)appLaunched:(BOOL)canPromptForRating;

/*
 Same as the above but providing necessery data to be self contained after application load
 */

+ (void)appLaunched:(BOOL)canPromptForRating withAppleID:(NSString *)appleID andNumberOfDays:(NSInteger)days andNumberOfActivations:(NSInteger)activations;

/*
 Tells APRater that the app was brought to the foreground on multitasking
 devices. You should call this method from the application delegate's
 applicationWillEnterForeground: method.
 
 If the app has been used enough to be rated (and enough significant events),
 you can suppress the rating alert
 by passing NO for canPromptForRating. The rating alert will simply be postponed
 until it is called again with YES for canPromptForRating. The rating alert
 can also be triggered by appLaunched: and userDidSignificantEvent:
 (as long as you pass YES for canPromptForRating in those methods).
 */
+ (void)appEnteredForeground:(BOOL)canPromptForRating;

/*
 Tells APRater that the user performed a significant event. A significant
 event is whatever you want it to be. If you're app is used to make VoIP
 calls, then you might want to call this method whenever the user places
 a call. If it's a game, you might want to call this whenever the user
 beats a level boss.
 
 If the user has performed enough significant events and used the app enough,
 you can suppress the rating alert by passing NO for canPromptForRating. The
 rating alert will simply be postponed until it is called again with YES for
 canPromptForRating. The rating alert can also be triggered by appLaunched:
 and appEnteredForeground: (as long as you pass YES for canPromptForRating
 in those methods).
 */
+ (void)userDidSignificantEvent:(BOOL)canPromptForRating;

/*
 Tells APRater to open the App Store page where the user can specify a
 rating for the app. Also records the fact that this has happened, so the
 user won't be prompted again to rate the app.
 
 The only case where you should call this directly is if your app has an
 explicit "Rate this app" command somewhere.  In all other cases, don't worry
 about calling this -- instead, just call the other functions listed above,
 and let APRater handle the bookkeeping of deciding when to ask the user
 whether to rate the app.
 */
+ (void)rateApp;

@end