//
//  APCMCustomization.h
//  applicaster
//
//  Created by Miri Vecselboim on 13/10/13.
//  Copyright (c) 2013 Applicaster Ltd. All rights reserved.
//

#import <Foundation/Foundation.h>

@interface APCMCustomization : NSObject

/**
 Get custom CrossMates plist.
 */
+ (NSMutableDictionary *)customCMPlistDict;

/**
 Get custom Class name of APCMViewController.
 */
+ (NSString *)CMViewControllerClassName;

/**
 Get custom Class name of APCMCharacterSelectionViewController.
 */
+ (NSString *)APCMCharacterSelectionViewControllerClassName;

/**
 Get custom Class name of APCMCharacterSelectionCollectionViewCell.
 */
+ (NSString *)APCMCharacterSelectionCollectionViewCellClassName;

/**
 Get custom Class name of APCMSingleCharacterViewController.
 */
+ (NSString *)APCMSingleCharacterViewControllerClassName;

/**
 Get custom Class name of APCMCharacterSelectionCarouselCell.
 */
+ (NSString *)APCMCharacterSelectionCarouselCellClassName;

/**
 Get custom Class name of APCMInboxCharacterViewCell.
 */
+ (NSString *)APCMInboxCharacterViewCellClassName;

/**
 Get custom Class name of APCMAlertViewController.
 */
+ (NSString *)APCMAlertViewControllerClassName;

/**
 Get custom Class name of APCMEventsCollectionViewController.
 */
+ (NSString *)APCMEventsCollectionViewControllerClassName;

/**
 Get custom Class name of APCMEventMessageViewCell.
 */
+ (NSString *)APCMEventMessageViewCellClassName;

/**
 Get custom Class name of APCMEventImageViewCell.
 */
+ (NSString *)APCMEventImageViewCellClassName;

/**
 Get custom Class name of APCMEventImageViewCell.
 */
+ (NSString *)APCMEventVideoViewCellClassName;

/**
 Get custom Class name of APCMImageFullScreenCollectionView.
 */
+ (NSString *)APCMImageFullScreenCollectionViewClassName;

/**
 Get custom Class name of APCMImageFullScreenCollectionViewcell.
 */
+ (NSString *)APCMImageFullScreenCollectionViewcellClassName;

/**
 Get custom Class name of APCMEventQuestionViewCell.
 */
+ (NSString *)APCMEventQuestionViewCellClassName;

/**
 Get custom Class name of APCMEventAnswerViewCell.
 */
+ (NSString *)APCMEventAnswerViewCellClassName;

/**
 Get name of APCMVideoLoadingImage.
 */
+ (NSString *)APCMVideoLoadingImageName;

/**
 Nav bar customization name
 */
+ (NSString *)APCMNavBarViewClassName;

/**
 Video sharing bar
 */
+ (NSString *)APCMVideoSharing;

/**
 show navigation back button 
 */
+ (BOOL)APCMHideBackButtonInFirstPage;

@end
