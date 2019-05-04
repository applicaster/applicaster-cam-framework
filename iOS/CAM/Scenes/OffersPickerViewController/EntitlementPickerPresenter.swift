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
