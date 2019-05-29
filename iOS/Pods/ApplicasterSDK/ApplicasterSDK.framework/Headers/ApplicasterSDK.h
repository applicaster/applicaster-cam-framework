//
//  ApplicasterSDK.h
//  ApplicasterSDK
//
//  Created by Anton Kononenko on 06.03.16.
//  Copyright © 2016 Applicaster Ltd. All rights reserved.
//

#import <UIKit/UIKit.h>

//! Project version number for ApplicasterSDK.
FOUNDATION_EXPORT double applicasterSDKVersionNumber;

//! Project version string for ApplicasterSDK.
FOUNDATION_EXPORT const unsigned char applicasterSDKVersionString[];

#import <ApplicasterSDK/APUtils.h>
#import <ApplicasterSDK/APApplicasterResourcesHelper.h>
#import <ApplicasterSDK/APApplicasterController.h>
#import <ApplicasterSDK/APEndUserProfile.h>

#import <ApplicasterSDK/APAdvertiser.h>

#import <ApplicasterSDK/APTimedWebViewController.h>

#import <ApplicasterSDK/APPlayerController.h>

#import <ApplicasterSDK/APLogger.h>
#import <ApplicasterSDK/APAdditions.h>
#import <ApplicasterSDK/APLocalization.h>
#import <ApplicasterSDK/APStateMachine.h>
#import <ApplicasterSDK/APFacebookSDKClient.h>
#import <ApplicasterSDK/APImageLoader.h>
#import <ApplicasterSDK/APReachability.h>
#import <ApplicasterSDK/APSlider.h>
#import <ApplicasterSDK/APAnalytics.h>
#import <ApplicasterSDK/APRunModeDefine.h>
#import <ApplicasterSDK/APMacros.h>
#import <ApplicasterSDK/APRemoteLocalizationClient.h>

#import <ApplicasterSDK/APModel.h>
#import <ApplicasterSDK/APBroadcaster.h>
#import <ApplicasterSDK/APChannel.h>
#import <ApplicasterSDK/APProgram.h>
#import <ApplicasterSDK/APCollection.h>
#import <ApplicasterSDK/APCategory.h>
#import <ApplicasterSDK/APVodItem.h>
#import <ApplicasterSDK/APItemList.h>
#import <ApplicasterSDK/APAtomFeed.h>
#import <ApplicasterSDK/APAccount.h>

#import <ApplicasterSDK/APButton.h>
#import <ApplicasterSDK/APImageView.h>
#import <ApplicasterSDK/APUnhittableView.h>

#import <ApplicasterSDK/APAuthorizationManager.h>

#import <ApplicasterSDK/APAchievementClient.h>
#import <ApplicasterSDK/APACActionViewCell.h>

#import <ApplicasterSDK/APACLeaderBoard.h>
#import <ApplicasterSDK/APACLeaderBoardViewController.h>
#import <ApplicasterSDK/APACLeaderBoardPageViewCell.h>
#import <ApplicasterSDK/APACLeaderBoardViewCell.h>


#import <ApplicasterSDK/APACActionsViewController.h>
#import <ApplicasterSDK/APACScoreNotificationView.h>
#import <ApplicasterSDK/APACSeeHowToPlayView.h>
#import <ApplicasterSDK/APACWelcomeBackViewController.h>
#import <ApplicasterSDK/APACWelcomeViewController.h>
#import <ApplicasterSDK/APACWinnerViewController.h>
#import <ApplicasterSDK/APAdProvider.h>

#import <ApplicasterSDK/APAkamaiClient.h>
#import <ApplicasterSDK/APAnalyticsManager.h>
#import <ApplicasterSDK/APApplicasterAdProvider.h>
#import <ApplicasterSDK/APApplicasterBannerView.h>
#import <ApplicasterSDK/APASIAuthenticationDialog.h>
#import <ApplicasterSDK/APASICacheDelegate.h>
#import <ApplicasterSDK/APASIDataCompressor.h>
#import <ApplicasterSDK/APASIDataDecompressor.h>
#import <ApplicasterSDK/APASIDownloadCache.h>
#import <ApplicasterSDK/APASIHTTPRequest.h>
#import <ApplicasterSDK/APASIHTTPRequestConfig.h>

