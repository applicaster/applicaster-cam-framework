//
//  ResetPasswordPresenter.swift
//  CAMFramework
//
//  Created by Egor Brel on 4/30/19.
//  Copyright © 2019 Egor Brel. All rights reserved.
//

import Foundation

class ResetPasswordPresenter {
    weak var coordinatorDelegate: AuthorizationCoordinatorProtocol?
    
    func showResetPasswordScreen() {
        coordinatorDelegate?.showResetPasswordScreen()
    }
    
    func backToPreviousScreen() {
        coordinatorDelegate?.popCurrentScreen()
    }
    
    func resetPassword() {
        
    }
    
    func close() {
        coordinatorDelegate?.finishAuthorizationFlow(isUserLogged: false)
    }
}
