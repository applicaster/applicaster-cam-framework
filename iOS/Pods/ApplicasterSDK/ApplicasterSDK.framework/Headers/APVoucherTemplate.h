//
//  APVoucherTemplate.h
//  applicaster
//
//  Created by Guy Kogus on 5/01/12.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//

#import "APModel.h"

@interface APVoucherTemplate : APModel {
	
}

@property (nonatomic, strong, readonly) NSString *name;
@property (nonatomic, strong, readonly) NSString *productIdentifier;
@property (nonatomic, strong, readonly) NSString *productType;
@property (nonatomic, strong, readonly) NSString *associatedClassType;
@property (nonatomic, readonly) BOOL isAutoRenewable;

/**
 Deprecated
 */
- (void)load;
@end

@interface APPermanentVoucherTemplate : APVoucherTemplate

@end

@interface APSkSubscriptionVoucherTemplate : APVoucherTemplate

@end

@interface APDailyTrialVoucherTemplate : APVoucherTemplate

@end
