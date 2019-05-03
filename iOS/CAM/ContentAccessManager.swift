//
//  ContentAccessManager.swift
//  CAMFramework
//
//  Created by Egor Brel on 4/25/19.
//  Copyright © 2019 Egor Brel. All rights reserved.
//

import UIKit

protocol PluginDataProviderProtocol: AnyObject {
    func getConfigProvider() -> CAMConfigProtocol
    func getCamDelegate() -> CAMDelegate
}

protocol Coordinator {
    func start(navigationController: UINavigationController, parentCoordinator: PluginDataProviderProtocol, completion: @escaping (Bool) -> Void)
}

public class ContentAccessManager {
    
    var navigationController = UINavigationController()
    var completion: ((Bool) -> Void)!
    weak var configProvider: CAMConfigProtocol!
    weak var delegate: CAMDelegate!
    var childCoordinator: Coordinator?
    
    public static let shared = ContentAccessManager()
    
    private init() {
    }
    
    public func startFlow(camDelegate: CAMDelegate, camConfigProtocol: CAMConfigProtocol, completion: @escaping (Bool) -> Void) {
        self.delegate = camDelegate
        self.configProvider = camConfigProtocol
        self.completion = completion
        if configProvider.isUserLogged() {
            checkUserAccess()
        } else {
            authorize()
        }
    }
    
    func authorize() {
        UIViewController.topMostViewController?.present(navigationController, animated: true, completion: nil)
        childCoordinator = AuthorizationCoordinator()
        childCoordinator?.start(navigationController: self.navigationController, parentCoordinator: self, completion: { [weak self] (isUserLogged) in
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
        if self.configProvider.isEntitlementsValid() {
            finishFlow(true)
        } else {
            if navigationController.parent == nil {
                UIViewController.topMostViewController?.present(navigationController, animated: true, completion: nil)
            }
        }
    }
    
    func finishFlow(_ result: Bool) {
        navigationController.viewControllers.removeAll()
        self.navigationController.dismiss(animated: true, completion: {
            self.completion(result)
        })
    }

}

extension ContentAccessManager: PluginDataProviderProtocol {
    
    func getConfigProvider() -> CAMConfigProtocol {
        return configProvider
    }
    
    func getCamDelegate() -> CAMDelegate {
        return delegate
    }
}
