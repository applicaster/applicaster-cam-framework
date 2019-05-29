//
//  APSNStatusManager.h
//  Applicaster
//
//  Created by Hagit Shemer on 1/30/14.
//  Copyright (c) 2014 Applicaster. All rights reserved.
//

extern NSString * const APSNStatusChangedNotification;

typedef enum
{
    APSNStatusLoggedinUndefined = -1,
    APSNStatusLoggedinNone      = 0,
    APSNStatusLoggedinTwitter   = (1 << 0), // => 00000001
    APSNStatusLoggedinFacebook  = (1 << 1)  // => 00000010
} APSNStatusMask;


@interface APSNStatusManager : NSObject

+ (APSNStatusManager *)sharedInstance;

@property (nonatomic, readonly) APSNStatusMask statusMask;

@end
