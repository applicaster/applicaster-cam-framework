//
//  AnalyticsEvents.swift
//  CAM
//
//  Created by Roman Karpievich on 7/9/19.
//

import Foundation
import StoreKit

private enum PlayableItemInfoKeys: String {
    case name = "Content Entity Name"
    case type = "Content Entity Type"
}

struct PlayableItemInfo {
    private let name: String
    private let type: String
    
    var metadata: [String: String] {
        return [PlayableItemInfoKeys.name.rawValue: self.name,
                PlayableItemInfoKeys.type.rawValue: self.type]
    }
}

enum VoucherPropertiesKeys: String {
    case subscriber = "Subscriber"
    case voucherName = "Voucher Name"
    case price = "Price"
    case transactionID = "Transaction ID"
    case productID = "Product ID"
    case subscriptionDuration = "Subscription Duration"
    case purchaseType = "Purchase Type"
    case trialPeriod = "Trial Period"
    case purchaseEntityType = "Purchase Entity Type"
    case gracePeriod = "Grace Period"
}

struct VoucherProperties {
    
    var metadata: [String: String] {
        return [:]
    }
}

private enum AlertInfoKeys: String {
    case title = "Alert Title"
    case description = "Alert Description"
}

struct AlertInfo {
    private let title: String
    private let description: String
    
    var metadata: [String: String] {
        return [AlertInfoKeys.title.rawValue: self.title,
                AlertInfoKeys.description.rawValue: self.description]
    }
}

//enum AnalyticsEvents: String {
//    case tapStandardLoginButton = "Tap Standard Login Button"
//    case standardLoginSuccess = "Standard Login Success"
//    case standardLoginFailure = "Standard Login Failure"
//    case tapAlternativeLogin = "Tap Alternative Login"
//    case alternativaLoginSucess = "Alternative Login Success"
//    case alternativaLoginFailure = "Alternative Login Failure"
//    case tapStandardSignUpButton = "Tap Standard Sign-Up Button"
//    case standardSignUpSuccess = "Standard Sign-Up Success"
//    case standardSignUpFailure = "Standard Sign-Up Failure"
//    case tapAlternativeSignUp = "Tap Alternative Sign-Up"
//    case alternativeSignUpSuccess = "Alternative Sign-Up Success"
//    case alternativeSignUpFailure = "Alternative Sign-Up Failure"
//    case launchContentGatewayPlugin = "Launch Content Gateway Plugin"
//    case contentGatewaySession = "Content Gateway Session"
//    case switchToLoginScreen = "Switch to Login Screen"
//    case switchToSignUpScreen = "Switch to Sign-Up Screen"
//    case launchPasswordResetScreen = "Launch Password Reset Screen"
//    case resetPassword = "Reset Password"
//    case viewAlert = "View Alert"
//    case tapPurchaseButton = "Tap Purchase Button"
//    case startPurchase = "Start Purchase"
//    case completePurchase = "Complete Purchase"
//    case cancelPurchase = "Cancel Purchase"
//    case storePurchaseError = "Store Purchase Error"
//    case tapRestorePurchaseLink = "Tap Restore Purchase Link"
//    case startRestorePurchase = "Start Restore Purchase"
//    case completeRestorePurchase = "Complete Restore Purchase"
//    case cancelRestorePurchase = "Cancel Restore Purchase"
//    case storeRestorePurchaseError = "Store Restore Purchase Error"
//}

