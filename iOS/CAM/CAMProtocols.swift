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

public protocol CAMDelegate: AnyObject {
    func getPluginConfig() -> [String: String]
    func isPurchaseNeeded() -> Bool
    func facebookLogin(userData: (email: String, userId: String), completion: @escaping (LoginResult) -> Void)
    func facebookSignUp(userData: (email: String, userId: String), completion: @escaping (SignupResult) -> Void)
    func login(authData: [String: String], completion: @escaping (LoginResult) -> Void)
    func signUp(authData: [String: String], completion: @escaping (SignupResult) -> Void)
    func resetPassword(data: [String: String], completion: @escaping (Result<Void>) -> Void)
    
    func availableProducts(completion: @escaping (AvailableProductsResult) -> Void)
    func itemPurchased(purchasedItem: PurchasedProduct, completion: @escaping (PurchaseResult) -> Void)
    func itemsRestored(restoredItems: [PurchasedProduct], completion: @escaping (PurchaseResult) -> Void)
    
    func itemName() -> String
    func itemType() -> String
    func purchaseProperties(for productIdentifier: String) -> PurchaseProperties
}

public enum ItemState {
    case purchased
    case restored
    case redeemed
}

open class PurchasedProduct {
    public private(set) var transaction: SKPaymentTransaction
    public private(set) var receipt: Data
    private(set) var redeemCode: String?
    private(set) var state: ItemState = .purchased
    
    init(transaction: SKPaymentTransaction,
         receipt: Data,
         redeemCode: String? = nil,
         state: ItemState) {
        self.transaction = transaction
        self.receipt = receipt
        self.redeemCode = redeemCode
        self.state = state
    }
}
