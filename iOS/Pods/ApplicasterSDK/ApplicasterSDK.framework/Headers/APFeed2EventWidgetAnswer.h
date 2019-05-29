//
//  APFeed2EventWidgetAnswer.h
//  applicaster
//
//  Created by Hagit Shemer on 2/10/14.
//  Copyright (c) 2014 Applicaster Ltd. All rights reserved.
//

@interface APFeed2EventWidgetAnswer : NSObject

@property (nonatomic, strong, readonly) NSString *uniqueID;
@property (nonatomic, strong, readonly) NSString *text;
@property (nonatomic, strong, readonly) NSURL *submitURL;

@property (nonatomic, assign, readonly) BOOL isCorrect;
@property (nonatomic, assign, readonly) CGFloat resultFraction;

@property (nonatomic, assign) BOOL isPoll;


/**
 Did the user choose this answer
 */
@property (nonatomic, assign) BOOL userChosen;

-(id)initWithDictionary:(NSDictionary *)dictionary;

@end
