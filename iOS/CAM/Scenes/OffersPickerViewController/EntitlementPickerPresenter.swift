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

private enum IAPEvent {
    case purchase
    case restore
    
    var analyticsEvent: ConfirmationAlertTypes {
        switch self {
        case .purchase:
            return .purchase
        case .restore:
            return .restorePurchase
        }
    }
}

class EntitlementPickerPresenter {
    
    unowned var view: EntitlementPickerViewController
    unowned var coordinatorDelegate: BillingCoordinatorProtocol
    unowned var camDelegate: CAMDelegate
    
    var availableProducts: [SKProduct] = []
    
    init(view: EntitlementPickerViewController,
         coordinatorDelegate: BillingCoordinatorProtocol,
         camDelegate: CAMDelegate) {
        self.view = view
        self.coordinatorDelegate = coordinatorDelegate
        self.camDelegate = camDelegate
    }
    
    // MARK: - Public methods
    
    func viewDidLoad() {
        let screenTitle = camDelegate.getPluginConfig()[CAMKeys.paymentScreenTitle.rawValue] ?? ""
        let restoreHint = camDelegate.getPluginConfig()[CAMKeys.restoreHint.rawValue] ?? ""
        let restoreButtonText = camDelegate.getPluginConfig()[CAMKeys.restoreButtonText.rawValue] ?? ""
        let legalDetailsText = camDelegate.getPluginConfig()[CAMKeys.legalDetailsText.rawValue] ?? ""
        let viewModel = OffersViewModel(title: screenTitle,
                                        restoreHint: restoreHint,
                                        restoreButtonText: restoreButtonText,
                                        legalDetails: legalDetailsText)
        
        self.view.viewModel = viewModel
        
        camDelegate.availableProducts(completion: { [weak self] (result) in
            guard let self = self else { return }
            
            switch result {
            case .success(let productStoreIDs):
                BillingHelper.sharedInstance.products(Set<String>(productStoreIDs), completion: { (result) in
                    self.view.hideLoadingIndicator()
                    switch result {
                    case .success(let result):
                        self.availableProducts = result.products
                        self.showOffers()
                    case .failure:
                        self.showOffers()
                    }
                })
            case .failure(let error):
                self.view.showAlert(description: error.localizedDescription)
                self.view.hideLoadingIndicator()
            }
        })
    }
    
    func close() {
        coordinatorDelegate.finishBillingFlow(isUserHasAccess: false)
    }
    
