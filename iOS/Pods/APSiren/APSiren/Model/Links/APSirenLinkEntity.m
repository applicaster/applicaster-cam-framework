//
//  APSirenLinkEntity.m
//  SirenParser
//
//  Created by Anton Kononenko on 3/12/15.
//  Copyright (c) 2015 Anton Kononenko. All rights reserved.
//

#import "APSirenLinkEntity.h"
#import "NSObject+APSirenAdditions.h"
#import "NSArray+APSirenAdditions.h"

@implementation APSirenLinkEntity

- (NSString *)debugDescription {
    return [NSString stringWithFormat:@"<entity:%@, title: %@, link: %@>",self, self.title, self.hRef];
}

#pragma mark - Custom setters

-(void)setTitle:(NSString *)title {
    _title = nil;
    if ([title isNotEmpty] && [title isKindOfClass:[NSString class]]) {
        _title = title;
    }
}

-(void)setRelations:(NSArray *)relations {
    _relations = nil;
    if ([relations isNotEmpty] && [relations isKindOfClass:[NSArray class]]) {
       _relations = [NSArray arrayWithArray:relations expectedClassInObjects:[NSString class]];
    }
}

- (void)setHRef:(NSString *)hRef {
    _hRef = nil;
    if ([hRef isNotEmpty] && [hRef isKindOfClass:[NSString class]]) {
        _hRef = hRef;
    }
}

#pragma mark - Helpers methods
//TODO:Change to isNotEmpty Entity
-(BOOL)emptyEntity {
    BOOL retVal = YES;
    if (self.title ||
            self.hRef ||
            self.relations) {
        retVal = NO;
    }
    return retVal;
}

#pragma mark - NSCoding

- (id)initWithCoder:(NSCoder *)decoder {
    if (self = [super init]) {
        self.title = [decoder decodeObjectForKey:@"title"];
        self.relations = [decoder decodeObjectForKey:@"relations"];
        self.hRef = [decoder decodeObjectForKey:@"hRef"];
    }
    return self;
}

- (void)encodeWithCoder:(NSCoder *)encoder {
    [encoder encodeObject:_title forKey:@"title"];
    [encoder encodeObject:_relations forKey:@"relations"];
    [encoder encodeObject:_hRef forKey:@"hRef"];

}


@end
