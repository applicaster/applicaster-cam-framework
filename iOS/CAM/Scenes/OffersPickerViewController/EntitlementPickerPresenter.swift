//
//  EntitlementsPickerPresenter.swift
//  CAMFramework
//
//  Created by Egor Brel on 5/3/19.
//  Copyright © 2019 Egor Brel. All rights reserved.
//

import Foundation

class EntitlementPickerPresenter {
    weak var coordinatorDelegate: BillingCoordinatorProtocol?
    weak var camDelegate: CAMDelegate?
    weak var view: EntitlementPickerViewController?
    var availableProducts: [Product] = []
    
    func viewDidLoad() {
        self.availableProducts = camDelegate?.availableProducts() ?? []
        
        let viewModels = self.availableProducts.map({ (product) -> OfferViewModel in
            let buyAction = {}
            return OfferViewModel(title: product.title,
                                  description: product.description,
                                  buyAction: buyAction)
        })
        
        self.view?.showOffers(viewModels)
    }
    
    func backToPreviousScreen() {
        coordinatorDelegate?.finishBillingFlow(isUserHasAccess: false)
    }
    
    func showRedeemCodeScreen() {
        coordinatorDelegate?.showRedeemCodeScreen()
    }
    
    func close() {
       coordinatorDelegate?.finishBillingFlow(isUserHasAccess: false)
    }
}
