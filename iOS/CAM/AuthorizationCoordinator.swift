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
        switch parentCoordinator.getConfigProvider().getDefaultAuthScreen() {
        case .login:
            showLoginScreen(isCoordinatorRootController: true)
        case .registration:
            showSingUpScreen(isCoordinatorRootController: true)
        }
    }
    
    func showLoginScreen(isCoordinatorRootController: Bool) {
        let loginVC = LoginViewController.instantiateVC()
        let presenter = LoginPresenter()
        loginVC.presenter = presenter
        
        presenter.coordinatorDelegate = self
        presenter.camDelegate = parentCoordinator?.getCamDelegate()
        presenter.isRoot = isCoordinatorRootController
        loginVC.configProvider = parentCoordinator?.getConfigProvider() //setup ui provider
        navigationController?.pushViewController(loginVC, animated: true)
    }
    
    func showSingUpScreen(isCoordinatorRootController: Bool) {
        let signUpVC = SignUpViewController.instantiateVC()
        let presenter = SignUpPresenter()
        signUpVC.presenter = presenter
        
        presenter.coordinatorDelegate = self
        presenter.camDelegate = parentCoordinator?.getCamDelegate()
        presenter.isRoot = isCoordinatorRootController
        signUpVC.configProvider = parentCoordinator?.getConfigProvider() //setup ui provider
        navigationController?.pushViewController(signUpVC, animated: true)
    }
    
    func showResetPasswordScreen() {
        let restoreVC = ResetPasswordViewController.instantiateVC()
        let presenter = ResetPasswordPresenter()
        restoreVC.presenter = presenter
        
        presenter.coordinatorDelegate = self
        presenter.camDelegate = parentCoordinator?.getCamDelegate()
        navigationController?.pushViewController(restoreVC, animated: true)
    }
    
    func popCurrentScreen() {
        navigationController?.popViewController(animated: true)
    }
    
    func finishAuthorizationFlow(isUserLogged: Bool) {
        completionHandler?(isUserLogged)
    }
}
