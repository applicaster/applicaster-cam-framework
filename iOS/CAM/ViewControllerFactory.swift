//
//  ViewControllerFactory.swift
//  CAM
//
//  Created by Egor Brel on 5/10/19.
//

import UIKit

class ViewControllerFactory {
    
    static func createLoginScreen(pluginDataProvider: PluginDataProviderProtocol?, isRoot: Bool, authCoordinator: AuthorizationCoordinatorProtocol) -> LoginViewController {
        let loginVC = LoginViewController.instantiateVC()
        let presenter = LoginPresenter()
        loginVC.presenter = presenter
        
        presenter.coordinatorDelegate = authCoordinator
        presenter.camDelegate = pluginDataProvider?.getCamDelegate()
        presenter.isRoot = isRoot
        return loginVC
    }
    
    static func createSignUpScreen(pluginDataProvider: PluginDataProviderProtocol?, isRoot: Bool, authCoordinator: AuthorizationCoordinatorProtocol) -> SignUpViewController {
        let signUpVC = SignUpViewController.instantiateVC()
        let presenter = SignUpPresenter()
        signUpVC.presenter = presenter
        
        presenter.coordinatorDelegate = authCoordinator
        presenter.camDelegate = pluginDataProvider?.getCamDelegate()
        presenter.isRoot = isRoot
        return signUpVC
    }
    
    static func createResetPasswordScreen(pluginDataProvider: PluginDataProviderProtocol?, authCoordinator: AuthorizationCoordinatorProtocol) -> ResetPasswordViewController {
        let restoreVC = ResetPasswordViewController.instantiateVC()
        let presenter = ResetPasswordPresenter()
        restoreVC.presenter = presenter
        
        presenter.coordinatorDelegate = authCoordinator
        presenter.camDelegate = pluginDataProvider?.getCamDelegate()
        return restoreVC
    }
    
    static func createEntitlementPicker(pluginDataProvider: PluginDataProviderProtocol?, billingCoordinator: BillingCoordinatorProtocol) -> EntitlementPickerViewController {
        let pickerVC = EntitlementPickerViewController.instantiateVC()
        let presenter = EntitlementPickerPresenter()
        pickerVC.presenter = presenter
        
        presenter.coordinatorDelegate = billingCoordinator
        presenter.camDelegate = pluginDataProvider?.getCamDelegate()
        return pickerVC
    }
}
