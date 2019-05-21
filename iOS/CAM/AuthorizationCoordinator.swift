//
//  AuthorizationCoordinator.swift
//  CAMFramework
//
//  Created by Egor Brel on 4/26/19.
//  Copyright © 2019 Egor Brel. All rights reserved.
//

import UIKit

protocol AuthorizationCoordinatorProtocol: AnyObject {
    func showLoginScreen(isCoordinatorRootController: Bool)
    func showSingUpScreen(isCoordinatorRootController: Bool)
    func showResetPasswordScreen()
    func popCurrentScreen()
    func finishAuthorizationFlow(isUserLogged: Bool)
}

class AuthorizationCoordinator: AuthorizationCoordinatorProtocol, Coordinator {

    weak var parentCoordinator: PluginDataProviderProtocol?
    weak var navigationController: UINavigationController?
    var completionHandler: ((Bool) -> Void)?
    
    func start(navigationController: UINavigationController, parentCoordinator: PluginDataProviderProtocol, completion: @escaping (Bool) -> Void) {
        self.completionHandler = completion
        self.parentCoordinator = parentCoordinator
        self.navigationController = navigationController
        let dictionary = parentCoordinator.getCamDelegate().getPluginConfig()
        switch dictionary[CAMKeys.defaultAuthScreen.rawValue] as? String {
        case "login":
            showLoginScreen(isCoordinatorRootController: true)
        case "registration":
            showSingUpScreen(isCoordinatorRootController: true)
        default:
            return
        }
    }
    
    func showLoginScreen(isCoordinatorRootController: Bool) {
        let controller = ViewControllerFactory.createLoginScreen(pluginDataProvider: parentCoordinator, isRoot: isCoordinatorRootController, authCoordinator: self)
        navigationController?.pushViewController(controller, animated: true)
    }
    
    func showSingUpScreen(isCoordinatorRootController: Bool) {
        let controller = ViewControllerFactory.createSignUpScreen(pluginDataProvider: parentCoordinator, isRoot: isCoordinatorRootController, authCoordinator: self)
        navigationController?.pushViewController(controller, animated: true)
    }
    
    func showResetPasswordScreen() {
        let controller = ViewControllerFactory.createResetPasswordScreen(pluginDataProvider: parentCoordinator, authCoordinator: self)
        navigationController?.pushViewController(controller, animated: true)
    }
    
    func popCurrentScreen() {
        navigationController?.popViewController(animated: true)
    }
    
    func finishAuthorizationFlow(isUserLogged: Bool) {
        completionHandler?(isUserLogged)
    }
}
