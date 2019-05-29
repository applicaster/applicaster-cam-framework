//
//  APFacebookCreatePost.h
//  ApplicasterSDK
//
//  Created by Shimon Shvartsbroit on 8/14/13.
//  Copyright (c) 2013 Shimon Shvartsbroit. All rights reserved.
//

#import <UIKit/UIKit.h>

@class APFacebookPostObject;

// Protocol
@protocol APFacebookCreatePostDelegate

@required
-(void)postText:(NSString*)aText forPost:(APFacebookPostObject*)aPost;

@end

// Enum
typedef enum
{
    APFacebookCreatePostTypeComment = 0,
    APFacebookCreatePostTypePost = 1,
} APFacebookCreatePostType;

// Class
@interface APFacebookCreatePostViewController : UIViewController <UITextViewDelegate>

@property (unsafe_unretained, nonatomic) IBOutlet UILabel *instructionsLabel;
@property (assign, nonatomic)   id <APFacebookCreatePostDelegate>   delegate;
@property (unsafe_unretained, nonatomic) IBOutlet UILabel *placeholderLabel;
@property (unsafe_unretained, nonatomic) IBOutlet UIButton *postButton;
@property (unsafe_unretained, nonatomic) IBOutlet UITextView *contentTextView;

@property (nonatomic, strong) APFacebookPostObject* post; //TODO: make private and define feed navigation protocol

- (IBAction)postTapped:(id)sender;

- (id)initWithType:(APFacebookCreatePostType)type forPost:(APFacebookPostObject*)aPost;
- (id)initWithType:(APFacebookCreatePostType)type forPost:(APFacebookPostObject*)aPost andNibName:(NSString*)nibName andBundle:(NSBundle*)bundle;


@end
