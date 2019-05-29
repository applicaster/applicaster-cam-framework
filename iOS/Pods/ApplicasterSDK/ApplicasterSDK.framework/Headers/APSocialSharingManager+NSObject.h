//
//  APSocialSharingManager+NSObject.h
//  applicaster
//
//  Created by Yael Buchman on 11/30/14.
//  Copyright (c) 2014 Applicaster Ltd. All rights reserved.
//

#import "APSocialSharingManager.h"

typedef enum {
    APSharingViaFacebookType,
    APSharingViaTwitterType,
    APSharingViaMailType,
    APSharingViaGooglePlusType,
    APSharingViaWhatsAppType,
    APSharingViaSMSType,
    APSharingViaNativeType
}   APSharingType;

@interface APSocialSharingManager (NSObject)
/**
 Share on all sharingType options with default text
 @param model - which model should be shared (each one has its own method)
 @param sharingType - on which sharing type we want to share the model (like facebook, twitter etc.)
 */
- (void)shareWithDefaultTextWithModel:(id)model
                       andSharingType:(APSharingType)sharingType;

/**
 Share on all sharingType options with default text
 @param model - which model should be shared (each one has its own method)
 @param sharingType - on which sharing type we want to share the model (like facebook, twitter etc.)
 @param sender - View instance that send this action
 */
- (void)shareWithDefaultTextWithModel:(id)model
                       andSharingType:(APSharingType)sharingType
                               sender:(UIView *)sender;
@end
