//
//  PaymentCoordinator.swift
//  CAMFramework
//
//  Created by Egor Brel on 5/3/19.
//  Copyright © 2019 Egor Brel. All rights reserved.
//

import Foundation

protocol BillingCoordinatorProtocol: AnyObject {
    func showRedeemCodeScreen()
    func popCurrentScreen()
    func finishBillingFlow(isUserHasAccess: Bool)
    func showEntitlementPicker()
}

class BillingCoordinator: BillingCoordinatorProtocol, Coordinator {
    weak var parentCoordinator: PluginDataProviderProtocol?
    weak var navigationController: UINavigationController?
    var completionHandler: ((Bool) -> Void)?
    
    func start(navigationController: UINavigationController, parentCoordinator: PluginDataProviderProtocol, completion: @escaping (Bool) -> Void) {
        self.completionHandler = completion
        self.parentCoordinator = parentCoordinator
        self.navigationController = navigationController
        showEntitlementPicker()
    }
    
    func showEntitlementPicker() {
        let controller = ViewControllerFactory.createEntitlementPicker(pluginDataProvider: parentCoordinator, billingCoordinator: self)
        let presenter = EntitlementPickerPresenter()
        controller.presenter = presenter
        
        presenter.coordinatorDelegate = self
        presenter.camDelegate = parentCoordinator?.getCamDelegate()
        presenter.view = controller
        navigationController?.pushViewController(controller, animated: true)
    }
    
    func showRedeemCodeScreen() {
        
    }
    
    func popCurrentScreen() {
        navigationController?.popViewController(animated: true)
    }
    
    func finishBillingFlow(isUserHasAccess: Bool) {
        completionHandler?(isUserHasAccess)
    }
}
