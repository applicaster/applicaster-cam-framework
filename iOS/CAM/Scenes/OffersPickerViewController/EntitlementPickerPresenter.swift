//
//  EntitlementsPickerPresenter.swift
//  CAMFramework
//
//  Created by Egor Brel on 5/3/19.
//  Copyright © 2019 Egor Brel. All rights reserved.
//

import Foundation
import ApplicasterIAP
import StoreKit
import ZappPlugins

class EntitlementPickerPresenter {
    weak var coordinatorDelegate: BillingCoordinatorProtocol?
    weak var camDelegate: CAMDelegate?
    weak var view: EntitlementPickerViewController?
    var availableProducts: [SKProduct] = []
    
    // MARK: - Public methods
    
    func viewDidLoad() {
        let screenTitle = camDelegate?.getPluginConfig()[CAMKeys.paymentScreenTitle.rawValue] ?? ""
        let restoreHint = camDelegate?.getPluginConfig()[CAMKeys.restoreHint.rawValue] ?? ""
        let restoreButtonText = camDelegate?.getPluginConfig()[CAMKeys.restoreButtonText.rawValue] ?? ""
        let legalDetailsText = camDelegate?.getPluginConfig()[CAMKeys.legalDetailsText.rawValue] ?? ""
        let viewModel = OffersViewModel(title: screenTitle,
                                        restoreHint: restoreHint,
                                        restoreButtonText: restoreButtonText,
                                        legalDetails: legalDetailsText)
        
        self.view?.viewModel = viewModel
        
        camDelegate?.availableProducts(completion: { [weak self] (result) in
            switch result {
            case .success(let productStoreIDs):
                BillingHelper.sharedInstance.products(Set<String>(productStoreIDs), completion: { (result) in
                    self?.view?.hideLoadingIndicator()
                    switch result {
                    case .success(let result):
                        self?.availableProducts = result.products
                        self?.showOffers()
                    case .failure:
                        self?.showOffers()
                    }
                })
            case .failure(let error):
                self?.view?.showAlert(description: error.localizedDescription)
                self?.view?.hideLoadingIndicator()
            }
        })
    }
    
    func close() {
        coordinatorDelegate?.finishBillingFlow(isUserHasAccess: false)
    }
    
    func restore() {
        let playableInfo = PlayableItemInfo(name: camDelegate?.itemName() ?? "",
                                            type: camDelegate?.itemType() ?? "")
        let tapRestoreEvent = AnalyticsEvents.tapRestorePurchaseLink(playableInfo)
        ZAAppConnector.sharedInstance().analyticsDelegate.trackEvent(name: tapRestoreEvent.key,
                                                                     parameters: tapRestoreEvent.metadata)
        
        BillingHelper.sharedInstance.restore { (result) in
            switch result {
            case .success(let response):
                let resultArray = response.map {(transaction) -> PurchasedProduct in
                    let receipt = (BillingHelper.sharedInstance.localReceiptData() ?? Data()).base64EncodedString(options: [])
                    let item = PurchasedProduct()
                    item.state = .restored
                    item.receipt = receipt
                    item.transaction = transaction
                    return item
                }
                self.camDelegate?.itemsRestored(restoredItems: resultArray, completion: { [weak self] (result) in
                    switch result {
                    case .success:
                        if self?.camDelegate?.isPurchaseNeeded() == true {
                            self?.showConfirmationScreen()
                        }
                    case .failure(let error):
                        self?.view?.showAlert(description: error.localizedDescription)
                    }
                })
            case .failure(let error):
                print(error.localizedDescription)
            }
        }
    }
    
    // MARK: - Private methods
    
    private func showOffers() {
        let viewModels = availableProducts.map({ (skProduct) -> OfferViewModel in
            let buyAction = {
                BillingHelper.sharedInstance.purchase(skProduct, completion: { [weak self] (result) in
                    switch result {
                    case .success(let purchase):
                        self?.purchaseAction(purchase: purchase)
                    case .failure(let error):
                        print(error.localizedDescription)
                    }
                })
            }
            
            let redeemAction: () -> Void = { [weak self] in
                self?.coordinatorDelegate?.showRedeemCodeScreen()
            }
            
            let configText = camDelegate?.getPluginConfig()[CAMKeys.purchaseButtonText.rawValue] ?? ""
            let price = skProduct.localizedPrice ?? ""
            let purchaseButtonText = configText + " " + price
            
            return OfferViewModel(config: camDelegate?.getPluginConfig() ?? [String: String](),
                                  title: skProduct.localizedTitle,
                                  description: skProduct.localizedDescription,
                                  purchaseButtonText: purchaseButtonText,
                                  buyAction: buyAction,
                                  redeemAction: redeemAction)
        })
        
        self.view?.showOffers(viewModels)
    }
    
    private func purchaseAction(purchase: Purchase) {
        let receipt = (BillingHelper.sharedInstance.localReceiptData() ?? Data()).base64EncodedString(options: [])
        let purchasedItem = PurchasedProduct()
        purchasedItem.transaction = purchase.transaction
        purchasedItem.product = purchase.item
        purchasedItem.receipt = receipt
        purchasedItem.state = .purchased
        self.camDelegate?.itemPurchased(purchasedItem: purchasedItem, completion: { [weak self] (result) in
            switch result {
            case .success:
                self?.showConfirmationScreen()
            case .failure(let error):
                self?.view?.showAlert(description: error.localizedDescription)
            }
        })
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

