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

public protocol CAMDelegate: AnyObject {
    func getPluginConfig() -> [String: String]
    func isUserLogged() -> Bool
    func isPurchaseNeeded() -> Bool
    func facebookLogin(userData: (email: String, userId: String), completion: @escaping (CAMResult) -> Void)
    func facebookSignUp(userData: (email: String, userId: String), completion: @escaping (CAMResult) -> Void)
    func login(authData: [String: String], completion: @escaping (CAMResult) -> Void)
    func signUp(authData: [String: String], completion: @escaping (CAMResult) -> Void)
    func resetPassword(data: [String: String], completion: @escaping (CAMResult) -> Void)
    func itemPurchased(item: SKProduct)
    func itemsRestored(items: [SKPaymentTransaction])
    func availableProducts() -> [Product]
}

public struct Product {
    public let skProduct: SKProduct
    
    public init(skProduct: SKProduct) {
        self.skProduct = skProduct
    }
}
