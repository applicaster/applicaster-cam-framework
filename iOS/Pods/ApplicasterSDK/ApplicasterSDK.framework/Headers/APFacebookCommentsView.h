//
//  APFacebookCommentsView.h
//  ApplicasterSDK
//
//  Created by Liviu Romascanu on 10/10/12.
//  Copyright (c) 2012 Applicaster. All rights reserved.
//

#import <UIKit/UIKit.h>

@class APFacebookCommentsFilter;

@protocol APFacebookCommentsViewDelegate <NSObject>

- (void)postOnPublicPageWithCompletionHandler:(void (^)(BOOL error))handler andMessage:(NSString *)message;
- (void)filterFriends:(BOOL)filter;

@end

@interface APFacebookCommentsView : UIView <UITextViewDelegate>

@property (nonatomic, assign) CGFloat standardWidth;

@property (unsafe_unretained, nonatomic) IBOutlet UITableView *postsTable;
@property (unsafe_unretained, nonatomic) IBOutlet UILabel *publicPageNameLabel;
@property (unsafe_unretained, nonatomic) IBOutlet UIActivityIndicatorView *loader;
@property (unsafe_unretained, nonatomic) IBOutlet UIButton *closeCommentsViewButton;
// This property is only available on iPhone for hiding the post view during commenting.
@property (unsafe_unretained, nonatomic) IBOutlet UIView *postContainerView;
@property (unsafe_unretained, nonatomic) IBOutlet UIButton *postButton;
@property (unsafe_unretained, nonatomic) IBOutlet UITextView *postTextView;
@property (unsafe_unretained, nonatomic) IBOutlet UIImageView *postBackgroundImageView;
@property (unsafe_unretained, nonatomic) IBOutlet UIButton *friendsFilter;
@property (readonly, nonatomic) APFacebookCommentsFilter *commentsFilterView;
@property (unsafe_unretained, nonatomic) id<APFacebookCommentsViewDelegate> delegate;

- (IBAction)closeButtonClicked:(id)sender;
- (IBAction)postButtonClicked:(id)sender;
- (IBAction)friendsFilterClicked:(id)sender;

- (BOOL)commentsShowing;
- (void)showComments;
- (void)hideComments;

// Used on iPhone only.
- (void)showPosts;
- (void)hidePosts;

@end
