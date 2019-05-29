//
//  APSupportRequest.h
//  applicaster
//
//  Created by Guy Kogus on 5/01/12.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//

#import "APModel.h"

@class APSupportRequest;
@protocol APSupportRequestDelegate

@required
- (void)modelDidFinishCreate:(APSupportRequest *)request;
- (void)modelDidFailCreate:(APSupportRequest *)request;

@end


@interface APSupportRequest : APModel {
	id<APSupportRequestDelegate> __unsafe_unretained _delegate;
}

@property (nonatomic, unsafe_unretained) id<APSupportRequestDelegate> delegate;
@property (nonatomic, strong, readonly) NSString *emailAddress;
@property (nonatomic, strong, readonly) NSString *name;
@property (nonatomic, strong, readonly) NSString *contactNumber;
@property (nonatomic, strong, readonly) NSString *problemDescription;

- (id)initWithEmailAddress:(NSString*)email
					  name:(NSString*)name
			 contactNumber:(NSString*)contactNumber
		problemDescription:(NSString*)problemDescription
		attachmentFilePath:(NSString*)filePath; //For future use, currently ignored


- (void)submitSupportRequest;

@end
