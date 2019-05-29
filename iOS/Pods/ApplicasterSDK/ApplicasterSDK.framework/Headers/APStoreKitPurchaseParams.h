//
//  APStoreKitPurchaseParams.h
//  applicaster
//
//  Created by Tom Susel on 12/13/10.
//  Copyright 2010 __MyCompanyName__. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "APModel.h"

@interface APStoreKitPurchaseParams : APModel {

}

@property (nonatomic, strong, readonly) NSString *voucherDomainID;
@property (nonatomic, strong, readonly) NSString *voucherDomainType;

@end
