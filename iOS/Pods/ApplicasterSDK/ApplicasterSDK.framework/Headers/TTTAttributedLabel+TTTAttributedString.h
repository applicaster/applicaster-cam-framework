//
//  TTTAttributedLabel+TTTAttributedString.h
//  ApplicasterSDK
//
//  Created by dan g / applicaster on 1/2/14.
//  Copyright (c) 2014 Applicaster. All rights reserved.
//

#import <TTTAttributedLabel/TTTAttributedLabel.h>

@interface TTTAttributedLabel (TTTAttributedString)

/**
 Generates NSAttributedString from NSString
 
 @param NSString to become NSAttributedString
 
 @discussion sizeThatFitsAttributedString can calculate the size of TTTAttributedLabel instance, however it should get NSAttributedString in order to calculate. in order to get NSAttributedString, we can use the method "setText: afterInheritingLabelAttributesAndConfiguringWithBlock:", However the last method is a block and sometimes we dont want to use a block. for example when using inside UICollectionViewCell and the cell size should be calculated compare to the label size. in this case the block interfare with the flow calculation of the UICollectionView. This method just return the right attributed string for using afterward in the sizeThatFitsAttributedString method. this was tested in ios 7 and ios 6.
 @return NSAttributedString from the given NSString
 
 */
- (NSAttributedString *)getAttributedStringFromString:(NSString *)string;

@end
