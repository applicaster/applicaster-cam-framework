//
//  APSideMenuItemData.h
//  SideMenuControllerExample
//
//  Side menu item containing the metadata and view controller / children side menu items
//
//  Created by Liviu Romascanu on 7/22/13.
//  Copyright (c) 2013 Applicaster. All rights reserved.
//

#import <Foundation/Foundation.h>

@class APSideMenuControllerItem;
@protocol APSideMenuControllerItem;

/**
 Side menu item style attributes keys
 */
extern NSString *const kAPSideMenuItemAttributeCellNibName;         // NSString
extern NSString *const kAPSideMenuItemAttributeCellBundlePath;      // Set this attribute in order to override the bundle path which the cell's xib will be taken from. Default bundle is main bundle.

extern NSString *const kAPSideMenuItemAttributeFont;                // UIFont
extern NSString *const kAPSideMenuItemAttributeLabelLeftIndent;     // NSNumber with float value
extern NSString *const kAPSideMenuItemAttributeImageLeftIndent;     // NSNumber with float value
extern NSString *const kAPSideMenuItemAttributeImage;               // UIImage
extern NSString *const kAPSideMenuItemAttributeImageSelected;       // UIImage
extern NSString *const kAPSideMenuItemAttributeImageURL;            // NSURL
extern NSString *const kAPSideMenuItemAttributeImageURLSelected;    // NSURL
extern NSString *const kAPSideMenuItemAttributeFgColor;             // UIColor
extern NSString *const kAPSideMenuItemAttributeFgColorSelected;     // UIColor
extern NSString *const kAPSideMenuItemAttributeBgColor;             // UIColor
extern NSString *const kAPSideMenuItemAttributeBgColorSelected;     // UIColor
extern NSString *const kAPSideMenuItemAttributeBgView;              // UIView
extern NSString *const kAPSideMenuItemAttributeBgViewSelected;      // UIView
extern NSString *const kAPSideMenuItemAttributeSeparatorColor;      // UIColor

extern NSString *const kAPSideMenuItemAttributeExpandableIndicatorView;         // UIView
extern NSString *const kAPSideMenuItemAttributeExpandableIndicatorViewSelected; // UIView
extern NSString *const kAPSideMenuItemAttributeExpandableIndicatorViewExpanded;         // UIView
extern NSString *const kAPSideMenuItemAttributeExpandableIndicatorViewExpandedSelected; // UIView

@interface APSideMenuItem : NSObject

/**
 Menu Item Name
 */
@property (nonatomic, strong) NSString *name;

/**
 Is menu item exandable
 TODO: Consider changing to readonly
 */
@property (nonatomic, assign, readonly) BOOL isExpandable;

/**
 Is menu item currently expanded
 */
@property (nonatomic, assign) BOOL isExpanded;

/**
 is the children array loaded
 It's an opt point for future loading data for children
 */
@property (nonatomic, assign) BOOL isLoaded;

/**
 Children array - should only contain Side Menu Items
 */
@property (nonatomic, strong) NSArray *children;

/**
 SideMenuControllerItem view controller
 */
@property (nonatomic, strong, readonly) UIViewController <APSideMenuControllerItem> *viewController;

/**
 Cell attributes
 */
@property (nonatomic, strong, readonly) NSDictionary *cellAttributesDictionary;

/**
 Item cell target - optional
 Set using setTarget:action:object: method, object can be nil
 */
@property (nonatomic, weak, readonly) id target;

/**
 Item cell action - optional
 Set using setTarget:action:object: method, object can be nil
 */
@property (nonatomic, readonly) SEL action;

/**
 Item cell action object - optional
 Set using setTarget:action:object: method, object can be nil
 */
@property (nonatomic, strong, readonly) id object;

/**
 Init side menu item
 @param name - name to display on item cell
 @param attributesDict - item cell style atrtributes
 **/
- (id)initWithName:(NSString *)name andStyleAttributes:(NSDictionary *)attributesDict;

/**
 Init side menu item
 @param viewController - view controller that shall be opened when the item cell is selected, pass nil if no view should be presented
 @param name - name to display on item cell
 **/
- (id)initWithViewController:(UIViewController <APSideMenuControllerItem> *)viewController andName:(NSString *)name;

/**
 Init side menu item
 @param viewController - view controller that shall be opened when the item cell is selected, pass nil if no view should be presented
 @param name - name to display on item cell
 @param attributesDict - item cell style atrtributes
 **/
- (id)initWithViewController:(UIViewController <APSideMenuControllerItem> *)viewController andName:(NSString *)name andStyleAttributes:(NSDictionary *)attributesDict;

/**
 Init expandable side menu item
 @param name - name to display on item cell
 @param children - array of side menu items to display in expandable item's submenu
 **/
- (id)initExpandableCellWithName:(NSString *)name andChildren:(NSArray *)children;

/**
 Init expandable side menu item
 @param name - name to display on item cell
 @param attributesDict - item cell style atrtributes
 @param children - array of side menu items to display in expandable item's submenu
 **/
- (id)initExpandableCellWithName:(NSString *)name andChildren:(NSArray *)children andStyleAttributes:(NSDictionary *)attributesDict;

/**
 Set target and action to the item cell
 @param target
 @param action
 @param object - action parameter
 **/
- (void)setTarget:(id)target action:(SEL)action object:(id)object;

@end


