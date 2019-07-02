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
            case .success(let products):
                self?.retrieveStoreProductsFor(products: products, completion: { (result) in
                    self?.showOffers(availableProducts: result)
                    self?.view?.hideLoadingIndicator()
                })
            case .failure(let description):
                self?.view?.showAlert(description: description)
                self?.view?.hideLoadingIndicator()
            }
        })
    }
    
    func retrieveStoreProductsFor(products: [AvailableProduct], completion: @escaping ([(delegateProduct: AvailableProduct, storeProduct: SKProduct)]) -> Void) {
        let productsDictionary = products.reduce([String: AvailableProduct]()) { (dict, product) -> [String: AvailableProduct] in
            var dict = dict
            dict[product.appleStoreID] = product
            return dict
        }
        let storeIDs = Set<String>(productsDictionary.keys)
        BillingHelper.sharedInstance.products(storeIDs, completion: { (result) in
            switch result {
            case .success(let data):
                let offersArray = self.wrapOffersWithStoreProducts(products: productsDictionary, storeProducts: data.products)
                completion(offersArray)
            case .failure:
                completion([])
            }
        })
    }
    
    func wrapOffersWithStoreProducts(products: [String: AvailableProduct], storeProducts: [SKProduct]) -> [(delegateProduct: AvailableProduct, storeProduct: SKProduct)] {
        return storeProducts.reduce([(delegateProduct: AvailableProduct, storeProduct: SKProduct)]()) {
            (array, item) -> [(delegateProduct: AvailableProduct, storeProduct: SKProduct)] in
            var array = array
            guard let availableProduct = products[item.productIdentifier] else {
                return array
            }
            array.append((delegateProduct: availableProduct, storeProduct: item))
            return array
        }
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
    
    private func showOffers(availableProducts: [(delegateProduct: AvailableProduct, storeProduct: SKProduct)]) {
        let viewModels = availableProducts.map({ (item) -> OfferViewModel in
            let buyAction = {
                BillingHelper.sharedInstance.purchase(item.storeProduct, completion: { [weak self] (result) in
                    switch result {
                    case .success(let purchase):
                        self?.purchaseAction(item: item, purchase: purchase)
                    case .failure(let error):
                        print(error.localizedDescription)
                    }
                })
            }
            
            let redeemAction: () -> Void = { [weak self] in
                self?.coordinatorDelegate?.showRedeemCodeScreen()
            }
            
            let configText = camDelegate?.getPluginConfig()[CAMKeys.purchaseButtonText.rawValue] ?? ""
            let price = item.storeProduct.localizedPrice ?? ""
            let purchaseButtonText = configText + " " + price
            
            return OfferViewModel(config: camDelegate?.getPluginConfig() ?? [String: String](),
                                  title: item.storeProduct.localizedTitle,
                                  description: item.storeProduct.localizedDescription,
                                  purchaseButtonText: purchaseButtonText,
                                  buyAction: buyAction,
                                  redeemAction: redeemAction)
        })
        
        self.view?.showOffers(viewModels)
    }
    
    private func purchaseAction(item: (delegateProduct: AvailableProduct, storeProduct: SKProduct), purchase: Purchase) {
        let transactionID = purchase.transaction?.transactionIdentifier
        let receipt = (BillingHelper.sharedInstance.localReceiptData() ?? Data()).base64EncodedString(options: [])
        let purchasedItem = PurchasedProduct.init(offerID: item.delegateProduct.offerID,
                                                  entitlementID: item.delegateProduct.entitlementID,
                                                  transactionID: transactionID,
                                                  receipt: receipt,
                                                  productID: item.storeProduct.productIdentifier,
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
