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
    func login(authData: [(key: String, value: String?)], completion: @escaping (CAMResult) -> Void)
    func signUp(authData: [(key: String, value: String?)], completion: @escaping (CAMResult) -> Void)
    func resetPassword(completion: @escaping (CAMResult) -> Void)
    func itemPurchased(item: SKProduct)
    func itemsRestored(items: [SKProduct])
}
