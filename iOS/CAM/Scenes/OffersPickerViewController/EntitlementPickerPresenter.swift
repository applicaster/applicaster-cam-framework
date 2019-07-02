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

class EntitlementPickerPresenter {
    weak var coordinatorDelegate: BillingCoordinatorProtocol?
    weak var camDelegate: CAMDelegate?
    weak var view: EntitlementPickerViewController?
    var availableProducts: [(offer: AvailableOffer, skProduct: SKProduct)] = []
    
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
            case .success(let product):
                let dictionary = product.reduce([String: AvailableOffer]()) { (dict, item) ->
                    [String: AvailableOffer] in
                    var dict = dict
                    dict[item.appleStoreID] = item
                    return dict
                }
                self?.retrieveStoreProductsFor(products: dictionary, completion: { (availableProducts) in
                    self?.availableProducts = availableProducts
                    self?.showOffers()
                    self?.view?.hideLoadingIndicator()
                })
            case .failure(let description):
                self?.view?.showAlert(description: description)
                self?.view?.hideLoadingIndicator()
            }
        })
    }
    
    func retrieveStoreProductsFor(products: [String: AvailableOffer], completion: @escaping ([(offer: AvailableOffer, skProduct: SKProduct)]) -> Void) {
        let appleIDs = Set<String>(products.keys)
        BillingHelper.sharedInstance.products(appleIDs, completion: { (result) in
            switch result {
            case .success(let data):
                let result = data.products.reduce([(offer: AvailableOffer, skProduct: SKProduct)]()) { (array, item) ->
                    [(offer: AvailableOffer, skProduct: SKProduct)] in
                    var array = array
                    guard let offer = products[item.productIdentifier] else {
                        return array
                    }
                    array.append((offer: offer, skProduct: item))
                    return array
                }
                completion(result)
            case .failure:
                completion([])
            }
        })
    }
    
    func close() {
        coordinatorDelegate?.finishBillingFlow(isUserHasAccess: false)
    }
    
    func restore() {
        BillingHelper.sharedInstance.restore { (result) in
            switch result {
            case .success(let response):
                //self.camDelegate?.itemsRestored(items: response)
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
        let viewModels = availableProducts.map({ (offer, skProduct) -> OfferViewModel in
            let buyAction = {
                BillingHelper.sharedInstance.purchase(skProduct, completion: { [weak self] (result) in
                    switch result {
                    case .success(let purchase):
                        self?.purchaseAction(itemID: offer.entitlementID, item: skProduct, purchase: purchase)
                    case .failure(let error):
                        print(error.localizedDescription)
                    }
                })
            }
            
            let redeemAction: () -> Void = { [weak self] in
                let itemID = offer.entitlementID //used for redeem in cleeng
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
    
    private func purchaseAction(itemID: String, item: SKProduct, purchase: Purchase) {
        let transactionID = purchase.transaction?.transactionIdentifier
        let receipt = (BillingHelper.sharedInstance.localReceiptData() ?? Data()).base64EncodedString(options: [])
        let purchasedItem = PurchasedProduct.init(itemID: itemID,
                                                  transactionID: transactionID,
                                                  receipt: receipt,
                                                  redeemCode: nil,
                                                  state: .purchased)
        self.camDelegate?.itemPurchased(purchasedItem: purchasedItem, completion: { [weak self] (result) in
            switch result {
            case .success:
                self?.showConfirmationScreen()
            case .failure(let description):
                self?.view?.showAlert(description: description)
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