#import <ApplicasterSDK/AFHTTPRequestOperation+APAddition.h>
#import <ApplicasterSDK/APASIInputStream.h>
#import <ApplicasterSDK/APASINetworkQueue.h>
#import <ApplicasterSDK/APAtomFeedParser.h>
#import <ApplicasterSDK/APBackgroundManager.h>
#import <ApplicasterSDK/APBackgroundPromotedDTCell.h>
#import <ApplicasterSDK/APBanner.h>
#import <ApplicasterSDK/APBannerFactory.h>
#import <ApplicasterSDK/APBannerManager.h>
#import <ApplicasterSDK/APBannerParameters.h>
#import <ApplicasterSDK/APBannerViewController.h>
#import <ApplicasterSDK/APBannerSizes.h>
#import <ApplicasterSDK/APCallbackHandler+JavaScript.h>
#import <ApplicasterSDK/APCallbackHandler.h>
#import <ApplicasterSDK/APCaptureMoment.h>
#import <ApplicasterSDK/APCircleProgressIndicator.h>
#import <ApplicasterSDK/APClickThruWebView.h>

#import <ApplicasterSDK/APCMCharacter.h>
#import <ApplicasterSDK/APCMCustomization.h>
#import <ApplicasterSDK/APCollectionChildMetadata.h>
#import <ApplicasterSDK/APColorPicker.h>
#import <ApplicasterSDK/APComposeViewController.h>
#import <ApplicasterSDK/APCoreUtils.h>
#import <ApplicasterSDK/APCrashReporter.h>
#import <ApplicasterSDK/APCustomAdProvider.h>
#import <ApplicasterSDK/APDefaultPlayerLoadingView.h>
#import <ApplicasterSDK/APDefines.h>
#import <ApplicasterSDK/APEPAdProvider.h>
#import <ApplicasterSDK/APEPBannerView.h>
#import <ApplicasterSDK/APEPGCollectionViewCell.h>
#import <ApplicasterSDK/APEPGDay.h>
#import <ApplicasterSDK/APEPGDayViewCell.h>
#import <ApplicasterSDK/APEPGProgramCell.h>


#import <ApplicasterSDK/APFeedEventQuestion.h>
#import <ApplicasterSDK/NSObject+APAdditions.h>
#import <ApplicasterSDK/APSocialShareSheetSMSShare.h>
#import <ApplicasterSDK/APTimedWebView.h>
#import <ApplicasterSDK/APFeedEventLink.h>
#import <ApplicasterSDK/APVoucherTemplate.h>
#import <ApplicasterSDK/APKeychain.h>
#import <ApplicasterSDK/APEventSequence.h>
#import <ApplicasterSDK/APFacebookCreatePostViewController.h>
#import <ApplicasterSDK/APFeedBanner.h>
#import <ApplicasterSDK/HQMEStateChangedNotification.h>
#import <ApplicasterSDK/APFeedFeed.h>
#import <ApplicasterSDK/APReachabilityManager.h>
#import <ApplicasterSDK/UIFont+APAdditions.h>

#import <ApplicasterSDK/UIViewController+APAdditions.h>
#import <ApplicasterSDK/APJavaScriptListener.h>
#import <ApplicasterSDK/APInstagramCaption.h>
#import <ApplicasterSDK/APTodayVODCollectionViewCell.h>
#import <ApplicasterSDK/APInstagramLocation.h>
#import <ApplicasterSDK/APPlayerInterruptionViewProtocol.h>
#import <ApplicasterSDK/APASIHTTPRequest.h>
#import <ApplicasterSDK/TTTAttributedLabel+TTTAttributedString.h>
#import <ApplicasterSDK/APLocalBannerView.h>
#import <ApplicasterSDK/APWatermarkProviderProtocol.h>
#import <ApplicasterSDK/APPlayable.h>
#import <ApplicasterSDK/APHQMECache.h>
#import <ApplicasterSDK/APTodayProgramCollectionViewCell.h>
#import <ApplicasterSDK/APTakeoverCallbackHandler.h>
#import <ApplicasterSDK/VodItemDownloadOperation.h>
#import <ApplicasterSDK/APStateMachineEvent.h>
#import <ApplicasterSDK/APTwitterUser.h>
#import <ApplicasterSDK/NSArray+APAdditions.h>
#import <ApplicasterSDK/APStoreKitPurchaseParams.h>
#import <ApplicasterSDK/APTwitterItem.h>

