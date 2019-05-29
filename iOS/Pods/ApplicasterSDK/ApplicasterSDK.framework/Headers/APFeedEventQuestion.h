//
//  APFeedEventQuestion.h
//  applicaster
//
//  Created by Liviu Romascanu on 8/1/13.
//  Copyright (c) 2013 Applicaster Ltd. All rights reserved.
//

#import "APFeedEventImage.h"

@interface APFeedEventQuestion : APFeedEventImage

/**
 Answers and Feedback array.
 Example:
 [{feedback:"Yep",wording:"Nijer",id:"516175feae3798751d00000c"},
 {feedback:"meetoo. that is why I asked!.",wording:"dont
 know",id:"516175feae3798751d00000e"}]
 */
@property (nonatomic, strong) NSMutableArray *answers;
@property (nonatomic, strong) NSArray *answerFromServer;
@property (nonatomic, assign) BOOL hasAnswered; 

@end
