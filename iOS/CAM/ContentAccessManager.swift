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
    func start()
}

open class ContentAccessManager {
    
    private var navigationController: UINavigationController
    private var completion: (Bool) -> Void
    private weak var delegate: CAMDelegate!
    private weak var rootViewController: UIViewController!
    private var childCoordinator: Coordinator?
    
    public init(rootViewController: UIViewController,
                camDelegate: CAMDelegate,
                completion: @escaping (Bool) -> Void) {
        self.rootViewController = rootViewController
        self.delegate = camDelegate
        self.completion = completion
        self.navigationController = UINavigationController()
        self.navigationController.isNavigationBarHidden = true
    }
    
    public func startFlow() {
        if delegate.isUserLogged() {
            checkUserAccess()
        } else {
            authorize()
        }
    }
    
    // MARK: - Private methods
    
    private func authorize() {
        let authorizeCompletion: (Bool) -> Void = { [weak self] (isUserLogged) in
            self?.childCoordinator = nil
            self?.navigationController.setViewControllers([], animated: false)
            if isUserLogged {
                self?.checkUserAccess()
            } else {
                self?.finishFlow(false)
            }
        }
        rootViewController.present(navigationController, animated: true, completion: nil)
        childCoordinator = AuthorizationCoordinator(navigationController: self.navigationController,
                                                    parentCoordinator: self,
                                                    completion: authorizeCompletion)
        childCoordinator!.start()
    }
    
    private func checkUserAccess() {
        if delegate.isEntitlementsValid() {
            finishFlow(true)
        } else {
            if navigationController.presentingViewController == nil {
                rootViewController.present(navigationController, animated: true, completion: nil)
            }
            purchaseEntitlement()
        }
    }
    
    private func purchaseEntitlement() {
        let purchaseCompletion: (Bool) -> Void = { [weak self] (isUserHasAccess) in
            self?.childCoordinator = nil
            self?.finishFlow(isUserHasAccess)
        }
        
        childCoordinator = BillingCoordinator(navigationController: navigationController,
                                              parentCoordinator: self,
                                              completion: purchaseCompletion)
        childCoordinator!.start()
    }
    
    private func finishFlow(_ result: Bool) {
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
