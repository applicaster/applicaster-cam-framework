//
//  APAchievementCustomization.h
//  applicaster
//
//  Created by dan g / applicaster on 1/27/14.
//  Copyright (c) 2014 Applicaster Ltd. All rights reserved.
//

#import <Foundation/Foundation.h>

/*
 Currently the customization taken from the feed , in the future will be a separate API for Achievement center
 */
typedef NS_ENUM (NSInteger, APAchievementThemeColor){
    APAchievementThemeColorMain = 0,
    APAchievementThemeColorSecondary,
    APAchievementThemeColorBackground,
    APAchievementThemeMainColorText,
    APAchievementThemeColorSecondaryText
} ;

@interface APAchievementCustomization : NSObject

@property (nonatomic, strong) NSDictionary *colors;
@property (nonatomic, strong) NSDictionary *defualtColors;
@property (nonatomic, strong) NSString *timelineID;

extern NSString *const kRefreshCustomizationOfAchievement;

/*
 Init theme with timeLineId of feed. (Only now - until to be a separate api of achievement)
 */
- (id)initWithTimelineID:(NSString *)timelineID;

/*
 Get theme color
 **/
- (UIColor *)getColor:(APAchievementThemeColor)themeColor;

/*
 Fetch new customization colors and asset from server
 **/
- (void)refreshCustomization:(BOOL)isDemo;

@end
