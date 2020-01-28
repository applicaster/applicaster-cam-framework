//
//  AccountActivationCoordinator.swift
//  CAM
//
//  Created by Egor Brel on 1/22/20.
//

import Foundation

protocol AccountActivationCoordinatorProtocol: Coordinator {
    func finishCoordinatorFlow(result: Bool)
    func removeCoordinator()
}

class AccountActivationCoordinator: AccountActivationCoordinatorProtocol {
    
    var userData: [String: String]
    weak var navigationController: UINavigationController?
    unowned var pluginDataProvider: PluginDataProviderProtocol
    var backAction: (() -> Void)?
    var completionHandler: ((Bool) -> Void)?
    
    public init(userData: [String: String],
                navigationController: UINavigationController?,
                pluginDataProvider: PluginDataProviderProtocol,
                backAction: @escaping () -> Void,
                completion: @escaping (Bool) -> Void) {
        self.userData = userData
        self.navigationController = navigationController
        self.pluginDataProvider = pluginDataProvider
        self.completionHandler = completion
        self.backAction = backAction
    }
    
    func start() {
        showCodeActivationScreen()
    }
    
    func showCodeActivationScreen() {
        let controller = ViewControllerFactory.createAccountActivationScreen(userData: userData,
                                                                             pluginDataProvider: pluginDataProvider,
                                                                             accountActivationCoordinator: self)
        navigationController?.pushViewController(controller, animated: true)
    }
    
    func finishCoordinatorFlow(result: Bool) {
        completionHandler?(result)
    }
    
    func removeCoordinator() {
        navigationController?.popViewController(animated: true)
        backAction?()
    }
}
