//
//  APTodayFeedEpisodeStatusViewController.h
//  applicaster
//
//  Created by Liviu Romascanu on 9/18/14.
//  Copyright (c) 2014 Applicaster Ltd. All rights reserved.
//

#import <UIKit/UIKit.h>
#import "APTodayFeedEpisodeStatusApplicasterDataProvider.h"

/**
 Applicaster Feed Status Today extension widget.

 @discussion
 Integration instructions:
 1. Create a new widget.
 2. Link it with Applicaster SDK just like the app itself is linked + Add the Applicaster SDK bundle / APTodayFeedEpisodeStatusViewController.xib + takeover_sync_button.png + @2x
 3. Today extension must inherit APTodayFeedEpisodeStatusViewController and implement APFeedEpisodeStatusApplicasterDataProvider
 4. In the extensions info.plist Replace in the NSExtension - storyboard value with NSExtensionPrincipalClass = TodayViewController (or your inheriting view controller class
 5. Implement the protocol methods
 6. Override the init method:
    -(instancetype)init
    {
        return [super initWithNibName:@"APTodayFeedEpisodeStatusViewController" bundle:nil];
    }
 */
@interface APTodayFeedEpisodeStatusViewController : UIViewController <APTodayFeedEpisodeStatusApplicasterDataProvider>

/**
 Feed launch button - transparent button covering the entire widget while the feed episode is live
 */
@property (strong, nonatomic) IBOutlet UIButton *feedLaunchButton;

/**
 Feed information message label - Appears when the button is not visible
 */
@property (strong, nonatomic) IBOutlet UILabel *feedMessageLabel;

/**
 Feed sync animation image view - currently - the image inside it is rotated constantly when an episode is live
 */
@property (strong, nonatomic) IBOutlet UIImageView *feedSyncAnimationImageView;

/**
 Call to action label - showed when the Feed is live
 */
@property (strong, nonatomic) IBOutlet UILabel *feedCallToActionLabel;

/**
 View containing all the subviews that need to be shown when the episode is live
 */
@property (strong, nonatomic) IBOutlet UIView *launchAppView;

/**
 Information view - containing all subviews that need to be shown when loading , future episode or errors are shown.
 The openTheApp button is also showed
 */
@property (strong, nonatomic) IBOutlet UIView *informationView;

/**
 Add reminder button - currently not displayed - this functionality is not yet decided since the straight forward scenario is not possible in a widget
 */
@property (strong, nonatomic) IBOutlet UIButton *addReminderButton;

/**
 Open the app button - can be used with a provided icon
 */
@property (strong, nonatomic) IBOutlet UIButton *openTheAppButton;

- (void)updateApplicaster;
- (IBAction)feedLaunchButtonClicked:(id)sender;
- (IBAction)openAppButtonClicked:(id)sender;
- (IBAction)addReminderButtonClicked:(id)sender;

@end
