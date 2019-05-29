//
//  APAtomFeed.h
//  applicaster
//
//  Created by Miri on 10/27/14.
//  Copyright (c) 2014 Applicaster Ltd. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "APCategory.h"
#import "APShareable.h"

/*
 This type of feed determined by entries
 Feed can be: 
 APAtomFeedNatureArticle type if contains just article entries,
 APAtomFeedNatureImage type if contains just images entries,
 APAtomFeedNatureImageGallery type if contains just Galery entries ,
 APAtomFeedNatureMix type if contains some types
 */

@class APAtomEntry;
typedef enum{
    APAtomFeedNatureUnknown,
    APAtomFeedNatureArticle,
    APAtomFeedNatureVideo,
    APAtomFeedNatureImage,
    APAtomFeedNatureImageGallery,
    APAtomFeedNatureMix
} APAtomFeedNature;

@interface APAtomFeed : APCategory <APShareable>

/*
 Identifier - item identifier.
 */
@property (nonatomic, strong) NSString *atomFeedIdentifier;

/*
 Title - item title.
 */
@property (nonatomic, strong) NSString *atomFeedTitle;

/*
 SubTitle - description of item.
 */
@property (nonatomic, strong) NSString *atomFeedSubTitle;

/*
 Summary - description of item.
 */
@property (nonatomic, strong) NSString *atomFeedSummary;

/*
 */
@property (nonatomic, strong) NSString *atomFeedPublishDate;

/*
 UpdateDate - date the item was updated if available.
 */
@property (nonatomic, strong) NSString *atomFeedUpdateDate;


@property (nonatomic, strong) NSURL *atomFeedLink;

/**
 The value of the link will be used as the shared link URL of the feed.
 */
@property (nonatomic, strong) NSURL *atomFeedShareLink;

/*
 Author - .
 */
@property (nonatomic, strong) NSString *atomFeedAuthor;

/*
 Entries - array of all entries.
 */
@property (nonatomic, copy) NSArray *atomFeedEntries;

/**
 Returns the feed nature - Article, Video, Image, Gallery, mix.
 */
@property (nonatomic, assign) APAtomFeedNature atomFeedNature;

/*
 MediaGroup - element groups media assets from the same type.
 */
@property (nonatomic, strong) NSMutableArray *atomFeedMediaGroups;

- (instancetype)initWithEntry:(APAtomEntry *)entry;

- (NSString *)imageNamed:(NSString*)name
                   scale:(NSString *)scale;


@end
