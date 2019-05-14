//
//  EntitlementsPickerPresenter.swift
//  CAMFramework
//
//  Created by Egor Brel on 5/3/19.
//  Copyright © 2019 Egor Brel. All rights reserved.
//

import Foundation
import ApplicasterIAP

class EntitlementPickerPresenter {
    weak var coordinatorDelegate: BillingCoordinatorProtocol?
    weak var camDelegate: CAMDelegate?
    weak var view: EntitlementPickerViewController?
    var availableProducts: [Product] = []
    
    // MARK: - Public methods
    
    func viewDidLoad() {
        self.availableProducts = camDelegate?.availableProducts() ?? []
        self.showOffers()
    }
    
    func backToPreviousScreen() {
        coordinatorDelegate?.finishBillingFlow(isUserHasAccess: false)
    }
    
    func close() {
       coordinatorDelegate?.finishBillingFlow(isUserHasAccess: false)
    }
    
    // MARK: - Private methods
    
    private func showOffers() {
        let viewModels = self.availableProducts.map({ (product) -> OfferViewModel in
            let buyAction = {
                BillingHelper.sharedInstance.purchase(product.skProduct, completion: { [weak self] (result) in
                    switch result {
                    case .success(let purchase):
                        self?.camDelegate?.itemPurchased(item: purchase.item)
                        self?.coordinatorDelegate?.finishBillingFlow(isUserHasAccess: true)
                    case .failure(let error):
                        print(error.localizedDescription)
                    }
                })
            }
            
            let redeemAction: () -> Void = { [weak self] in
                self?.coordinatorDelegate?.showRedeemCodeScreen()
            }
            
            return OfferViewModel(title: product.title,
                                  description: product.description,
                                  buyAction: buyAction,
                                  redeemAction: redeemAction)
        })
        
        self.view?.showOffers(viewModels)
    }
}
