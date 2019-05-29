
#import <Foundation/Foundation.h>
#import "APAdProvider.h"
 
extern NSString *const kAPEPAdSizeKey;
extern NSString *const kAPEPAdPlacementKey;

@interface APEPAdProvider : APAdProvider

+ (instancetype)providerWithPlatformId:(NSString *)platformId;

@end