    func restore() {
        let playableInfo = PlayableItemInfo(name: camDelegate.itemName(),
                                            type: camDelegate.itemType())
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
                self.camDelegate.itemsRestored(restoredItems: resultArray, completion: { [weak self] (result) in
                    guard let self = self else { return }
                    switch result {
                    case .success:
                        if self.camDelegate.isPurchaseNeeded() == true {
                            self.showConfirmationScreen(for: .restore)
                        }
                        let productsProperties = resultArray.compactMap({ (purchasedProduct) -> PurchaseProperties? in
                            guard let productIdentifier = purchasedProduct.transaction?.payment.productIdentifier else {
                                return nil
                            }
                            
                            return self.camDelegate.purchaseProperties(for: productIdentifier)
                        })
                        let successfulRestoreEvent = AnalyticsEvents.completeRestorePurchase(playableInfo,
                                                                                             productsProperties)
                        ZAAppConnector.sharedInstance().analyticsDelegate.trackEvent(name: successfulRestoreEvent.key,
                                                                                     parameters: successfulRestoreEvent.metadata)
                    case .failure(let error):
                        self.view.showAlert(description: error.localizedDescription)
                        self.sendAnalyticsEvent(for: error)
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
            let itemName = camDelegate.itemName()
            let itemType = camDelegate.itemType()
            var voucherProperties = camDelegate.purchaseProperties(for: skProduct.productIdentifier)
            
            let buyAction = {
                let playableInfo = PlayableItemInfo(name: itemName,
                                                    type: itemType)
                
                let buyEvent = AnalyticsEvents.tapPurchaseButton(playableInfo,
                                                                 voucherProperties)
                ZAAppConnector.sharedInstance().analyticsDelegate.trackEvent(name: buyEvent.key,
                                                                             parameters: buyEvent.metadata)
                
                    
                BillingHelper.sharedInstance.purchase(skProduct, completion: { [weak self] (result) in
                    let purchaseResultEvent: AnalyticsEvents
                    
                    switch result {
                    case .success(let purchase):
                        voucherProperties.transactionID = purchase.transaction?.transactionIdentifier
                        purchaseResultEvent = AnalyticsEvents.completePurchase(playableInfo,
                                                                               voucherProperties)
                        self?.purchaseAction(purchase: purchase)
                    case .failure(let error):
                        if let skError = error as? SKError, skError.code == .paymentCancelled {
                            purchaseResultEvent = AnalyticsEvents.cancelPurchase(playableInfo,
                                                                                 voucherProperties)
                        } else {
                            purchaseResultEvent = AnalyticsEvents.storePurchaseError(error,
                                                                                     playableInfo,
                                                                                     voucherProperties)
                        }
                        
                    }
                    
                    ZAAppConnector.sharedInstance().analyticsDelegate.trackEvent(name: purchaseResultEvent.key,
                                                                                 parameters: purchaseResultEvent.metadata)
                })
            }
            
            let redeemAction: () -> Void = { [weak self] in
                self?.coordinatorDelegate.showRedeemCodeScreen()
            }
            
            let configText = camDelegate.getPluginConfig()[CAMKeys.purchaseButtonText.rawValue] ?? ""
            let price = skProduct.localizedPrice ?? ""
            let purchaseButtonText = configText + " " + price
            
            return OfferViewModel(config: camDelegate.getPluginConfig(),
                                  title: skProduct.localizedTitle,
                                  description: skProduct.localizedDescription,
                                  purchaseButtonText: purchaseButtonText,
                                  buyAction: buyAction,
                                  redeemAction: redeemAction)
        })
        
        self.view.showOffers(viewModels)
    }
    
    private func purchaseAction(purchase: Purchase) {
        let receipt = (BillingHelper.sharedInstance.localReceiptData() ?? Data()).base64EncodedString(options: [])
        let purchasedItem = PurchasedProduct()
        purchasedItem.transaction = purchase.transaction
        purchasedItem.product = purchase.item
        purchasedItem.receipt = receipt
        purchasedItem.state = .purchased
        self.camDelegate.itemPurchased(purchasedItem: purchasedItem, completion: { [weak self] (result) in
            switch result {
            case .success:
                self?.showConfirmationScreen(for: .purchase)
            case .failure(let error):
                self?.view.showAlert(description: error.localizedDescription)
                self?.sendAnalyticsEvent(for: error)
            }
        })
    }
    
    private func showConfirmationScreen(for event: IAPEvent) {
        let configDictionary = camDelegate.getPluginConfig()
        let alertTitleKey = self.alertTitleKey(for: event)
        let alertDescriptionKey = self.alertDescriptionKey(for: event)
        
        guard let alertTitle = configDictionary[alertTitleKey.rawValue],
            let alertDescription = configDictionary[alertDescriptionKey.rawValue],
            let _ = configDictionary[CAMKeys.alertButtonText.rawValue] else {
                self.coordinatorDelegate.finishBillingFlow(isUserHasAccess: true)
                return
        }
        
        let viewAlertEvent = AnalyticsEvents.viewAlert(AlertInfo(title: alertTitle,
                                                                 description: alertDescription,
                                                                 isConfirmation: IsConfirmationAlert.yes(type: event.analyticsEvent)),
                                                       apiError: nil)
        ZAAppConnector.sharedInstance().analyticsDelegate.trackEvent(name: viewAlertEvent.key,
                                                                     parameters: viewAlertEvent.metadata)
        
        self.view.showConfirmationScreen(config: configDictionary,
                                          titleKey: alertTitleKey,
                                          descriptionKey: alertDescriptionKey,
                                          buttonKey: .alertButtonText, action: {
                                            self.coordinatorDelegate.finishBillingFlow(isUserHasAccess: true)
        })
    }
    
    private func alertTitleKey(for event: IAPEvent) -> CAMKeys {
        switch event {
        case .purchase:
            return CAMKeys.paymentAlertTitle
        case .restore:
            return CAMKeys.restoreAlertTitle
        }
    }
    
    private func alertDescriptionKey(for event: IAPEvent) -> CAMKeys {
        switch event {
        case .purchase:
            return CAMKeys.paymentAlertInfo
        case .restore:
            return CAMKeys.restoreAlertDescription
        }
    }
    
    private func sendAnalyticsEvent(for error: Error) {
        let viewAlertEvent = AnalyticsEvents.makeViewAlert(from: error)
        ZAAppConnector.sharedInstance().analyticsDelegate.trackEvent(name: viewAlertEvent.key,
                                                                     parameters: viewAlertEvent.metadata)
    }
}

