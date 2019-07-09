//
//  ViewControllerFactory.swift
//  CAM
//
//  Created by Egor Brel on 5/10/19.
//

import UIKit

class ViewControllerFactory {
    
    static func createLoginScreen(pluginDataProvider: PluginDataProviderProtocol,
                                  isRoot: Bool,
                                  authCoordinator: AuthorizationCoordinatorProtocol) -> LoginViewController {
        let loginVC = LoginViewController.instantiateVC()
        let presenter = LoginPresenter(view: loginVC,
                                       coordinatorDelegate: authCoordinator,
                                       camDelegate: pluginDataProvider.getCamDelegate())
        presenter.isRoot = isRoot
        
        loginVC.presenter = presenter
        
        return loginVC
    }
    
    static func createSignUpScreen(pluginDataProvider: PluginDataProviderProtocol?,
                                   isRoot: Bool,
                                   authCoordinator: AuthorizationCoordinatorProtocol) -> SignUpViewController {
        let signUpVC = SignUpViewController.instantiateVC()
        let presenter = SignUpPresenter()
        signUpVC.presenter = presenter
        
        presenter.view = signUpVC
        presenter.coordinatorDelegate = authCoordinator
        presenter.camDelegate = pluginDataProvider?.getCamDelegate()
        presenter.isRoot = isRoot
        return signUpVC
    }
    
    static func createResetPasswordScreen(pluginDataProvider: PluginDataProviderProtocol?,
                                          authCoordinator: AuthorizationCoordinatorProtocol) -> ResetPasswordViewController {
        let resetPasswordVC = ResetPasswordViewController.instantiateVC()
        let presenter = ResetPasswordPresenter()
        resetPasswordVC.presenter = presenter
        
        presenter.view = resetPasswordVC
        presenter.coordinatorDelegate = authCoordinator
        presenter.camDelegate = pluginDataProvider?.getCamDelegate()
        return resetPasswordVC
    }
    
    static func createEntitlementPicker(pluginDataProvider: PluginDataProviderProtocol?,
                                        billingCoordinator: BillingCoordinatorProtocol) -> EntitlementPickerViewController {
        let pickerVC = EntitlementPickerViewController.instantiateVC()
        let presenter = EntitlementPickerPresenter()
        pickerVC.presenter = presenter
    
        presenter.coordinatorDelegate = billingCoordinator
        presenter.camDelegate = pluginDataProvider?.getCamDelegate()
        presenter.view = pickerVC
        return pickerVC
    }
}
