//
//  APSideMenuTableViewCell.h
//  ApplicasterUIKit
//
//  Created by Hagit Shemer on 11/25/13.
//  Copyright (c) 2013 Applicaster. All rights reserved.
//

@class APSideMenuItem;

@interface APSideMenuTableViewCell : UITableViewCell

/**
 *  Connect this label in your xib in order to override the native textLabel property of a TableViewCell.
 */
@property (nonatomic, weak) IBOutlet UILabel *itemTitleLabel;

/**
 *  Connect this imageView in your xib in order to override the native imageView property of a TableViewCell.
 */
@property (nonatomic, weak) IBOutlet UIImageView *itemImageView;

/**
 * The view that is shown when item is expandable but closed.
 */
@property (nonatomic, strong) IBOutlet UIView *expandableIndicatorView;

/**
 * The view that is shown when item is expandable but closed.
 */
@property (nonatomic, strong) IBOutlet UIView *expandableIndicatorViewSelected;

@property (nonatomic, strong) IBOutlet UIView *expandableIndicatorViewExpanded;

@property (nonatomic, strong) IBOutlet UIView *expandableIndicatorViewExpandedSelected;

/**
 The side menu item given for this cell.
 */
@property (nonatomic, strong, readonly) APSideMenuItem *sideMenuItem;

/**
 Set the side menu item attributes - image, selected image, image URL, selected image URL
 @param sideMenuItem - the side menu item to get the attributes from
**/
- (void)setSideMenuItemAttributes:(APSideMenuItem *)sideMenuItem;

/**
 Method synchronously loads an image for menu item. It can be overridden.
 @param url - image URL
 @param callback - completion block which receives loaded image
**/
- (void)loadImageFromURL:(NSURL*)url callback:(void (^)(UIImage *image))callback;

/*
 Sets the appropriate state of an expandable cell
 */
@property (nonatomic) BOOL expanded;

/*
 specifies whether a cell has sublevels
 */
@property (nonatomic) BOOL isExpandable;

@end
