//
//  ResetPasswordPresenter.swift
//  CAMFramework
//
//  Created by Egor Brel on 4/30/19.
//  Copyright © 2019 Egor Brel. All rights reserved.
//

import Foundation

protocol ResetPasswordViewProtocol: AnyObject {
    func showError(description: String?)
    func showLoadingScreen(_ show: Bool)
    func showConfirmationScreenIfNeeded()
}

class ResetPasswordPresenter {
    weak var view: ResetPasswordViewProtocol?
    weak var coordinatorDelegate: AuthorizationCoordinatorProtocol?
    weak var camDelegate: CAMDelegate?
    
    func showResetPasswordScreen() {
        coordinatorDelegate?.showResetPasswordScreen()
    }
    
    func backToPreviousScreen() {
        coordinatorDelegate?.popCurrentScreen()
    }
    
    func resetPassword(email: String) {
        self.view?.showLoadingScreen(true)
        camDelegate?.resetPassword(email: email, completion: { (result) in
            switch result {
            case .success:
                self.view?.showConfirmationScreenIfNeeded()
            case .failure(let description):
                self.view?.showLoadingScreen(false)
                self.view?.showError(description: description)
            }
        })
    }
    
    func close() {
        coordinatorDelegate?.finishAuthorizationFlow(isUserLogged: false)
    }
}
