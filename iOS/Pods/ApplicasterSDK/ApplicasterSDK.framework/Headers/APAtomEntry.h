//
//  APAtomEntry.h
//  applicaster
//
//  Created by Miri on 10/23/14.
//  Copyright (c) 2014 Applicaster Ltd. All rights reserved.
//

#import <Foundation/Foundation.h>

#import "APURLPlayable.h"
#import "APShareable.h"

@class APContent;
@class APAtomMediaGroup;
@class APAtomEntryPlayable;

/*
 Type of entry
  */
typedef enum{
    APEntryTypeUnknown,
    APEntryTypeArticle,
    APEntryTypeVideo,
    APEntryTypeImage,
    APEntryTypeImageGallery,
} APEntryType;

#pragma mark - APAtomEntry

@interface APAtomEntry : NSObject <APShareable>

/*
 Title - title of the parent feed (forward from the parent).
 */
@property (nonatomic, strong) NSString *parentTitle;

/*
 EntryType - item type.
 */
@property (nonatomic, assign) APEntryType entryType;

/*
 Title - item title.
 */
@property (nonatomic, strong) NSString *title;

/*
 Summary - description of item.
 */
@property (nonatomic, strong) NSString *summary;

/*
 Link
 */
@property (nonatomic, copy) NSString *link;

/*
 Identifier - item identifier.
 */
@property (nonatomic, strong) NSString *identifier;

/*
 PublishDate - date the item was published.
 */
@property (nonatomic, strong) NSString *publishDate;

/*
 UpdateDate - date the item was updated if available.
 */
@property (nonatomic, strong) NSString *updateDate;

/*
 Content - more detailed content (if available).
 */
@property (nonatomic, strong) APContent *content;

/*
 MediaGroup - element groups media assets from the same type.
 */
@property (nonatomic, strong) NSMutableArray *mediaGroups;

/**
 Returns a string URL of the first media group with small scale.
 @param name of the image from the image dictionary. (Name is ignored at the moment)
 @return image string URL
 */
- (NSString *)imageNamed:(NSString*)name;

/**
 Returns a string URL of the first media group.
 @param scale of the image from the media group items.
 @param group of media assets from the same type.
 @return image string URL
 */
- (NSString *)imageForScale:(NSString *)scale mediaGroup:(APAtomMediaGroup *)mediaGroup;


/**
 *  Finds the first media group by wanted type
 *  @param type wanted type
 *  @return first wanted media group
 */
- (APAtomMediaGroup *)mediaGroupWithType:(NSString *)type;

/**
 Compares to models.
 @param otherModel The other model to compare to.
 @return YES if models points are equal, NO if not.
 */
- (BOOL)isEqualToModel:(APAtomEntry *)otherModel;

/**
 @return A new instance of playable for this entry each call.
 */
- (APAtomEntryPlayable *)playable;

@end

#pragma mark - APContent

@interface APContent: NSObject

@property (nonatomic, strong) NSString *type;
@property (nonatomic, strong) NSString *src;
@property (nonatomic, strong) NSString *content;

@end

#pragma mark -  APAtomEntryPlayable

@interface APAtomEntryPlayable : APURLPlayable <APPlayable>

#pragma mark - Init

- (instancetype)initWithAtomEntry:(APAtomEntry *)atomEntry;

#pragma mark - Properties

/**
 @return The name of the AtomFeed that contains this entry.
 */
- (NSString *)feedName;

@end