#import <ApplicasterSDK/APOverlayController.h>
#import <ApplicasterSDK/APAchievementCustomization.h>
#import <ApplicasterSDK/HQMEDownloadManager.h>
#import <ApplicasterSDK/NSBundle+APAdditions.h>
#import <ApplicasterSDK/APPublicPageBuilder.h>
#import <ApplicasterSDK/APGradientView.h>
#import <ApplicasterSDK/APBreakpointsView.h>
#import <ApplicasterSDK/UIDevice+APAdditions.h>
#import <ApplicasterSDK/APInstagramModel.h>
#import <ApplicasterSDK/APFeedEventImage.h>
#import <ApplicasterSDK/APProgramsProxy.h>
#import <ApplicasterSDK/NSData+APAdditions.h>
#import <ApplicasterSDK/APSocialViewTableCell.h>

#import <ApplicasterSDK/APWebAuthorizationClient.h>
#import <ApplicasterSDK/APFBGraphUser.h>
#import <ApplicasterSDK/NSURL+APAddition.h>
#import <ApplicasterSDK/APInstagramMedia.h>
#import <ApplicasterSDK/APInstagramCommentsCollection.h>
#import <ApplicasterSDK/NSString+HQME.h>
#import <ApplicasterSDK/APAchievementManager.h>
#import <ApplicasterSDK/APFeed2Customization.h>
#import <ApplicasterSDK/APSideMenuTableViewController.h>
#import <ApplicasterSDK/APFacebookAttachment.h>
#import <ApplicasterSDK/UIColor+APAdditions.h>
#import <ApplicasterSDK/APPlayerCommercialsProtocol.h>

#import <ApplicasterSDK/APServerSwitchManager.h>
#import <ApplicasterSDK/APNotificationNames.h>
#import <ApplicasterSDK/HQMEApplicasterDataStore.h>
#import <ApplicasterSDK/APPlayerControls.h>
#import <ApplicasterSDK/APPlayerControlsView.h>
#import <ApplicasterSDK/APFacebookCommentsTextViewWithOverlay.h>
#import <ApplicasterSDK/APSocialActionView.h>

#import <ApplicasterSDK/APFeedEvent.h>
#import <ApplicasterSDK/NSString+APAdditions.h>
#import <ApplicasterSDK/APIdentityClient.h>
#import <ApplicasterSDK/APTodayFeedEpisodeStatusApplicasterDataProvider.h>
#import <ApplicasterSDK/UIView+APAnimation.h>
#import <ApplicasterSDK/APFacebookCommentsCommentingTableViewCell.h>
#import <ApplicasterSDK/APStarsClient.h>
#import <ApplicasterSDK/APEPGViewController.h>
#import <ApplicasterSDK/APEvent.h>

#import <ApplicasterSDK/NSString+InflectionSupport.h>
#import <ApplicasterSDK/APFeedUser.h>
#import <ApplicasterSDK/APTwitterClient.h>
#import <ApplicasterSDK/SKProduct+APAdditions.h>
#import <ApplicasterSDK/APPlayerSocialControls.h>
#import <ApplicasterSDK/APFavoritesManager.h>
#import <ApplicasterSDK/APTimelinesManager.h>
#import <ApplicasterSDK/APPlayerConstants.h>
#import <ApplicasterSDK/HQMEManager.h>
#import <ApplicasterSDK/APNativePlayerViewController.h>
#import <ApplicasterSDK/APAVPlayerViewController.h>
#import <ApplicasterSDK/APFeedAnswerOfQuestionEvent.h>
#import <ApplicasterSDK/APACUser.h>
#import <ApplicasterSDK/APModelCollection.h>
#import <ApplicasterSDK/APMacros.h>
#import <ApplicasterSDK/APAtomMediaGroup.h>
#import <ApplicasterSDK/APModel+Internal.h>