enum AnalyticsEvents {
    case tapStandardLoginButton(PlayableItemInfo, pluginProvider: String)
    case standardLoginSuccess(PlayableItemInfo, pluginProvider: String)
    case standardLoginFailure(PlayableItemInfo, pluginProvider: String)
    case tapAlternativeLogin(PlayableItemInfo, pluginProvider: String)
    case alternativaLoginSucess(PlayableItemInfo, pluginProvider: String)
    case alternativaLoginFailure(PlayableItemInfo, pluginProvider: String)
    case tapStandardSignUpButton(PlayableItemInfo, pluginProvider: String)
    case standardSignUpSuccess(PlayableItemInfo, pluginProvider: String)
    case standardSignUpFailure(PlayableItemInfo, pluginProvider: String)
    case tapAlternativeSignUp(PlayableItemInfo, pluginProvider: String)
    case alternativeSignUpSuccess(PlayableItemInfo, pluginProvider: String)
    case alternativeSignUpFailure(PlayableItemInfo, pluginProvider: String)
    case launchContentGatewayPlugin(trigger: String, firstScreen: String, PlayableItemInfo, pluginProvider: String)
    case contentGatewaySession(trigger: String, action: String, pluginProvider: String)
    case switchToLoginScreen(pluginProvider: String)
    case switchToSignUpScreen(pluginProvider: String)
    case launchPasswordResetScreen(pluginProvider: String)
    case resetPassword(pluginProvider: String)
    case viewAlert(PlayableItemInfo, pluginProvider: String, AlertInfo, apiError: String)
    case tapPurchaseButton(PlayableItemInfo, pluginProvider: String, VoucherProperties)
    case startPurchase(PlayableItemInfo, pluginProvider: String, VoucherProperties)
    case completePurchase(PlayableItemInfo, pluginProvider: String, VoucherProperties)
    case cancelPurchase(PlayableItemInfo, pluginProvider: String, VoucherProperties)
    case storePurchaseError(SKError, PlayableItemInfo, pluginProvider: String, VoucherProperties)
    case tapRestorePurchaseLink(PlayableItemInfo, pluginProvider: String)
    case startRestorePurchase(PlayableItemInfo, pluginProvider: String)
    case completeRestorePurchase(PlayableItemInfo, pluginProvider: String, VoucherProperties)
    case cancelRestorePurchase(PlayableItemInfo, pluginProvider: String, VoucherProperties)
    case storeRestorePurchaseError(SKError, PlayableItemInfo, pluginProvider: String, VoucherProperties)
    
    var key: String {
        switch self {
        case .tapStandardLoginButton: return "Tap Standard Login Button"
        case .standardLoginSuccess: return "Standard Login Success"
        case .standardLoginFailure: return "Standard Login Failure"
        case .tapAlternativeLogin: return "Tap Alternative Login"
        case .alternativaLoginSucess: return "Alternative Login Success"
        case .alternativaLoginFailure: return "Alternative Login Failure"
        case .tapStandardSignUpButton: return "Tap Standard Sign-Up Button"
        case .standardSignUpSuccess: return "Standard Sign-Up Success"
        case .standardSignUpFailure: return "Standard Sign-Up Failure"
        case .tapAlternativeSignUp: return "Tap Alternative Sign-Up"
        case .alternativeSignUpSuccess: return "Alternative Sign-Up Success"
        case .alternativeSignUpFailure: return "Alternative Sign-Up Failure"
        case .launchContentGatewayPlugin: return "Launch Content Gateway Plugin"
        case .contentGatewaySession: return "Content Gateway Session"
        case .switchToLoginScreen: return "Switch to Login Screen"
        case .switchToSignUpScreen: return "Switch to Sign-Up Screen"
        case .launchPasswordResetScreen: return "Launch Password Reset Screen"
        case .resetPassword: return "Reset Password"
        case .viewAlert: return "View Alert"
        case .tapPurchaseButton: return "Tap Purchase Button"
        case .startPurchase: return "Start Purchase"
        case .completePurchase: return "Complete Purchase"
        case .cancelPurchase: return "Cancel Purchase"
        case .storePurchaseError: return "Store Purchase Error"
        case .tapRestorePurchaseLink: return "Tap Restore Purchase Link"
        case .startRestorePurchase: return "Start Restore Purchase"
        case .completeRestorePurchase: return "Complete Restore Purchase"
        case .cancelRestorePurchase: return "Cancel Restore Purchase"
        case .storeRestorePurchaseError: return "Store Restore Purchase Error"
        }
    }
}
