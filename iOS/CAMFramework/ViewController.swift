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

class ViewController: UIViewController, CAMDelegate {
    func resetPassword(email: String, completion: @escaping (CAMResult) -> Void) {
        completion(.success)
    }
    
    func login(authData: [(key: String, value: String?)], completion: @escaping (CAMResult) -> Void) {
        DispatchQueue.main.asyncAfter(deadline: .now() + .seconds(4), execute: {
            completion(.success)
        })
    }
    
    func signUp(authData: [(key: String, value: String?)], completion: @escaping (CAMResult) -> Void) {
        
    }
    
    func getPluginConfig() -> Dictionary<String, Any> {
        if let path = Bundle.main.path(forResource: "mockJson", ofType: "json") {
            do {
                let data = try Data(contentsOf: URL(fileURLWithPath: path), options: .mappedIfSafe)
                let jsonResult = try JSONSerialization.jsonObject(with: data, options: .mutableLeaves)
                let dict = jsonResult as! Dictionary<String, Any>
                return dict
            } catch {
            
            }
        }
        return Dictionary<String, Any>()
    }
    

    @IBAction func start(_ sender: Any) {
        ContentAccessManager.shared.startFlow(rootViewController: self, camDelegate: self, completion: { (r) in
            print(r)
        })
    }
    
    func itemPurchased(item: SKProduct) {
        
    }
    
    func itemsRestored(items: [SKProduct]) {
        
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

