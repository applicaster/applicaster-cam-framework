//
//  APValidationFlowProtocol.h
//  applicaster
//
//  Created by Anton Kononenko on 9/10/15.
//  Copyright (c) 2015 Applicaster Ltd. All rights reserved.
//

#import <Foundation/Foundation.h>
/**
 *  Type Key to use as part of URL scheme 
 *  @see "&validation_flow_type=number"
 */
static NSString *const kValidationFlowTypeParam = @"validation_flow_type";

typedef void (^ValidationFlowCompletion)(BOOL accessGranted, NSURL *urlScheme);

@protocol APValidationFlowProtocolDelegate;

/**
 *  Protocol created for usage of showing some navigation flow before url scheme will presented
 */
@protocol APValidationFlowProtocol <NSObject>

@required

/**
 *  Base url scheme
 *  @see Should be added before navigation flow will be presented
 */
@property (nonatomic, strong, readonly) NSURL *urlScheme;

/**
 *  Type of Validation flow
 *
 *  @return String type of validation flow
 */
- (NSString *)validationFlowType;

/**
 *  Setter for url scheme
 *
 *  @param urlScheme base url scheme
 *  @see Should be added before navigation flow will be presented
 */
- (void)setUrlScheme:(NSURL *)urlScheme;

/**
 *  Implement this method when navigation flow will grant access to user
 *  @see Example user push on OK button or input passcode
 */
- (void)accessGrantedFromValidationFlow;

/**
 *  Implement this method when navigation flow will reject access to user
 *  @see Example user push on Cancel button or input wrong passcode
 */
- (void)accessRejectedFromValidationFlow;


@optional

/**
 *  Delegate can be used if user do not want to use completion block
 */
@property (nonatomic, weak)id <APValidationFlowProtocolDelegate>delegate;

/**
 *  Present navigation flow with predefined way
 *
 *  @param viewController navigation flow will be added on this ViewController
 *  @param completion     complition block when navigation flow will finish its logic
 *  @param accessGranted  notify user if access was granted for navigation flow
 *  @param urlScheme url scheme
 */
- (void)presentValidationFlowOnTopViewController:(UIViewController *)viewController
                                  withCompletion:(ValidationFlowCompletion)completion;

/**
 *  Present navigation flow with predefined way
 *
 *  @param viewController navigation flow will be added on this ViewController
 *  @see this method can be used with delegate
 */
- (void)presentValidationFlowOnTopViewController:(UIViewController *)viewController;

/**
 *  Removes validation flow from the screen
 * @see Use this method in case you use delegate and show screen with method presentValidationFlowOnTopViewController:
 * @see Other case use custom remove
 *
 */
- (void)dissmisValidationFlow;

@end

@protocol APValidationFlowProtocolDelegate <NSObject>

@required

/**
 *  This method will be called when navigation flow finished it's logic and should be removed from screen
 *
 *  @param validationFlow validation flow instance
 *  @param accessGranted  if user has access from navigation flow
 *  @param urlSchemes     url scheme that should be processed
 */
- (void)validationFlowViewControllerShouldBeDismissed:(id <APValidationFlowProtocol>)validationFlow
                                        accessGranted:(BOOL)accessGranted
                                            urlScheme:(NSURL *) urlSchemes;

@optional

/**
 *  Notify user that navigation flow will present
 *
 *  @param validationFlow validation flow instance
 */
- (void)validationFlowViewControllerWillPresent:(id <APValidationFlowProtocol>)validationFlow;

/**
 *  Notify user that navigation flow did present
 *
 *  @param validationFlow validation flow instance
 */
- (void)validationFlowViewControllerDidPresent:(id <APValidationFlowProtocol>)validationFlow;



@end
