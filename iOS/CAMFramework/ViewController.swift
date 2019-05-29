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
    func resetPassword(data: [(key: String, value: String?)], completion: @escaping (CAMResult) -> Void) {
        completion(.success)
    }
    
    
    var cam: ContentAccessManager?
    
    let myConnector = MyConnector()
    
    
    func login(authData: [(key: String, value: String?)], completion: @escaping (CAMResult) -> Void) {
        DispatchQueue.main.asyncAfter(deadline: .now() + .seconds(1), execute: {
            completion(.success)
        })
    }
    
    func signUp(authData: [(key: String, value: String?)], completion: @escaping (CAMResult) -> Void) {
        DispatchQueue.main.asyncAfter(deadline: .now() + .seconds(1), execute: {
            completion(.success)
        })
    }
    
    func getPluginConfig() -> Dictionary<String, String> {
        if let path = Bundle.main.path(forResource: "mockJson", ofType: "json") {
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
        self.cam = ContentAccessManager(rootViewController: self, camDelegate: self) { (r) in
            print(r)
        }
        self.cam?.startFlow()
    }
    
    func itemPurchased(item: SKProduct) {
        
    }
    
    func itemsRestored(items: [SKPaymentTransaction]) {
        
    }
    
    func availableProducts() -> [Product] {
//        let title = "Monthly Subscription Monthly Subscription Monthly Subscription"
        let title = "Monthly Subscription Subscription"
        let description = "Subscription details go here and might take up to two lines maximum"
        let price = "4.99"
        let skProduct = SKProduct()
        let product = Product(title: title,
                              description: description,
                              price: price,
                              skProduct: skProduct)
        return Array(repeating: product, count: 3)
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
    
    func getEntitlementsData(completion: @escaping ([CAMEntitlementItem]) -> Void) {
        
    }
    
    func isEntitlementsValid() -> Bool {
        return false
    }

    override func viewDidLoad() {
        super.viewDidLoad()

    }
    
    override func viewDidAppear(_ animated: Bool) {
        super.viewDidAppear(animated)
    }

}
