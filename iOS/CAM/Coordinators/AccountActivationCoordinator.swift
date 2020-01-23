//
//  AccountActivationCoordinator.swift
//  CAM
//
//  Created by Egor Brel on 1/22/20.
//

import Foundation

protocol AccountActivationCoordinatorProtocol: Coordinator {
    func showLoginScreen(isCoordinatorRootController: Bool)
    func showSingUpScreen(isCoordinatorRootController: Bool)
    func showResetPasswordScreen()
    func popCurrentScreen()
    func finishCoordinatorFlow(result: Bool)
}

class AccountActivationCoordinator {
    
    var accountInfo: [String: String]
    weak var navigationController: UINavigationController?
    unowned var parentCoordinator: PluginDataProviderProtocol
    var completionHandler: ((Bool) -> Void)?
    
    public init(accountInfo: [String: String],
                navigationController: UINavigationController,
                parentCoordinator: PluginDataProviderProtocol,
                completion: @escaping (Bool) -> Void) {
        self.accountInfo = accountInfo
        self.navigationController = navigationController
        self.parentCoordinator = parentCoordinator
        self.completionHandler = completion
    }
    
    func start() {
        showCodeActivationScreen()
    }
    
    func showCodeActivationScreen() {
        
    }
    
}
