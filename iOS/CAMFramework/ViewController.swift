//
//  ViewController.swift
//  CAMFramework
//
//  Created by Egor Brel on 4/24/19.
//  Copyright © 2019 Egor Brel. All rights reserved.
//

import UIKit
import StoreKit
import CAM

// swiftlint:disable all

class ViewController: UIViewController, CAMDelegate {
    func availableProducts(completion: @escaping (AvailableProductsResult) -> Void) {
        
    }
    
    func itemPurchased(purchasedItem: PurchasedProduct, completion: @escaping (ProductPurchaseResult) -> Void) {
        
    }
    
    func itemsRestored(restoredItems: [PurchasedProduct], completion: @escaping (ProductPurchaseResult) -> Void) {
        
    }
    
    func facebookSignUp(userData: (email: String, userId: String), completion: @escaping (CAMResult) -> Void) {
        completion(.success)
    }
    
    func facebookLogin(userData: (email: String, userId: String), completion: @escaping (CAMResult) -> Void) {
        completion(.failure(description: "Test"))
    }
    
    func resetPassword(data: [String: String], completion: @escaping (CAMResult) -> Void) {
        completion(.success)
    }
    
    
    var cam: ContentAccessManager?
    
    let myConnector = MyConnector()
    
    
    func login(authData: [String: String], completion: @escaping (CAMResult) -> Void) {
        DispatchQueue.main.asyncAfter(deadline: .now() + .seconds(1), execute: {
            completion(.success)
        })
    }
    
    func signUp(authData: [String: String], completion: @escaping (CAMResult) -> Void) {
        DispatchQueue.main.asyncAfter(deadline: .now() + .seconds(1), execute: {
            completion(.success)
        })
    }
    
    func getPluginConfig() -> Dictionary<String, String> {
        if let path = Bundle.main.path(forResource: "mock", ofType: "json") {
            do {
                let data = try Data(contentsOf: URL(fileURLWithPath: path), options: .mappedIfSafe)
                let jsonResult = try JSONSerialization.jsonObject(with: data, options: .mutableLeaves)
                let dict = jsonResult as! Dictionary<String, String>
                return dict
            } catch {
            
            }
        }
        return Dictionary<String, String>()
    }

    @IBAction func start(_ sender: Any) {
        self.cam = ContentAccessManager(rootViewController: self, camDelegate: self, camFlow: .authAndStorefront) { (r) in
            print(r)
        }
        self.cam?.startFlow()
    }
    
    func itemPurchased(item: SKProduct) {
        
    }
    
    func itemsRestored(items: [SKPaymentTransaction]) {
        
    }
    
    func isTriggerOnAppLaunch() -> Bool {
        return true
    }
    
    func isUserLogged() -> Bool {
        return false
    }
    
    func getDefaultAuthScreen() -> CAMDefaultAuthScreen {
        return .login
    }
    
    func isConfirmationScreenRequired() -> Bool {
        return false
    }
    
    func isPasswordResetRequired() -> Bool {
        return false
    }
    
    func isPurchaseNeeded() -> Bool {
        return false
    }

    override func viewDidLoad() {
        super.viewDidLoad()

    }
    
    override func viewDidAppear(_ animated: Bool) {
        super.viewDidAppear(animated)
    }

}

private extension SKProduct {
    
    convenience init(identifier: String, title: String, description: String, price: String, priceLocale: Locale) {
        self.init()
        self.setValue(identifier, forKey: "productIdentifier")
        self.setValue(title, forKey: "localizedTitle")
        self.setValue(description, forKey: "localizedDescription")
        self.setValue(NSDecimalNumber(string: price), forKey: "price")
        self.setValue(priceLocale, forKey: "priceLocale")
    }
}
