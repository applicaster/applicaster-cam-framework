//
//  APSideMenuTableViewController.h
//  SideMenuControllerExample
//
//  Table view controller to accompany the side menu controller
//
//  Created by Liviu Romascanu on 7/22/13.
//  Copyright (c) 2013 Applicaster. All rights reserved.
//

#import <UIKit/UIKit.h>

@protocol APSideMenuTableViewControllerDelegate;
@class APSideMenuController, APSideMenuItem;

@interface APSideMenuTableViewController : UIViewController <UITableViewDataSource , UITableViewDelegate>
/**
 Contained table view - can be done either by code or an outlet
 */
@property (nonatomic, weak) IBOutlet UITableView *tableView;

/**
 Delegate Side menu
 */
@property (nonatomic, weak) id<APSideMenuTableViewControllerDelegate> delegate;

/**
 Toggle if to allow reordering of the items
 */
@property (nonatomic, assign) BOOL allowReorder;

/**
 Programmatically select menu item
 */
- (void)programmaticallySelectItemAtIndexPath:(NSIndexPath *)selectedIndexPath;

/**
 Called before toggling the submenu
 */
- (void)willToggleSubmenuAtSection:(NSInteger)section;

/**
 toggling the submenu
 */
- (void)toggleSubmenuAtIndexPath:(NSIndexPath *)indexPath;

/**
 Reorder button clicked
 */
- (IBAction)reorderButtonClicked:(id)sender;
@end

/**
 Side Menu Table Delegate
 */
@protocol APSideMenuTableViewControllerDelegate <NSObject>
@required
/**
 Get item metadata for index path.
 @param sideMenuTableViewController - for which to get the data
 @param indexPath for the item
 @return APSideMenuItem containing the correct metadata for the table
 */
- (APSideMenuItem *)sideMenuTableViewController:(APSideMenuTableViewController *)sideMenuTableViewController metadataForObjectAtIndexPath:(NSIndexPath *)indexPath;

/**
 Is called when side menu item will be selected
 @param sideMenuTableViewController
 @param indexPath of the item that will be selected
 */
- (void)sideMenuTableViewController:(APSideMenuTableViewController *)sideMenuTableViewController willSelectItemAtIndexPath:(NSIndexPath *)indexPath;

/**
 Selection method to convey selection in the table
 @param sideMenuTableViewController
 @param indexPath of the selected item
 */
- (void)sideMenuTableViewController:(APSideMenuTableViewController *)sideMenuTableViewController didSelectItemAtIndexPath:(NSIndexPath *)indexPath;

- (void)sideMenuTableViewController:(APSideMenuTableViewController *)sideMenuTableViewController moveRowAtIndexPath:(NSIndexPath *)sourceIndexPath toIndexPath:(NSIndexPath *)destinationIndexPath;

/**
 Total number of items to display in table
 */
- (NSInteger)numberOfItems;

@end

@protocol SideMenuTableCellView <NSObject>

@property (nonatomic, strong) IBOutlet UILabel *name;
@property (nonatomic, strong) IBOutlet UIImageView *imageView;
@property (nonatomic, readonly) float height;
@property (nonatomic, readonly) float childItemHeight;

@end