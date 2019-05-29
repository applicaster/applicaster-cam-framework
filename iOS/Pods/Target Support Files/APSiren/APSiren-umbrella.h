#ifdef __OBJC__
#import <UIKit/UIKit.h>
#else
#ifndef FOUNDATION_EXPORT
#if defined(__cplusplus)
#define FOUNDATION_EXPORT extern "C"
#else
#define FOUNDATION_EXPORT extern
#endif
#endif
#endif

#import "APSirenParser.h"
#import "APSirenFactory.h"
#import "NSArray+APSirenAdditions.h"
#import "NSDictionary+APSirenAdditions.h"
#import "NSObject+APSirenAdditions.h"
#import "APSirenParserLoadingManager.h"
#import "APSirenEntity.h"
#import "APSirenLinkEntity.h"

FOUNDATION_EXPORT double APSirenVersionNumber;
FOUNDATION_EXPORT const unsigned char APSirenVersionString[];

