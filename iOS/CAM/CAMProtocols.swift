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

public enum AvailableProductsResult {
    case success(products: [String])
    case failure(description: String?)
}

public enum ProductPurchaseResult {
    case success
    case failure(description: String?)
}

public protocol CAMDelegate: AnyObject {
    func getPluginConfig() -> [String: String]
    func isPurchaseNeeded() -> Bool
    func facebookLogin(userData: (email: String, userId: String), completion: @escaping (CAMResult) -> Void)
    func facebookSignUp(userData: (email: String, userId: String), completion: @escaping (CAMResult) -> Void)
    func login(authData: [String: String], completion: @escaping (CAMResult) -> Void)
    func signUp(authData: [String: String], completion: @escaping (CAMResult) -> Void)
    func resetPassword(data: [String: String], completion: @escaping (CAMResult) -> Void)
    
    func availableProducts(completion: @escaping (AvailableProductsResult) -> Void)
    func itemPurchased(purchasedItem: PurchasedProduct, completion: @escaping (ProductPurchaseResult) -> Void)
    func itemsRestored(restoredItems: [PurchasedProduct], completion: @escaping (ProductPurchaseResult) -> Void)
    
}

public enum ItemState {
    case purchased
    case restored
    case redeemed
}

open class PurchasedProduct {
    public var transaction: SKPaymentTransaction?
    public var product: SKProduct?
    public var receipt: String?
    public var redeemCode: String?
    public var state: ItemState = .purchased
}
