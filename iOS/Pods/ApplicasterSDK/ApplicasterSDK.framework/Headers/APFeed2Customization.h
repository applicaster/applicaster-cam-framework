//
//  APFeed2Customization.h
//  applicaster
//
//  Created by dan g / applicaster on 1/27/14.
//  Copyright (c) 2014 Applicaster Ltd. All rights reserved.
//

#import <Foundation/Foundation.h>

typedef enum {
    APFeed2ThemeColorMain = 0,
    APFeed2ThemeColorSecondary = 1,
    APFeed2ThemeColorBackground = 2,
    APFeed2ThemeColorMainText = 3,
    APFeed2ThemeColorSecondaryText = 4
} APFeed2ThemeColor;


@interface APFeed2Customization : NSObject

@property (nonatomic, strong) NSMutableDictionary *icons;
@property (nonatomic, strong) NSMutableDictionary *images;
@property (nonatomic, strong) NSDictionary *colours;
@property (nonatomic, strong) NSDictionary *defualtColors;
@property (nonatomic, strong) NSString *timelineID;

extern NSString *const kRefreshCustomizationOfFeed2;

- (id)initWithTimelineID:(NSString *)timelineID;

/*
 Get theme color
 **/
- (UIColor *)getColor:(APFeed2ThemeColor)themeColor;

/**
 Crop the image event according the mask image.
 */
+ (UIImage*)getCropped:(UIImage *)image withMask:(UIImage *)maskImage;

/**
 Tint the image event according the selected color.
 */
+ (UIImage *)imageWithTint:(UIColor *)tintColor andImageName:(NSString *)imageName;

/*
 Get a Name of the asset which required and return the url of the asset which client has set in the star api
 **/
- (NSURL *)getAssetByName:(NSString *)name;

/*
 Fetch new customization colors and asset from server
 **/
- (void)refreshCustomization:(BOOL)isDemo;


/*
 Background image
 **/
- (NSURL *)getBgImg;

/*
 Get a letter and retun a UIColor object with the correct colour and make it darker
 @discusion A,B,C,D,E,F,G are letters which symobolize an object which can be customize.
 @param darkEffectLevel - float that simbolized the level of dark eefect for instance: 0.3 means 30%
 **/
- (UIColor *)getColor:(APFeed2ThemeColor)themeColor darkEffectLevel:(float)level;
- (UIColor *)getColor:(APFeed2ThemeColor)themeColor hasWhiteEffect:(BOOL)hasWhiteEffect;

@end
