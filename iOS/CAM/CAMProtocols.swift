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
    case success(products: [AvailableProduct])
    case failure(description: String?)
}

public enum ProductPurchaseResult {
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
    
    func availableProducts(completion: @escaping (AvailableProductsResult) -> Void)
    func itemPurchased(purchasedItem: PurchasedProduct, completion: @escaping (ProductPurchaseResult) -> Void)
    func itemsRestored(purchasedItem: [PurchasedProduct], completion: @escaping (ProductPurchaseResult) -> Void)
    
}

public struct AvailableProduct {
    let offerID: String
    let appleStoreID: String
    let entitlementID: String //auth id in case of sportsmax
    
    public init(offerID: String, appleStoreID: String, entitlementID: String) {
        self.offerID = offerID
        self.appleStoreID = appleStoreID
        self.entitlementID = entitlementID
    }
}

public enum ItemState {
    case purchased
    case restored
    case redeemed
}

public struct PurchasedProduct {
    let offerID: String
    let entitlementID: String //auth id in case of sportsmax
    let transactionID: String?
    let receipt: String?
    let productID: String?
    let redeemCode: String?
    let state: ItemState
}

