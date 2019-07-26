//
//  PurchaseProperties.swift
//  CAM
//
//  Created by Roman Karpievich on 7/16/19.
//

import Foundation
import StoreKit

private enum PurchaseType: String {
    case subscription = "Subscription"
    case consumable = "Consumable"
    
    var key: String {
        return "Purchase Type"
    }
}

public enum PurchaseEntityType: String {
    case vod = "VOD Item"
    case category = "Category"
    
    var key: String {
        return "Purchase Entity Type"
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
    
    static var key: String {
        return "Purchase Product Properties"
    }
    
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
