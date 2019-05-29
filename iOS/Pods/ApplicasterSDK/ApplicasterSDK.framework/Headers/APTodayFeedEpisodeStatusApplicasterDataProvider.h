//
//  APFeedEpisodeStatusApplicasterDataProvider.h
//  applicaster
//
//  Created by Liviu Romascanu on 10/2/14.
//  Copyright (c) 2014 Applicaster Ltd. All rights reserved.
//

@protocol APTodayFeedEpisodeStatusApplicasterDataProvider <NSObject>

@required
/**
 @return Applicaster Stars Account ID
 */
- (NSString *)starsAccountID;

/**
 @return Applicaster Stars Timeline ID
 */
- (NSString *)feedTimelineID;

/**
 @return Application URL Scheme used to launch the app from the widget
 */
- (NSString *)appURLScheme;

@optional
/**
 @return Application Icon returned for the launch button
 */
- (UIImage *)appIcon;
@end