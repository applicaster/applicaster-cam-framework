//
//  APLocalBanner.h
//  applicaster
//
//  Created by Irit Yablon on 6/5/11.
//  Copyright 2011 Applicaster. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "APModel.h"
#import "APBannerManager.h"

@class APCategory;
@class APItemList;
@class APButton;
@class APLocalBannerView;
@class APApplicasterController;

@protocol APLocalBannerViewDelegate <NSObject>

@required

-(void)apBannerViewIsReady:(UIView *)bannerView;
-(void)apBannerViewDidFailed:(UIView *)bannerView;


@optional

-(void)apBannerViewCloseButtonTapped:(UIView *)bannerView;
-(void)apBannerView:(UIView *)bannerView wasTappedWithURL:(NSString *)stringURL andCategory:(APCategory *)category;
-(void)apBannerView:(UIView *)bannerView wasTappedWithCategoryID:(NSString *)categoryID;

@end



@interface APLocalBannerView : UIView <APModelObserver>{
    
    id<APLocalBannerViewDelegate> __unsafe_unretained _delegate;
    
    APButton *_localBannerButton;
    
    APButton *_localBannerButtonLandscape;

        
    NSMutableArray *_localBannerCategoriesPortrait;
    NSMutableArray *_localBannerCategoriesLandscape;
    
    NSInteger _localBannnersIndexPortrait;
    NSInteger _localBannersIndexLandscape;
    
    APItemList *_bannersItemList;
    
    UIButton *_closeButton;
    
    CGFloat _refreshBannerTime;
    
    APBannerManagerSizeType _sizeType;
    
    NSString *_bannerImagePortrait;
    NSString *_bannerImageLandscape;
    
    APApplicasterController *_applicaster;
    
    NSString *_broadcasterId;
    
    APButton *_exposureButtonLink;
}

@property (nonatomic, unsafe_unretained) id delegate;
@property (nonatomic, strong) APButton *localBannerButton;
@property (nonatomic, strong) APButton *localBannerButtonLandscape;
@property (nonatomic, assign) CGFloat refreshBannerTime;
@property (nonatomic, assign) APBannerManagerSizeType sizeType;


/**
 * Constructor
 * @param frame of the view that the banner in goint to be displayed in
 * @param bannerType the size type of the banner
 * @param broadcasterID the unique id of the used broadcaster
 * @return APBannerView object
 */
-(id)initWithFrame:(CGRect)frame sizeType:(APBannerManagerSizeType)bannerType;

/**
 *Return the id of the banner's category which is currently displayed
 */
-(NSString *)getCurrentCategoryId;

/**
 *Return the name of the banner's category which is currently displayed
 */
-(NSString *)getCurrentCategoryName;

-(void) stopBannerTransformation;

-(void) startBannerTransformation;

@end
