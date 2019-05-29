//
//  CREPGViewController.h
//  Caracol
//
//  Created by dan g / applicaster on 7/23/13.
//  Copyright (c) 2013 Applicaster. All rights reserved.

/**
 EPG view controller display all programs by channel per day
 */
@interface APEPGViewController : UIViewController <UICollectionViewDataSource, UICollectionViewDelegate>

/**
 Current page is index of the display day. today is 0 ,tomorrow is one, etc.
 */
@property (assign, nonatomic) NSInteger currentPage;

/**
 Array of objects of APEPGDay which has day name and date.
 */
@property (strong, nonatomic) NSArray *daysOfTheWeek; 

/**
 All programs of a specific day. this dictionary contains array of program per day and the key is the index of the day
 */
@property (strong, nonatomic) NSMutableDictionary *programsByDay; 

/**
 The current channel which initialize and the method setChannelWithId
 */
@property (strong, nonatomic) APChannel *channel; 

/**
 Set program line spacing in collection view flow layout
 */
@property (assign, nonatomic) CGFloat programsLineSpacing;

/**
 Programs collection view (in bottom)
 */
@property (weak, nonatomic) IBOutlet UICollectionView *collectionViewPrograms;

/**
 Days collection view (in top)
 */
@property (weak, nonatomic) IBOutlet UICollectionView *collectionViewDays;

/**
 Spinner when loading new day
 */
@property (weak, nonatomic) IBOutlet UIActivityIndicatorView *spinner;

/**
 Default is NO.
 If set to YES, will force reload the programs from server and ignore the cache.
 */
@property (nonatomic, assign) BOOL forceReloadOfPrograms;

/**
 EPG can show future programs and also past programs.
 */
@property (assign, nonatomic) BOOL showOnlyFuturePrograms;

@property (strong, nonatomic) UICollectionViewFlowLayout *collectionFlowLayoutDays;
@property (strong, nonatomic) UICollectionViewFlowLayout *collectionFlowLayoutProgram;

- (id)initWithChannelID:(NSString *)channelID withCellDayNib:(NSString *)dayNibName andCellProgramNib:(NSString *)programNibName andLocal:(NSString *)locale;

/**
 Force EPG to custom the program and day nibs name or only one of them
 If this method not being called the default will be shown
 all params or optionals:
 @param dayNibName - upper collectionView for days xib
 @param programNibName - down collectionView for days xib
 @param local - NSLocale of the name of the day by srtring for example:@"es-CR"
 */
- (void)customCellDayNib:(NSString *)dayNibName andCellProgramNib:(NSString *)programNibName andLocale:(NSString *)local;

/**
 Tell EPG which channel should be parse 
 @param channelId - the channel id in string
 */
- (void)setChannelWithId:(NSString *)channelId;

/**
 If you like to change the collection view flow layout you need to override this method without calling the super
 */
- (void)setupDaysCollectionView;
- (void)setupProgramCollectionView;

- (void)scrollAllCollectionsToTop;

/**
 Set section insets for the Programs collection view flow layout
 */
- (void)setProgramsSectionInsets:(UIEdgeInsets)sectionInsets;

/**
 load all channel's programs by index of day (today is 0, tomorrow is 1 etc)
 */
- (void)fetchProgramsPerDay:(NSInteger)index;

@end
