//
//  APSideMenuController.h
//
//  Side menu class to ease development of applications with side menu
//  This class requires iOS 5 and Up due to use of child view controllers
//
//  TODO:
//  1. Implement expanding cells
//  2. Custom initializers for customization
//
//  Created by Philip Kramarov & Liviu Romascanu on 7/10/13.
//  Copyright (c) 2013 Applicaster. All rights reserved.
//
#import "APSideMenuTableViewController.h"

@class APSideMenuController;
@class APSideMenuItem;
/**
 Both Notifications will put NSNumber with leftMenuState in the object parameter.
 */
extern NSString *const kAPSideMenuLeftMenuWillChangeStateNotification; // sets the object to be the future state.
extern NSString *const kAPSideMenuLeftMenuDidChangeStateNotification; // sets the object to be the new state after change.

/**
 Used to describe the states of the sideMenu.
 */
typedef enum{
	APSideMenuStateClosed,          /**< The side menu is closed */
	APSideMenuStateSemiOpened,      /**< The side menu is semi opened */
	APSideMenuStateFullyOpened,    /**< The side menu is semi opened */
} APSideMenuState;

/**
 Used to describe the states of the sideMenu.
 */
typedef enum{
	APSideMenuPanStateDisabled,             /**< Panning the side menu is disabled */
	APSideMenuPanStatePanFromTopBarOnly,    /**< Panning the side menu is enabled from the top bar only */
	APSideMenuPanStateFullPan,              /**< Panning the side menu is enabled from the whole area of center view controller */
} APSideMenuPanState;


typedef NS_ENUM(NSUInteger, APNavigationBarPlace) {
    APNavigationBarPlaceOnTopOfRootController,
    APNavigationBarPlaceOverlayRootController
};

@protocol APSideMenuDelegate <NSObject>

@optional

/**
 Handle side menu item will be selected.
 @param sideMenuItem Side menu item that will be selected.
 @param indexPath Index path of item.
 */
-(void)willSelectSideMenuItem:(APSideMenuItem *)sideMenuItem atIndexPath:(NSIndexPath *)indexPath;

/**
 Handle side menu item selected
 */
-(void)didSelectSideMenuItem:(APSideMenuItem *)sideMenuItem atIndexPath:(NSIndexPath *)indexPath;

/**
 Handle re-order in the delegate
 @param APSideMenuController - the side menu controller delegating the reorder
 @param NSInteger source item index in the data array
 @param NSInteger destination item index in the data array
 */
- (void)sideMenuController:(APSideMenuController *)sideMenuController
         moveItemFromIndex:(NSInteger)sourceIndex
                   toIndex:(NSInteger)destinationIndex;

@end

#pragma mark -

@interface APSideMenuController : UIViewController <APSideMenuTableViewControllerDelegate>

/**
 A pan state for the left side menu. Default value is APSideMenuPanStateFullPan.
 */
@property (nonatomic, assign) APSideMenuPanState leftMenuPanState;

/**
 State of navigation bar placements. Default value is APNavigationBarPlaceOnTopOfRootController.
 */
@property (nonatomic) APNavigationBarPlace navigationBarPlace;

/**
 Delegate
 */
@property (nonatomic, weak) id<APSideMenuDelegate> delegate;

/**
 Side Menu Table View Controller - used to display the table and selection
 */
@property (nonatomic, strong, readonly) IBOutlet APSideMenuTableViewController *sideMenuTableViewController;
/**
 Center view controller - used to contain the content view controllers as child view controller
 */
@property (nonatomic, strong, readonly) IBOutlet UIViewController *centerViewController;

/**
 Current Centered view controller - the currently selected viewController inside the centerViewController
 */
@property (nonatomic, strong, readonly) UIViewController *currentCenteredViewController;

/**
 The fully opened width of the sideMenu.
 */
@property (nonatomic, assign) CGFloat ledgeWidth;

/**
 The semi opened width of the sideMenu.
 */
@property (nonatomic, assign) CGFloat ledgeSemiOpenedWidth;

/**
 Set this BOOL to YES if you want your menu to be two steps menu (semi and opened).
 */
@property (nonatomic, assign) BOOL isTwoStepsMenu;

/**
 The frame for this viewController.
 */
@property (nonatomic, assign) CGRect frame;

/**
 Mutable array of side menu items
 TODO: Implement a smart setter for it that will reload the table
 */
@property (nonatomic, strong) NSMutableArray *sideMenuItemDataArray;

/**
 Currently selected menu item
 */
@property (nonatomic, weak) APSideMenuItem *selectedMenuItem;

/**
 If not null, displayed on top of the center view
 */
@property (nonatomic, strong) UIView *customTopBar;

/**
 if YES content will be blocked if menu was opened. Every tap on the content area will close the sideMenu.
 */
@property (nonatomic, assign) BOOL shouldBlockContentIfMenuOpened;

/**
 A boolean maintaining the state of the left side menu.
 */
@property (nonatomic, assign, readonly) APSideMenuState leftSideMenuState;

/**
 A boolean maintaining the state of the left side menu.
 */
@property (nonatomic, assign) BOOL isSideMenuReorderable;

// ---------------------------- Initialization ---------------------------- //

/**
 Custom Initializer with Side menu table view controller classe
 */
- (id)initWithSideMenuTableViewControllerClass:(Class)sideMenuTableClass;

/**
 Custom Initializer with Side menu table view controller nib name
 */
- (id)initWithSideMenuTableViewControllerNib:(NSString *)sideMenuTableNib;

// ---------------------------- Public methods ---------------------------- //

/**
 Add side menu item to the items array
 @return the index path of the added item in the menu
 */
- (NSIndexPath *)addSideMenuItem:(APSideMenuItem *)sideMenuItem;

/**
 replaces a side menu item at index with replacement
 */
- (void)replaceSideMenuItemAtIndex:(NSUInteger)index with:(APSideMenuItem *)replacement;

/**
 Toggle side Menu. This will toggle the menu to it's next state between all available steps. 
 */
- (void)toggleLeftMenu;

/**
 Closes the side menu. For default behaviour use toggleLeftMenu instead.
 */
- (void)closeLeftSideMenu;

/**
 Semi opens the side menu (pushes the screen in ledgeSemiOpenedWidth px). For default behaviour use toggleLeftMenu instead.
 */
- (void)semiOpenLeftSideMenu;

/**
 Fully opens the side menu (pushes the screen in ledgeWidth px). For default behaviour use toggleLeftMenu instead.
 */
- (void)fullyOpenLeftSideMenu;

/**
 Select a side menu item programmatically by its index path
 */
-(void)programmaticallySelectItemAtIndexPath:(NSIndexPath *)indexPath;

@end

/**
 Protocol that should be implemented by child view controllers that will be the content of the app
 */
@protocol APSideMenuControllerItem <NSObject>

/**
 Containing side menu controller
 */
@property (nonatomic, weak) APSideMenuController *sideMenuController;

@optional
/**
 Side menu toggle action
 */
- (IBAction)toggleSideMenu:(id)sender;

@end
