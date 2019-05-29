//
//  APVoucher.h
//  applicaster
//
//  Created by Guy Kogus on 5/01/12.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//

#import "APModel.h"

extern NSString *const APVoucherDomainTypeApp;
extern NSString *const APVoucherDomainTypeCategory;
extern NSString *const APVoucherTypePermanent;
extern NSString *const APVoucherTypeSubscription;

@interface APVoucher : APModel

@property (nonatomic, strong, readonly) NSString *type;
@property (nonatomic, strong, readonly) NSDate *expiresAt;
@property (nonatomic, strong, readonly) NSString *purchasedItemID;
@property (nonatomic, strong, readonly) NSString *voucherTemplateID;
@property (nonatomic, strong, readonly) NSString *voucherDomainType;
@property (nonatomic, strong, readonly) NSString *voucherDomainID;
@property (nonatomic, readonly) BOOL isAutoRenewable;

@end
