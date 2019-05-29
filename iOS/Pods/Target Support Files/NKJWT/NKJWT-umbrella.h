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

#import "NKJWT.h"
#import "NSString+NKJWTBase64.h"
#import "NSString+NKJWTHmacSha256.h"

FOUNDATION_EXPORT double NKJWTVersionNumber;
FOUNDATION_EXPORT const unsigned char NKJWTVersionString[];

