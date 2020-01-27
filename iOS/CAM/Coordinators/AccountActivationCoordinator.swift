//
//  AccountActivationCoordinator.swift
//  CAM
//
//  Created by Egor Brel on 1/22/20.
//

import Foundation

protocol AccountActivationCoordinatorProtocol: Coordinator {
    func finishCAMFlow()
    func finishCoordinatorFlow(result: Bool)
    func popCurrentScreen()
}

class AccountActivationCoordinator: AccountActivationCoordinatorProtocol {
    
    var accountInfo: [String: String]
    weak var navigationController: UINavigationController?
    unowned var pluginDataProvider: PluginDataProviderProtocol
    var closeAction: (() -> Void)?
    var completionHandler: ((Bool) -> Void)?
    
    public init(accountInfo: [String: String],
                navigationController: UINavigationController?,
                pluginDataProvider: PluginDataProviderProtocol,
                closeAction: @escaping () -> Void,
                completion: @escaping (Bool) -> Void) {
        self.accountInfo = accountInfo
        self.navigationController = navigationController
        self.pluginDataProvider = pluginDataProvider
        self.closeAction = closeAction
        self.completionHandler = completion
    }
    
    func start() {
        showCodeActivationScreen()
    }
    
    func showCodeActivationScreen() {
        let controller = ViewControllerFactory.createAccountActivationScreen(pluginDataProvider: pluginDataProvider,
                                                                             accountActivationCoordinator: self)
        navigationController?.pushViewController(controller, animated: true)
    }
    
    func finishCoordinatorFlow(result: Bool) {
        navigationController?.popViewController(animated: true)
        completionHandler?(result)
    }
    
    func finishCAMFlow() {
        closeAction?()
    }
    
    func popCurrentScreen() {
        self.navigationController?.popViewController(animated: true)
    }
}
