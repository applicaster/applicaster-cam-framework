//
//  ContentAccessManager.swift
//  CAMFramework
//
//  Created by Egor Brel on 4/25/19.
//  Copyright © 2019 Egor Brel. All rights reserved.
//

import UIKit

protocol PluginDataProviderProtocol: AnyObject {
    func getCamDelegate() -> CAMDelegate
}

protocol Coordinator {
    func start(navigationController: UINavigationController, parentCoordinator: PluginDataProviderProtocol, completion: @escaping (Bool) -> Void)
}

public class ContentAccessManager {
    
    var navigationController = UINavigationController()
    var completion: ((Bool) -> Void)!
    weak var delegate: CAMDelegate!
    weak var rootViewController: UIViewController!
    var childCoordinator: Coordinator?
    
    public static let shared = ContentAccessManager()
    
    private init() {
        self.navigationController.isNavigationBarHidden = true
    }
    
    public func startFlow(rootViewController: UIViewController, camDelegate: CAMDelegate, completion: @escaping (Bool) -> Void) {
        self.rootViewController = rootViewController
        self.delegate = camDelegate
        self.completion = completion
        if delegate.isUserLogged() {
            checkUserAccess()
        } else {
            authorize()
        }
    }
    
    func authorize() {
        rootViewController.present(navigationController, animated: true, completion: nil)
        childCoordinator = AuthorizationCoordinator()
        childCoordinator?.start(navigationController: navigationController, parentCoordinator: self, completion: { [weak self] (isUserLogged) in
            self?.childCoordinator = nil
            self?.navigationController.setViewControllers([], animated: false)
            if isUserLogged {
                self?.checkUserAccess()
            } else {
                self?.finishFlow(false)
            }
        })
    }
    
    func checkUserAccess() {
        if delegate.isEntitlementsValid() {
            finishFlow(true)
        } else {
            if navigationController.presentingViewController == nil {
                rootViewController.present(navigationController, animated: true, completion: nil)
            }
            purchaseEntitlement()
        }
    }
    
    func purchaseEntitlement() {
        childCoordinator = BillingCoordinator()
        childCoordinator?.start(navigationController: navigationController, parentCoordinator: self, completion: { [weak self] (isUserHasAccess) in
            self?.childCoordinator = nil
            self?.finishFlow(isUserHasAccess)
        })
    }
    
    
    func finishFlow(_ result: Bool) {
        navigationController.viewControllers.removeAll()
        self.navigationController.dismiss(animated: true, completion: {
            self.completion(result)
        })
    }

}

extension ContentAccessManager: PluginDataProviderProtocol {
    
    func getCamDelegate() -> CAMDelegate {
        return delegate
    }
}
