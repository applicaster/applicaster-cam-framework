//
//  AnalyticsEvents.swift
//  CAM
//
//  Created by Roman Karpievich on 7/9/19.
//

import Foundation
import StoreKit
import ZappPlugins

private enum PlayableItemInfoKeys: String {
    case name = "Content Entity Name"
    case type = "Content Entity Type"
}

struct PlayableItemInfo {
    let name: String
    let type: String
    
    var metadata: [String: String] {
        return [PlayableItemInfoKeys.name.rawValue: self.name,
                PlayableItemInfoKeys.type.rawValue: self.type]
    }
}

private enum ProductPropertiesKeys: String {
    case subscriber = "Subscriber"
    case productName = "Product Name"
    case price = "Price"
    case transactionID = "Transaction ID"
    case productID = "Product ID"
    case subscriptionDuration = "Subscription Duration"
    case purchaseType = "Purchase Type"
    case trialPeriod = "Trial Period"
    
    static var key: String {
        return "Purchase Product Properties"
    }
}

public enum PurchaseEntityType: String {
    case vod = "VOD Item"
    case category = "Category"
    
    var key: String {
        return "Purchase Entity Type"
    }
}

private enum PurchaseType: String {
    case subscription = "Subscription"
    case consumable = "Consumable"
    
    var key: String {
        return "Purchase Type"
    }
}

public struct PurchaseProperties {
    
    private var isSubscriber: Bool
    public var productName: String?
    public var price: String?
    public var transactionID: String?
    private var productID: String
    public var isSubscription: Bool?
    public var subscriptionDuration: String?
    public var trialPeriod: String?
    public var purchaseEntityType: PurchaseEntityType?
    
    var metadata: [String: String] {
        var result: [String: String] = [ProductPropertiesKeys.productID.rawValue: productID]
        
        result[ProductPropertiesKeys.subscriber.rawValue] = isSubscriber ? "Yes" : "No"
        
        if let name = productName {
            result[ProductPropertiesKeys.productName.rawValue] = name
        }
        
        if let price = self.price {
            result[ProductPropertiesKeys.price.rawValue] = price
        }
        
        if let transactionID = self.transactionID {
            result[ProductPropertiesKeys.transactionID.rawValue] = transactionID
        }
        
        var purchaseType: PurchaseType
        
        if let duration = subscriptionDuration {
            purchaseType = .subscription
            result[ProductPropertiesKeys.subscriptionDuration.rawValue] = duration.capitalized
        } else {
            purchaseType = .consumable
        }
        
        result[purchaseType.key] = purchaseType.rawValue
        
        if let type = purchaseEntityType {
            result[type.key] = type.rawValue
        }
        
        if let trial = trialPeriod {
            result[ProductPropertiesKeys.trialPeriod.rawValue] = trial + " Days"
        }
        
        return result
    }
    
    public init(productIdentifier: String, isSubscriber: Bool) {
        self.productID = productIdentifier
        self.isSubscriber = isSubscriber
    }
    
    mutating func update(with skProduct: SKProduct) {
                self.productName = skProduct.localizedTitle
                self.price = skProduct.localizedPrice
                self.productID = skProduct.productIdentifier
    }
    

}

private enum AlertInfoKeys: String {
    case title = "Alert Title"
    case description = "Alert Description"
}

struct AlertInfo {
    let title: String
    let description: String
    let isConfirmation: IsConfirmationAlert
    
    var metadata: [String: String] {
        return isConfirmation.metadata.merge([AlertInfoKeys.title.rawValue: self.title,
                                              AlertInfoKeys.description.rawValue: self.description])
    }
}

private enum TriggerKeys: String {
    case trigger = "Trigger"
}

struct Trigger {
    private let trigger: String
    
    var metadata: [String: String] {
        return [TriggerKeys.trigger.rawValue: trigger]
    }
}

enum ConfirmationAlertTypes: String {
    case purchase = "Purchase"
    case restorePurchase = "Restore Purchase"
    case passwordReset = "Password Reset"
    
    var key: String {
        return "Confirmation Cause"
    }
}

enum IsConfirmationAlert {
    case yes(type: ConfirmationAlertTypes)
    case no
    
    var key: String {
        return "Confirmation Alert"
    }
    
    var metadata: [String: String] {
        switch self {
        case .yes(let type):
            return [key: "Yes",
                    type.key: type.rawValue]
        case .no:
            return [key: "No"]
        }
    }
}

