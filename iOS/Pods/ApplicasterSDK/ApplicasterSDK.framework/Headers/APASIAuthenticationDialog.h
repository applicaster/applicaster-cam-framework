//
//  ASIAuthenticationDialog.h
//  Part of ASIHTTPRequest -> http://allseeing-i.com/ASIHTTPRequest
//
//  Created by Ben Copsey on 21/08/2009.
//  Copyright 2009 All-Seeing Interactive. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <UIKit/UIKit.h>
@class APASIHTTPRequest;

typedef enum _APASIAuthenticationType {
	APASIStandardAuthenticationType = 0,
    APASIProxyAuthenticationType = 1
} APASIAuthenticationType;

@interface APASIAutorotatingViewController : UIViewController
@end

@interface APASIAuthenticationDialog : APASIAutorotatingViewController <UIActionSheetDelegate, UITableViewDelegate, UITableViewDataSource> {
	APASIHTTPRequest *request;
	APASIAuthenticationType type;
	UITableView *tableView;
	UIViewController *presentingController;
	BOOL didEnableRotationNotifications;
}
+ (void)presentAuthenticationDialogForRequest:(APASIHTTPRequest *)request;
+ (void)dismiss;

@property (strong) APASIHTTPRequest *request;
@property (assign) APASIAuthenticationType type;
@property (assign) BOOL didEnableRotationNotifications;
@property (strong, nonatomic) UIViewController *presentingController;
@end
