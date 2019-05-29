//
//  APBroadcaster.h
//  applicaster
//
//  Created by Guy Kogus on 5/01/12.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "APModel.h"

@class APCategory, APItemList;


/**
 APBroadcaster model represents the broadcaster object in the CMS.
 A broadcaster resides under an account and represents a group of Categories , Item lists and VOD items relevant to the specific broadcaster.
 This can either represent a show , an application or a language for example.
 
 Broadcasters should be fetched from The current account in the following manner:
 [[[APApplicasterController sharedInstance] account] broadcasters];
 Also - after choosing a broadcaster - the application should set it as the current broadcaster in the APApplicaster controller shared instance
 
 The Broadcaster info comes cashed and usually should not be loaded.
 
 A very important use of the broadcaster is to get the correct Content category and Item lists IDs
 */
@interface APBroadcaster : APModel {
	
}

#pragma mark - Properties

/**
 Parent Account ID
 */
@property (unsafe_unretained, readonly) NSString *accountID;

/**
 Broadcaster name
 */
@property (unsafe_unretained, readonly) NSString *name;

/**
 HQME ItemList ID 
 Note - HQME is no longer defined by server as the HQME item list contents - but rather a VOD Item property.
 */
@property (unsafe_unretained, readonly) NSString *hqmeItemListId;

/**
 Featured Item list Identifier
 */
@property (unsafe_unretained, readonly) NSString *featuredItemListId;

/**
 Recent Item list identifier
 */
@property (unsafe_unretained, readonly) NSString *recentItemListId;

/**
 Content Category identifier
 */
@property (unsafe_unretained, readonly) NSString *contentCategoryId;

/**
 Search Category identifier
 */
@property (unsafe_unretained, readonly) NSString *searchContentCategoryId;

/**
 Item List 1 ID
 */
@property (unsafe_unretained, readonly) NSString *itemList1Id;

/**
 Item List 2 ID
 */
@property (unsafe_unretained, readonly) NSString *itemList2Id;

/**
 Item List 3 ID
 */
@property (unsafe_unretained, readonly) NSString *itemList3Id;

/**
 Item List 4 ID
 */
@property (unsafe_unretained, readonly) NSString *itemList4Id;

/**
 Item List 5 ID
 */
@property (unsafe_unretained, readonly) NSString *itemList5Id;

/**
 Item List 6 ID
 */
@property (unsafe_unretained, readonly) NSString *itemList6Id;

/**
 Item List 7 ID
 */
@property (unsafe_unretained, readonly) NSString *itemList7Id;

/**
 Item List 8 ID
 */
@property (unsafe_unretained, readonly) NSString *itemList8Id;

/**
 Item List 9 ID
 */
@property (unsafe_unretained, readonly) NSString *itemList9Id;

/**
 Item List 10 ID
 */
@property (unsafe_unretained, readonly) NSString *itemList10Id;

/**
 Item List 11 ID
 */
@property (unsafe_unretained, readonly) NSString *itemList11Id;

/**
 Item List 12 ID
 */
@property (unsafe_unretained, readonly) NSString *itemList12Id;

/**
 Item List 13 ID
 */
@property (unsafe_unretained, readonly) NSString *itemList13Id;

/**
 Item List 14 ID
 */
@property (unsafe_unretained, readonly) NSString *itemList14Id;

/**
 Item List 15 ID
 */
@property (unsafe_unretained, readonly) NSString *itemList15Id;

/**
 Item List 16 ID
 */
@property (unsafe_unretained, readonly) NSString *itemList16Id;

/**
 Item List 17 ID
 */
@property (unsafe_unretained, readonly) NSString *itemList17Id;

/**
 Item List 18 ID
 */
@property (unsafe_unretained, readonly) NSString *itemList18Id;

/**
 Item List 19 ID
 */
@property (unsafe_unretained, readonly) NSString *itemList19Id;

/**
 Item List 20 ID
 */
@property (unsafe_unretained, readonly) NSString *itemList20Id;

/**
 Item List 21 ID
 */
@property (unsafe_unretained, readonly) NSString *itemList21Id;

/**
 Item List 22 ID
 */
@property (unsafe_unretained, readonly) NSString *itemList22Id;

/**
 Item List 23 ID
 */
@property (unsafe_unretained, readonly) NSString *itemList23Id;


/**
 Banners Item list ID
 */
@property (unsafe_unretained, readonly) NSString *bannersItemListId;

/**
 By default returns item list 9 (for backwards compatibility). Set this value to an empty string (@"") instead of nil to remove the promoted item list from being loaded in Back From Background.
 */
@property (nonatomic, copy) NSString *promotedItemListID;

/**
 Email body to be used from App / EPG
 */
@property (nonatomic, strong, readonly) NSString *emailBody;

/**
 Email subject to be used from App / EPG
 */
@property (nonatomic, strong, readonly) NSString *emailSubject;

/**
 free represents if the entire content of the broadcaster should be free or not.
 Free content will be playable even on nonfree apps
 */
@property (nonatomic, readonly) BOOL free;


#pragma mark - APBroadcaster

/**
 Method to create the virtual root category.
 This should probably not be used
 @return Virtual Root category of the broadcaster
 */
- (APCategory *)virtualRootCategory;

/**
 Returns the content category defined for the broadcaster.
 @return The root content category.
 */
- (APCategory *)contentCategory;

/**
 Returns the search content category defined for the broadcaster.
 @return The search content category.
 */
- (APCategory *)searchContentCategory;

/**
 Category with Identifier - Ready to be loaded from this broadcaster
 @param ID for category
 @return APCategory ready for load
 */
- (APCategory *)categoryWithID:(NSString *)ID;

/**
 Item List with Identifier - Ready to be loaded from this broadcaster
 @param ID for Item List
 @return APItemList ready for load
 */
- (APItemList *)itemListWithID:(NSString *)ID;

@end
