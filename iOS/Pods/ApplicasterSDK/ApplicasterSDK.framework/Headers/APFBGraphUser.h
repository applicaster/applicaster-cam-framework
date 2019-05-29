//
//  APFBGraphUser.h
//  ApplicasterSDK
//
//  Created by Miri Vecselboim on 20/7/15.
//  Copyright (c) 2014 Applicaster. All rights reserved.
//

#import <Foundation/Foundation.h>

@interface APFBGraphUser : NSObject
{
    NSMutableDictionary *_object;
}

/*!
 User's objectID.
 */
@property (retain, nonatomic) NSString *objectID;

/*!
 User's full name.
 */
@property (retain, nonatomic) NSString *name;

/*!
 User's first name.
 */
@property (retain, nonatomic) NSString *first_name;

/*!
 User's last name.
 */
@property (retain, nonatomic) NSString *last_name;

/*!
 User's profile URL.
 */
@property (retain, nonatomic) NSString *link;

/*!
 User's email.
 */
@property (retain, nonatomic) NSString *email;

/*!
 User's image.
 */
@property (retain, nonatomic) NSString *avatarImageUrl;

/*!
 @param user dictionary.
 */
- (instancetype)initWithDictionary:(NSDictionary *)dictionary;

/*!
 Used to compare two `APFBGraphUser`s to determine if represent the same object.
 @param user - an `APFBGraphUser` to test
 @param anotherUser - the `APFBGraphUser` to compare it against
 */
+ (BOOL)isGraphUserID:(APFBGraphUser *)user sameAs:(APFBGraphUser *)anotherUser;

@end