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
    func getPluginConfig() -> Dictionary<String, Any>
    func isUserLogged() -> Bool
    func isEntitlementsValid() -> Bool
    func login(authData: Dictionary<String, Any>, completion: (CAMResult) -> Void)
    func signUp(authData: Dictionary<String, Any>, completion: (CAMResult) -> Void)
    func resetPassword(completion: (CAMResult) -> Void)
    func itemPurchased(item: SKProduct)
    func itemsRestored(items: [SKProduct])
}
