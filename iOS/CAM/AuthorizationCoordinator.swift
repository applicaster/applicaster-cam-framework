//
//  AuthorizationCoordinator.swift
//  CAMFramework
//
//  Created by Egor Brel on 4/26/19.
//  Copyright © 2019 Egor Brel. All rights reserved.
//

import UIKit
import ZappPlugins
import ApplicasterSDK

protocol AuthorizationCoordinatorProtocol: Coordinator {
    func showLoginScreen(isCoordinatorRootController: Bool)
    func showSingUpScreen(isCoordinatorRootController: Bool)
    func showResetPasswordScreen()
    func popCurrentScreen()
    func finishAuthorizationFlow(isUserLogged: Bool)
}

class AuthorizationCoordinator: AuthorizationCoordinatorProtocol {

    weak var navigationController: UINavigationController?
    unowned var parentCoordinator: PluginDataProviderProtocol
    var completionHandler: ((Bool) -> Void)?
    
    public init(navigationController: UINavigationController,
                parentCoordinator: PluginDataProviderProtocol,
                completion: @escaping (Bool) -> Void) {
        self.navigationController = navigationController
        self.parentCoordinator = parentCoordinator
        self.completionHandler = completion
    }
    
    // MARK: - AuthorizationCoordinatorProtocol
    
    func start() {
        let dictionary = self.parentCoordinator.getCamDelegate().getPluginConfig()
        switch dictionary[CAMKeys.defaultAuthScreen.rawValue] {
        case "Login":
            showLoginScreen(isCoordinatorRootController: true)
        case "Sign-up":
            showSingUpScreen(isCoordinatorRootController: true)
        default:
            return
        }
    }
    
    func showLoginScreen(isCoordinatorRootController: Bool) {
        let controller = ViewControllerFactory.createLoginScreen(pluginDataProvider: parentCoordinator,
                                                                 isRoot: isCoordinatorRootController,
                                                                 authCoordinator: self)
        navigationController?.pushViewController(controller, animated: true)
    }
    
    func showSingUpScreen(isCoordinatorRootController: Bool) {
        let controller = ViewControllerFactory.createSignUpScreen(pluginDataProvider: parentCoordinator,
                                                                  isRoot: isCoordinatorRootController,
                                                                  authCoordinator: self)
        navigationController?.pushViewController(controller, animated: true)
    }
    
    func showResetPasswordScreen() {
        ZAAppConnector.sharedInstance().analyticsDelegate.trackEvent(event: AnalyticsEvents.launchPasswordResetScreen)
        let controller = ViewControllerFactory.createResetPasswordScreen(pluginDataProvider: parentCoordinator,
                                                                         authCoordinator: self)
        navigationController?.pushViewController(controller, animated: true)
    }
    
    func popCurrentScreen() {
        navigationController?.popViewController(animated: true)
    }
    
    func finishAuthorizationFlow(isUserLogged: Bool) {
        let loggedInValue = isUserLogged == true ? "Yes" : "No"
        let pluginName = ZPPluginManager.pluginModel(.Login)?.pluginName ?? ""
        APAnalyticsManager.setEventUserGenericProperties(["Logged In": loggedInValue,
                                                          "Authentication Provider": pluginName])
        completionHandler?(isUserLogged)
    }
}
