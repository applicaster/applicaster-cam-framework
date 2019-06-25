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
    private var camFlow: CAMFlow
    
    public init(rootViewController: UIViewController,
                camDelegate: CAMDelegate,
                camFlow: CAMFlow,
                completion: @escaping (Bool) -> Void) {
        self.rootViewController = rootViewController
        self.delegate = camDelegate
        self.camFlow = camFlow
        self.completion = completion
        self.navigationController = UINavigationController()
        self.navigationController.isNavigationBarHidden = true
    }
    
    public func startFlow() {
        switch camFlow {
        case .authentication:
            startAuthenticationFlow()
        case .storefront:
            startStorefrontFlow()
        case .authAndStorefront:
            startAuthAndStorefrontFlow()
        case .no:
            completion(true)
        }
    }
    
    // MARK: - Private methods
    
    private func startAuthenticationFlow() {
        if delegate.isUserLogged() == true {
            finishFlow(true)
        } else {
            authenticate { (isUserLogged) in
                self.finishFlow(isUserLogged)
            }
        }
    }
    
    private func startStorefrontFlow() {
        purchase { (isPurchased) in
            self.finishFlow(isPurchased)
        }
    }
    
    private func startAuthAndStorefrontFlow() {
        if delegate.isUserLogged() == true {
            startStorefrontFlow()
        } else {
            authenticate { (isUserLogged) in
                if isUserLogged == true {
                    self.startStorefrontFlow()
                } else {
                    self.finishFlow(false)
                }
            }
        }
    }
    
    private func authenticate(with completion: @escaping (Bool) -> Void) {
        rootViewController.present(navigationController, animated: true, completion: nil)
        childCoordinator = AuthorizationCoordinator(navigationController: self.navigationController,
                                                    parentCoordinator: self,
                                                    completion: completion)
        childCoordinator!.start()
    }
    
    private func purchase(with completion: @escaping (Bool) -> Void) {
        if navigationController.isBeingPresented == false {
            rootViewController.present(navigationController, animated: true, completion: nil)
        }
        
        childCoordinator = BillingCoordinator(navigationController: navigationController,
                                              parentCoordinator: self,
                                              completion: completion)
        childCoordinator!.start()
    }
    
    private func finishFlow(_ result: Bool) {
        childCoordinator = nil
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
