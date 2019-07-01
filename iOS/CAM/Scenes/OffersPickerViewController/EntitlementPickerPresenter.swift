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
        self.view?.hideLoadingIndicator()
        
        let screenTitle = camDelegate?.getPluginConfig()[CAMKeys.paymentScreenTitle.rawValue] ?? ""
        let restoreHint = camDelegate?.getPluginConfig()[CAMKeys.restoreHint.rawValue] ?? ""
        let restoreButtonText = camDelegate?.getPluginConfig()[CAMKeys.restoreButtonText.rawValue] ?? ""
        let legalDetailsText = camDelegate?.getPluginConfig()[CAMKeys.legalDetailsText.rawValue] ?? ""
        let viewModel = OffersViewModel(title: screenTitle,
                                        restoreHint: restoreHint,
                                        restoreButtonText: restoreButtonText,
                                        legalDetails: legalDetailsText)
        
        self.view?.viewModel = viewModel
    }
    
    func close() {
       coordinatorDelegate?.finishBillingFlow(isUserHasAccess: false)
    }
    
    func restore() {
        BillingHelper.sharedInstance.restore { (result) in
            switch result {
            case .success(let response):
                self.camDelegate?.itemsRestored(items: response)
                if self.camDelegate?.isPurchaseNeeded() == true {
                    self.showConfirmationScreen()
                }
            case .failure(let error):
                print(error.localizedDescription)
            }
        }
    }
    
    // MARK: - Private methods
    
    private func showOffers() {
        let viewModels = self.availableProducts.map({ (product) -> OfferViewModel in
            let buyAction = {
                BillingHelper.sharedInstance.purchase(product.skProduct, completion: { [weak self] (result) in
                    switch result {
                    case .success(let purchase):
                        self?.camDelegate?.itemPurchased(item: purchase.item)
                        self?.showConfirmationScreen()
                    case .failure(let error):
                        print(error.localizedDescription)
                    }
                })
            }
            
            let redeemAction: () -> Void = { [weak self] in
                self?.coordinatorDelegate?.showRedeemCodeScreen()
            }
            
            let configText = camDelegate?.getPluginConfig()[CAMKeys.purchaseButtonText.rawValue] ?? ""
            let price = product.skProduct.localizedPrice ?? ""
            let purchaseButtonText = configText + " " + price
            
            return OfferViewModel(config: camDelegate?.getPluginConfig() ?? [String: String](),
                                  title: product.skProduct.localizedTitle,
                                  description: product.skProduct.localizedDescription,
                                  purchaseButtonText: purchaseButtonText,
                                  buyAction: buyAction,
                                  redeemAction: redeemAction)
        })
        
        self.view?.showOffers(viewModels)
    }
    
    private func showConfirmationScreen() {
        guard let configDictionary = camDelegate?.getPluginConfig(),
            let _ = configDictionary[CAMKeys.paymentAlertTitle.rawValue],
            let _ = configDictionary[CAMKeys.paymentAlertInfo.rawValue],
            let _ = configDictionary[CAMKeys.alertButtonText.rawValue] else {
            self.coordinatorDelegate?.finishBillingFlow(isUserHasAccess: true)
            return
        }
        
        self.view?.showConfirmationScreen(config: configDictionary,
                                          titleKey: .paymentAlertTitle,
                                          descriptionKey: .paymentAlertInfo,
                                          buttonKey: .alertButtonText, action: {
            self.coordinatorDelegate?.finishBillingFlow(isUserHasAccess: true)
        })
    }
}
