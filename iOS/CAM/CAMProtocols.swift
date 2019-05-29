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
    func isEntitlementsValid() -> Bool
    func facebookLogin(userData: (email: String, userId: String), completion: @escaping (CAMResult) -> Void)
    func facebookSignUp(userData: (email: String, userId: String), completion: @escaping (CAMResult) -> Void)
    func login(authData: [(key: String, value: String?)], completion: @escaping (CAMResult) -> Void)
    func signUp(authData: [(key: String, value: String?)], completion: @escaping (CAMResult) -> Void)
    func resetPassword(data: [(key: String, value: String?)], completion: @escaping (CAMResult) -> Void)
    func itemPurchased(item: SKProduct)
    func itemsRestored(items: [SKProduct])
    func availableProducts() -> [Product]
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
