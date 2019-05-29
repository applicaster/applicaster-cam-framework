//
//  APApplicasterAdProvider.h
//  applicaster
//
//  Created by Guy Kogus on 23/01/12.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "APAdProvider.h"

extern NSString * const kAPImageURLStringKey;
extern NSString * const kAPWebViewParamsKey;

/**
 This ad provider supplies the Applicaster banners. It uses the account's advertiser to retrieve the appropriate banners.
 */
@interface APApplicasterAdProvider : APAdProvider

@end
