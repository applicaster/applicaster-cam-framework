//
//  APBannerManager.h
//  applicaster
//
//  Created by Irit Yablon on 7/12/11.
//  Copyright 2011 Applicaster. All rights reserved.
//

#import <Foundation/Foundation.h>

#import <UIKit/UIKit.h>

/**
 Defines banner size
 */
typedef enum{
    APBannerManagerPortraitIphone,
    APBannerManagerLandscapeIphone,
    APBannerManagerPortraitIpad,
    APBannerManagerLandscapeIpad,
}APBannerManagerSizeType;

#define kPortraitSizeIphone CGSizeMake(320.0,50.0)
#define kPortraitSizeIpad CGSizeMake(766.0,66.0)
#define kLandscapeSizeIphone CGSizeMake(480.0,32.0)
#define kLandscapeSizeIpad CGSizeMake(1024.0,66.0)
#define kTimeToUpdateBanner 30.0

/**
 * Each third party banner should implement this protocol
 */
@protocol ThirdPartyBannerProtocol 

/**
 * Set the banner size
 * If the banner does NOT SUPPORT the given size it should return nil
 * @param sizetype the new size
 * @return the banner view in the desired size
 */
-(UIView <ThirdPartyBannerProtocol> *)setBannerSizeType:(APBannerManagerSizeType)sizetype;
//-(APBannerManagerSizeType)sizeType;
-(APBannerManagerSizeType)sizeType;


@end

//Banner notification will be posted with NSDictionary in the following cases:
//1. banner is ready to use: key-banner value-UIView
//2. banner failed: key-banner value-nil
//3. banner started an action: key-action value-@"start"
//4. banner ended an action: key-action value-@"finish"
//5. a local banner clicked should open a category: key-category value-NSString categoryID
extern NSString * const kAPBannerManagerNotification;

/**
 The APBannerManager class manages banner ads in their entirety.
 */
@interface APBannerManager : NSObject {
    
    UIView *_banner;
    
    NSTimeInterval _duration;
    
    CGFloat _frequency;
    
    APBannerManagerSizeType _sizeType;
    
   // NSString *_moblinZonePortrait;
   // NSString *_moblinZoneLandscape;
    UIInterfaceOrientation _orientation;
    UIView <ThirdPartyBannerProtocol> *_thirdPartyBannerView;

}

/**
 The banner view.
 */
@property (nonatomic, strong) UIView *banner;


@property (nonatomic, strong) UIView  <ThirdPartyBannerProtocol> *thirdPartyBannerView;

/**
 The size of the banner. This is dependent on the device type (iPhone/iPad) and the orientation (landscape/portrait).
 */
@property (nonatomic, assign) APBannerManagerSizeType sizeType;
//@property (nonatomic, copy) NSString *moblinZonePortrait;
//@property (nonatomic, copy) NSString *moblinZoneLandscape;

-(BOOL)isReady;

/**
 * The third party banner should call this method when banner is clicked
 * and start some kind of action (so the banner manager will stop pause video if needed
 */
-(void)thirdPartyBannerDidStartAction;

/**
 * The third party banner should call this method when banner activity is finished
 * so the banner manager will continue / start video if needed
 */

-(void)thirdPartyBannerDidFinishAction;

-(void)thirdPartyBannerFailed;

-(void)thirdPartyBannerIsReady:(UIView *)bannerView;

@end
