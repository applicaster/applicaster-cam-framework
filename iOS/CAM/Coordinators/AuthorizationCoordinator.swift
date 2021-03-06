//
//  AuthorizationCoordinator.swift
//  CAMFramework
//
//  Created by Egor Brel on 4/26/19.
//  Copyright © 2019 Egor Brel. All rights reserved.
//

import UIKit
import ZappPlugins

enum AuthorizationCoordinatorFlow {
    case auth
    case logout
}

protocol AuthorizationCoordinatorProtocol: Coordinator {
    func showLoginScreen(isCoordinatorRootController: Bool)
    func showSingUpScreen(isCoordinatorRootController: Bool)
    func startResetPasswordFlow()
    func popCurrentScreen()
    func finishCoordinatorFlow(result: Bool)
    func finishAuthentification(result: Bool, userData: [String: String]?)
}

class AuthorizationCoordinator: AuthorizationCoordinatorProtocol {

    var childCoordinator: Coordinator?
    var coordinatorFlow: AuthorizationCoordinatorFlow = .auth
    weak var rootViewController: UIViewController?
    weak var navigationController: UINavigationController?
    unowned var parentCoordinator: PluginDataProviderProtocol
    var completionHandler: ((Bool) -> Void)?
    
    var isResetPasswordCodeActivationEnabled: Bool {
        let configDictionary = parentCoordinator.getCamDelegate().getPluginConfig()
        return configDictionary[CAMKeys.resetPasswordCodeActivationEnabled.rawValue] == true.description ? true : false
    }
    
    var isAccountActivationEnabled: Bool {
        let configDictionary = parentCoordinator.getCamDelegate().getPluginConfig()
        return configDictionary[CAMKeys.signUpActivationCodeEnabled.rawValue] == true.description ? true : false
    }
    
    public init(navigationController: UINavigationController? = nil,
                parentCoordinator: PluginDataProviderProtocol,
                rootViewController: UIViewController? = nil,
                flow: AuthorizationCoordinatorFlow,
                completion: @escaping (Bool) -> Void) {
        self.coordinatorFlow = flow
        self.rootViewController = rootViewController
        self.navigationController = navigationController
        self.parentCoordinator = parentCoordinator
        self.completionHandler = completion
    }
    
    // MARK: - AuthorizationCoordinatorProtocol
    
    func start() {
        switch coordinatorFlow {
        case .auth:
            startAuthFlow()
        case .logout:
            startLogoutFlow()
        }
    }
    
    func startAuthFlow() {
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
    
    func startLogoutFlow() {
        showLogoutScreen()
    }
    
    func startAccountActivationFlow(userData: [String: String]) {
        showAccountActivationScreen(userData: userData)
    }
    
    func startResetPasswordFlow() {
        let closeAction = { [unowned self] in
            self.childCoordinator = nil
            self.finishCoordinatorFlow(result: false)
        }
        guard let loginVC = navigationController?.topViewController else {
            return
        }
        childCoordinator = ResetPasswordCoordinator(parentViewController: loginVC,
                                                    navigationController: navigationController,
                                                    pluginDataProvider: parentCoordinator,
                                                    closeAction: closeAction,
                                                    completion: { [unowned self] in
            self.childCoordinator = nil
        })
        childCoordinator?.start()
    }
    
    func showLoginScreen(isCoordinatorRootController: Bool) {
        let controller = ViewControllerFactory.createLoginScreen(pluginDataProvider: parentCoordinator,
                                                                 isRoot: isCoordinatorRootController,
                                                                 authCoordinator: self)
        navigationController?.pushViewController(controller, animated: true)
    }
    
    func showLogoutScreen() {
        let controller = ViewControllerFactory.createLogoutScreen(pluginDataProvider: parentCoordinator,
                                                                  authCoordinator: self)
        self.rootViewController?.addChildViewController(controller)
    }
    
    func showSingUpScreen(isCoordinatorRootController: Bool) {
        let controller = ViewControllerFactory.createSignUpScreen(pluginDataProvider: parentCoordinator,
                                                                  isRoot: isCoordinatorRootController,
                                                                  authCoordinator: self)
        navigationController?.pushViewController(controller, animated: true)
    }
    
    func showAccountActivationScreen(userData: [String: String]) {
        let controller = ViewControllerFactory.createAccountActivationScreen(userData: userData,
                                                                             pluginDataProvider: parentCoordinator,
                                                                             authorizationCoordinator: self)
        navigationController?.pushViewController(controller, animated: true)
    }
    
    func popCurrentScreen() {
        navigationController?.popViewController(animated: true)
    }
    
    func finishAuthentification(result: Bool, userData: [String : String]?) {
        if isAccountActivationEnabled && !parentCoordinator.getCamDelegate().isUserActivated() {
            startAccountActivationFlow(userData: userData ?? [String: String]())
        } else {
            finishCoordinatorFlow(result: result)
        }
    }
    
    func finishCoordinatorFlow(result: Bool) {
        switch coordinatorFlow {
        case .auth:
            let loggedInValue = result == true ? "Yes" : "No"
            let pluginName = ZPPluginManager.pluginModel(.Login)?.pluginName ?? ""
            
            ZAAppConnector.sharedInstance().pluginsDelegate?.analyticsPluginsManager?.setEventUserGenericProperties(["Logged In": loggedInValue,
            "Authentication Provider": pluginName])
        case .logout:
            break
        }
        completionHandler?(result)
    }
}