#import <ApplicasterSDK/APRater.h>
#import <ApplicasterSDK/APSocialShareSheetCell.h>
#import <ApplicasterSDK/APImageFromDataLoader.h>
#import <ApplicasterSDK/APAuthorizationProvider.h>
#import <ApplicasterSDK/APLoggerFormatter.h>
#import <ApplicasterSDK/APPlayer.h>
#import <ApplicasterSDK/APInstagramUser.h>
#import <ApplicasterSDK/APSocialShareSheetFacebookShare.h>
#import <ApplicasterSDK/UINavigationController+APAdditions.h>
#import <ApplicasterSDK/APFeedEventEpisodeMessage.h>
#import <ApplicasterSDK/UIView+APAdditions.h>
#import <ApplicasterSDK/APSideMenuItem.h>
#import <ApplicasterSDK/APPurchasableItem.h>
#import <ApplicasterSDK/APASIProgressDelegate.h>

#import <ApplicasterSDK/NSDate+APAdditions.h>
#import <ApplicasterSDK/APFeedEventQuestionnaire.h>
#import <ApplicasterSDK/APPlayer+Internal.h>
#import <ApplicasterSDK/APFeedStarsEvent.h>
#import <ApplicasterSDK/APSocialSharingManager.h>
#import <ApplicasterSDK/APFacebookCommentsFilterAlertView.h>
#import <ApplicasterSDK/APFacebookPostObject.h>
#import <ApplicasterSDK/APFacebookWatchManager.h>
#import <ApplicasterSDK/APNetworkManager.h>

#import <ApplicasterSDK/APHttpServer.h>

#import <ApplicasterSDK/APStateMachineConfiguration.h>
#import <ApplicasterSDK/APTimedWebVCCallbackHandler.h>
#import <ApplicasterSDK/APHTTPResponseHandler.h>
#import <ApplicasterSDK/APInstagramImage.h>
#import <ApplicasterSDK/APStoreKitManager.h>
#import <ApplicasterSDK/APInstagramPagination.h>
#import <ApplicasterSDK/APFacebookCommentsManager.h>
#import <ApplicasterSDK/APSocialShareSheetWhatsAppShare.h>

#import <ApplicasterSDK/APSNStatusManager.h>
#import <ApplicasterSDK/APTodayFeedEpisodeStatusViewController.h>
#import <ApplicasterSDK/APTakeOverEventViewController.h>
#import <ApplicasterSDK/APFeed2EventWidgetQuestion.h>
#import <ApplicasterSDK/AVPlayerItem+APAdditions.h>
#import <ApplicasterSDK/APASIHTTPRequestDelegate.h>
#import <ApplicasterSDK/MFMailComposeViewController+APAdditions.h>
#import <ApplicasterSDK/APOwnershipProxy.h>
#import <ApplicasterSDK/APFeedEventMessage.h>
#import <ApplicasterSDK/APURLSchemeHandler.h>
#import <ApplicasterSDK/APSocialShareSheetSharingProtocol.h>

#import <ApplicasterSDK/APFacebookPostCellView.h>
#import <ApplicasterSDK/APPlayerViewController.h>
#import <ApplicasterSDK/APLoadingView.h>
#import <ApplicasterSDK/APSocialShareSheetViewController.h>
#import <ApplicasterSDK/APQueuePlayer.h>
#import <ApplicasterSDK/APFacebookCommentCellView.h>
#import <ApplicasterSDK/APUGCController.h>

#import <ApplicasterSDK/APSocialShareSheetMailShare.h>
#import <ApplicasterSDK/APPlayerInterruptionView.h>
#import <ApplicasterSDK/APPlayerController+APInternal.h>
#import <ApplicasterSDK/APPreloadViewController.h>
#import <ApplicasterSDK/APPlayerView.h>
#import <ApplicasterSDK/APASIInputStream.h>
#import <ApplicasterSDK/APStarsManager.h>
#import <ApplicasterSDK/APImagePicker.h>
#import <ApplicasterSDK/APSpringyCollectionFlowLayout.h>
#import <ApplicasterSDK/APAtomEntry.h>
#import <ApplicasterSDK/APSideMenuController.h>
#import <ApplicasterSDK/APResourceHelper.h>
#import <ApplicasterSDK/APNotificationManager.h>

