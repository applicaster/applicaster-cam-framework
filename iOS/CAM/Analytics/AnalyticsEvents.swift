//
//  AnalyticsEvents.swift
//  CAM
//
//  Created by Roman Karpievich on 7/9/19.
//

import Foundation

enum AnalyticsEvents: String {
    case tapStandardLoginButton = "Tap Standard Login Button"
    case standardLoginSuccess = "Standard Login Success"
    case standardLoginFailure = "Standard Login Failure"
    case tapAlternativeLogin = "Tap Alternative Login"
    case alternativaLoginSucess = "Alternative Login Success"
    case alternativaLoginFailure = "Alternative Login Failure"
    case tapStandardSignUpButton = "Tap Standard Sign-Up Button"
    case standardSignUpSuccess = "Standard Sign-Up Success"
    case standardSignUpFailure = "Standard Sign-Up Failure"
    case tapAlternativeSignUp = "Tap Alternative Sign-Up"
    case alternativeSignUpSuccess = "Alternative Sign-Up Success"
    case alternativeSignUpFailure = "Alternative Sign-Up Failure"
    case launchContentGatewayPlugin = "Launch Content Gateway Plugin"
    case contentGatewaySession = "Content Gateway Session"
    case switchToLoginScreen = "Switch to Login Screen"
    case switchToSignUpScreen = "Switch to Sign-Up Screen"
    case launchPasswordResetScreen = "Launch Password Reset Screen"
    case resetPassword = "Reset Password"
    case viewAlert = "View Alert"
    case tapPurchaseButton = "Tap Purchase Button"
    case startPurchase = "Start Purchase"
    case completePurchase = "Complete Purchase"
    case cancelPurchase = "Cancel Purchase"
    case storePurchaseError = "Store Purchase Error"
    case tapRestorePurchaseLink = "Tap Restore Purchase Link"
    case startRestorePurchase = "Start Restore Purchase"
    case completeRestorePurchase = "Complete Restore Purchase"
    case cancelRestorePurchase = "Cancel Restore Purchase"
    case storeRestorePurchaseError = "Store Restore Purchase Error"
}