enum AnalyticsEvents {
    case tapStandardLoginButton(PlayableItemInfo)
    case standardLoginSuccess(PlayableItemInfo)
    case standardLoginFailure(PlayableItemInfo)
    case tapAlternativeLogin(PlayableItemInfo)
    case alternativaLoginSucess(PlayableItemInfo)
    case alternativaLoginFailure(PlayableItemInfo)
    case tapStandardSignUpButton(PlayableItemInfo)
    case standardSignUpSuccess(PlayableItemInfo)
    case standardSignUpFailure(PlayableItemInfo)
    case tapAlternativeSignUp(PlayableItemInfo)
    case alternativeSignUpSuccess(PlayableItemInfo)
    case alternativeSignUpFailure(PlayableItemInfo)
    case launchContentGatewayPlugin(Trigger, firstScreen: String, PlayableItemInfo)
    case contentGatewaySession(Trigger, action: String)
    case switchToLoginScreen
    case switchToSignUpScreen
    case launchPasswordResetScreen
    case resetPassword
    case viewAlert(AlertInfo, apiError: String?)
    case tapPurchaseButton(PlayableItemInfo, PurchaseProperties)
    case startPurchase(PlayableItemInfo, PurchaseProperties)
    case completePurchase(PlayableItemInfo, PurchaseProperties)
    case cancelPurchase(PlayableItemInfo, PurchaseProperties)
    case storePurchaseError(Error, PlayableItemInfo, PurchaseProperties)
    case tapRestorePurchaseLink(PlayableItemInfo)
    case startRestorePurchase(PlayableItemInfo)
    case completeRestorePurchase(PlayableItemInfo, [PurchaseProperties])
    case storeRestorePurchaseError(Error, PlayableItemInfo, PurchaseProperties)
    
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
        case .storeRestorePurchaseError: return "Store Restore Purchase Error"
        }
    }
    
    var metadata: [String: Any] {
        var metadata: [String: Any] = ["Plugin Provider": loginPluginName]
        switch self {
        case .tapStandardLoginButton(let info),
             .standardLoginSuccess(let info),
             .standardLoginFailure(let info),
             .tapAlternativeLogin(let info),
             .alternativaLoginSucess(let info),
             .alternativaLoginFailure(let info),
             .tapStandardSignUpButton(let info),
             .standardSignUpSuccess(let info),
             .standardSignUpFailure(let info),
             .tapAlternativeSignUp(let info),
             .alternativeSignUpSuccess(let info),
             .alternativeSignUpFailure(let info):
            metadata = metadata.merge(info.metadata)
        case .launchContentGatewayPlugin(let trigger, let firstScreen, let info):
            metadata = metadata
                .merge(trigger.metadata)
                .merge(["First Screen": firstScreen])
                .merge(info.metadata)
        case .contentGatewaySession(let trigger, let action):
            metadata = metadata
                .merge(trigger.metadata)
                .merge(["Action": action])
        case .switchToLoginScreen,
             .switchToSignUpScreen,
             .launchPasswordResetScreen,
             .resetPassword:
            break
        case .viewAlert(let alert, let apiError):
            metadata = metadata
                .merge(alert.metadata)
                
            if let error = apiError {
                metadata = metadata.merge(["API Error Message": error])
            }
        case .tapPurchaseButton(let info, let voucher),
             .startPurchase(let info, let voucher),
             .completePurchase(let info, let voucher),
             .cancelPurchase(let info, let voucher):
            metadata = metadata
                .merge(info.metadata)
                .merge(voucher.metadata)
        case .storePurchaseError(let error, let info, let voucher),
             .storeRestorePurchaseError(let error, let info, let voucher):
            metadata = metadata
                .merge(["Error Message": error.localizedDescription])
                .merge(info.metadata)
                .merge(voucher.metadata)
            switch error {
            case let skError as SKError:
                metadata = metadata.merge(["Error Code ID": "\(skError.errorCode)"])
            case let nsError as NSError:
                metadata = metadata.merge(["Error Code ID": "\(nsError.code)"])
            default:
                break
            }
        case .tapRestorePurchaseLink(let info),
             .startRestorePurchase(let info):
            metadata = metadata.merge(info.metadata)
        case .completeRestorePurchase(let info, let purchaseProperties):
            metadata = metadata
                .merge(info.metadata)
                .merge([ProductPropertiesKeys.key: purchaseProperties.map({ $0.metadata })])
        }
        
        return metadata
    }
    
    private var loginPluginName: String {
        return ZPPluginManager.pluginModel(.Login)?.pluginName ?? ""
    }
    
    static public func makeViewAlert(from error: Error) -> AnalyticsEvents {
        return AnalyticsEvents.viewAlert(AlertInfo(title: "",
                                                   description: error.localizedDescription,
                                                   isConfirmation: IsConfirmationAlert.no),
                                         apiError: error.localizedDescription)
    }
}