#import <ApplicasterSDK/APStoreKitPurchase.h>
#import <ApplicasterSDK/APMediaPlayback.h>
#import <ApplicasterSDK/NSURLComponents+APAddition.h>
#import <ApplicasterSDK/APFacebookCommentsView.h>
#import <ApplicasterSDK/APURLRedirect.h>
#import <ApplicasterSDK/APSocialShareSheetTwitterShare.h>
#import <ApplicasterSDK/APPlayerAudioOnlyView.h>
#import <ApplicasterSDK/APHQMECategory.h>
#import <ApplicasterSDK/APFeed2EventWidgetAnswer.h>
#import <ApplicasterSDK/APACChallenge.h>


#import <ApplicasterSDK/APInstagramLikesCollection.h>
#import <ApplicasterSDK/APSupportRequest.h>
#import <ApplicasterSDK/APTodayEPGVODViewController.h>
#import <ApplicasterSDK/NSFileManager+APAdditions.h>
#import <ApplicasterSDK/APPlayerControllsNotifications.h>
#import <ApplicasterSDK/UIImage+APAdditions.h>
#import <ApplicasterSDK/APSocialSharingManager+NSObject.h>
#import <ApplicasterSDK/APFacebookCommentsFilter.h>
#import <ApplicasterSDK/APInstagramVideo.h>
#import <ApplicasterSDK/APURLPlayable.h>
#import <ApplicasterSDK/APInstagramClient.h>
#import <ApplicasterSDK/APFeedEpisode.h>

#import <ApplicasterSDK/APStoreKitProducts.h>

#import <ApplicasterSDK/APStreamResponseHandler.h>
#import <ApplicasterSDK/APFeedTimeline.h>
#import <ApplicasterSDK/APInstagramUserInPhoto.h>
#import <ApplicasterSDK/APTimedWebViewControllerDelegate.h>
#import <ApplicasterSDK/APVoucher.h>
#import <ApplicasterSDK/APFacebookCommentsController.h>
#import <ApplicasterSDK/APFeedEventVideo.h>
#import <ApplicasterSDK/UIScrollView+APAdditions.h>
#import <ApplicasterSDK/APFacebookCommentsObject.h>
#import <ApplicasterSDK/APFacebookCommentsPostTableViewCell.h>
#import <ApplicasterSDK/APSwitcherView.h>
#import <ApplicasterSDK/UIAlertView+APAdditions.h>
#import <ApplicasterSDK/APFacebookCommentsCommentTableViewCell.h>
#import <ApplicasterSDK/APTwitterManager.h>
#import <ApplicasterSDK/APSocialPlayerControlsView.h>


#import <ApplicasterSDK/APEventsPollingManager.h>
#import <ApplicasterSDK/APShareable.h>
#import <ApplicasterSDK/APGoogleBannerStitialViewController.h>
#import <ApplicasterSDK/APFreewheelBannerView.h>
#import <ApplicasterSDK/APiAdBannerView.h>
#import <ApplicasterSDK/APGoogleAdProvider.h>
#import <ApplicasterSDK/APEPInterstitialAd.h>
#import <ApplicasterSDK/APGoogleBannerView.h>
#import <ApplicasterSDK/APGoogleInterstitialManager.h>
#import <ApplicasterSDK/APGoogleAdProviderParametersKeys.h>
#import <ApplicasterSDK/APBannerView.h>
#import <ApplicasterSDK/APFreewheelVideoViewController.h>
#import <ApplicasterSDK/APGoogleAdsBannerType.h>
#import <ApplicasterSDK/APFreewheelAdProvider.h>
#import <ApplicasterSDK/APStreamSenseManager.h>
#import <ApplicasterSDK/APGoogleIMAPlayerManager.h>
#import <ApplicasterSDK/APValidationFlowProtocol.h>
#import <ApplicasterSDK/APiAdProvider.h>
#import <ApplicasterSDK/APURLSchemeHandlerProtocol.h>
#import <ApplicasterSDK/APTimelinesManager.h>
#import <ApplicasterSDK/APSideMenuTableViewCell.h>
