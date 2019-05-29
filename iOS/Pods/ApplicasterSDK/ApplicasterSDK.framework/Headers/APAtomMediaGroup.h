//
//  APAtomMediaGroup.h
//  applicaster
//
//  Created by Philip Kramarov on 11/22/14.
//  Copyright (c) 2014 Applicaster Ltd. All rights reserved.
//

#import <Foundation/Foundation.h>

@interface APAtomMediaGroup : NSObject

@property (nonatomic, strong, readonly) NSString *type;
@property (nonatomic, strong, readonly) NSMutableDictionary *mediaItems;

/**
 init the media group with it's type (image/video)
 and with an empty list of media items
 */
- (instancetype)initWithType:(NSString *)type;

- (void)addMediaItemType:(NSString *)type
               stringURL:(NSString *)sourceURL
                   scale:(NSString *)scale;

- (NSString *)mediaItemStringURLForType:(NSString *)type
                                  scale:(NSString *)scale;

@end