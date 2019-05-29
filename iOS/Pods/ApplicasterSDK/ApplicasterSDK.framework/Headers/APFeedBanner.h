//
//  APGenericBanner.h
//  ApplicasterSDK
//
//  Created by Hagit Shemer on 6/8/14.
//  Copyright (c) 2014 Applicaster. All rights reserved.
//

typedef enum {
    APBannerKindNone = 0,
    APBannerKindLink,
    APBannerKindAd
} APBannerKind;

typedef enum {
    APBannerLocationNone = 0,
    APBannerLocationBottom,
    APBannerLocationInline,
    APBannerLocationSplash
} APBannerLocation;

@interface APFeedBanner : NSObject

//***** general banner properties **/

/** banner kind: Link/Ad */
@property (nonatomic, readonly) APBannerKind kind;
/** banner type: Bottom/Inline */
@property (nonatomic, readonly) APBannerLocation location;
/** time interval to push a new banner in seconds */
@property (nonatomic, readonly) NSTimeInterval interval;

//***** link banner properties **/

/** image URL string - for link banner */
@property (nonatomic, strong, readonly) NSString *imageUrlString;
/** web vew parameters (orientation, close button, navigation) - for link banner */
@property (nonatomic, strong, readonly) NSDictionary *linkWebViewParams;

//***** ad banner properties **/

/** ad unit ID - for ad banner */
@property (nonatomic, strong, readonly) NSString *adUnitID;


/**
 Init banner with dictionary recieved from server
 */
- (id)initWithDictionary:(NSDictionary *)dict;

@end
