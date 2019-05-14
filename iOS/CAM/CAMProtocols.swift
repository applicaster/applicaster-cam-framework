//
//  CAMLoginPluginProtocol.swift
//  CAMFramework
//
//  Created by Egor Brel on 4/24/19.
//  Copyright © 2019 Egor Brel. All rights reserved.
//

import Foundation
import StoreKit

public enum CAMDefaultAuthScreen {
    case login
    case registration
}

public enum CAMResult {
    case success
    case failure(description: String?)
}

public struct Product {
    public let title: String
    public let description: String
    public let price: String
    public let skProduct: SKProduct
    
    public init(title: String, description: String, price: String, skProduct: SKProduct) {
        self.title = title
        self.description = description
        self.price = price
        self.skProduct = skProduct
    }
}

public protocol CAMDelegate: AnyObject {
    func login(authData: Dictionary<String, Any>, completion: (CAMResult) -> Void)
    func signUp(authData: Dictionary<String, Any>, completion: (CAMResult) -> Void)
    func resetPassword(completion: (CAMResult) -> Void)
    func itemPurchased(item: SKProduct)
    func itemsRestored(items: [SKProduct])
    func availableProducts() -> [Product]
}

public protocol CAMConfigProtocol: AnyObject {
    func isTriggerOnAppLaunch() -> Bool
    func isUserLogged() -> Bool
    func getDefaultAuthScreen() -> CAMDefaultAuthScreen
    func isConfirmationScreenRequired() -> Bool
    func isPasswordResetRequired() -> Bool
    func getEntitlementsData(completion: ([CAMEntitlementItem]) -> Void)
    func isEntitlementsValid() -> Bool
}
