//
//  ResetPasswordCoordinator.swift
//  CAM
//
//  Created by Egor Brel on 1/29/20.
//
import Foundation
import ZappPlugins

protocol ResetPasswordCoordinatorProtocol: Coordinator {
    func finishCoordinatorFlow()
    func showUpdatePasswordScreen(userData: [String: String])
    func popCurrentScreen()
    func close()
}

class ResetPasswordCoordinator: ResetPasswordCoordinatorProtocol {
    
    unowned var parentViewController: UIViewController
    weak var navigationController: UINavigationController?
    unowned var pluginDataProvider: PluginDataProviderProtocol
    var closeAction: () -> Void
    var completion: () -> Void
    
    public init(parentViewController: UIViewController,
                navigationController: UINavigationController?,
                pluginDataProvider: PluginDataProviderProtocol,
                closeAction: @escaping () -> Void,
                completion: @escaping () -> Void) {
        self.parentViewController = parentViewController
        self.navigationController = navigationController
        self.pluginDataProvider = pluginDataProvider
        self.completion = completion
        self.closeAction = closeAction
    }
    
    func start() {
        showResetPasswordScreen()
    }
    
    func showResetPasswordScreen() {
        ZAAppConnector.sharedInstance().analyticsDelegate.trackEvent(event: AnalyticsEvents.launchPasswordResetScreen)
        let controller = ViewControllerFactory.createResetPasswordScreen(pluginDataProvider: pluginDataProvider,
                                                                         resetPasswordCoordinator: self)
        navigationController?.pushViewController(controller, animated: true)
    }
    
    func showUpdatePasswordScreen(userData: [String: String]) {
        let controller = ViewControllerFactory.createUpdatePasswordScreen(userData: userData,
                                                                          pluginDataProvider: pluginDataProvider,
                                                                          resetPasswordCoordinator: self)
        navigationController?.pushViewController(controller, animated: true)
    }
    
    func popCurrentScreen() {
        navigationController?.popViewController(animated: true)
    }
    
    func finishCoordinatorFlow() {
        navigationController?.popToViewController(parentViewController, animated: true)
        completion()
    }
    
    func close() {
        closeAction()
    }
}
