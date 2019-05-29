//
//  APCallbackHandler+JavaScript.h
//  applicaster
//
//  Created by Guy Kogus on 7/08/12.
//
//

#import "APCallbackHandler.h"

@interface APCallbackHandler (JavaScript)

+ (NSString *)javaScriptCallbackFunctionWithName:(NSString *)callbackName parameterValue:(id)value;
+ (NSString *)javaScriptCallbackFunctionWithName:(NSString *)callbackName parameters:(NSDictionary *)parameters;

@end
