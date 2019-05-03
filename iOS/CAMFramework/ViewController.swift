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

class ViewController: UIViewController, CAMDelegate, CAMConfigProtocol {

    @IBAction func start(_ sender: Any) {
        ContentAccessManager.shared.startFlow(camDelegate: self, camConfigProtocol: self, completion: { (r) in
            print(r)
        })
    }
    func login(authData: Dictionary<String, Any>, completion: (CAMResult) -> Void) {
        
    }
    
    func signUp(authData: Dictionary<String, Any>, completion: (CAMResult) -> Void) {
        
    }
    
    func resetPassword(completion: (CAMResult) -> Void) {
        
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
    
    func getEntitlementsData(completion: ([CAMEntitlementItem]) -> Void) {
        
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

