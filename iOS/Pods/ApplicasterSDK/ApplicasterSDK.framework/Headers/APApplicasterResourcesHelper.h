//
//  APApplicasterResourcesHelper.h
//  ApplicasterSDK
//
//  Created by Anton Kononenko on 16/03/16.
//  Copyright © 2016 Applicaster Ltd. All rights reserved.
//

#import <Foundation/Foundation.h>

@interface APApplicasterResourcesHelper : NSObject

+ (NSBundle * __nonnull)bundle;
+ (NSBundle * __nullable)bundleWithNibName:(NSString * __nonnull)nibName;
+ (UIImage * __nullable)imageNamed:(NSString * __nonnull)imageName;
+ (UINib * __nullable)nibNamed:(NSString * __nonnull)nibName;
+ (UIView * __nullable)viewFromNibWithNibName:(NSString * __nonnull)nibName;

@end
