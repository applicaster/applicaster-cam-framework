//
//  APBannerSizes.h
//  ApplicasterSDK
//
//  Created by Guy Kogus on 29/01/12.
//  Copyright (c) 2012 Applicaster. All rights reserved.
//

#import <UIKit/UIKit.h>


// These are the sizes as defined by iAds.
static inline CGSize APBannerSizeForOrientation(UIInterfaceOrientation orientation) {
	CGSize size;
	
	if (UIInterfaceOrientationIsLandscape(orientation)) {
		if (IS_IPAD()) {
			size = CGSizeMake(1024.0, 66.0);;
		} else {
			size = CGSizeMake(480.0, 32.0);
		}
	} else {
		if (IS_IPAD()) {
			size = CGSizeMake(768.0, 66.0);;
		} else {
			size = CGSizeMake(320.0, 50.0);;
		}
	}
	
	return size;
}
