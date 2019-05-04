//
//  SignUpPresenter.swift
//  CAMFramework
//
//  Created by Egor Brel on 4/30/19.
//  Copyright © 2019 Egor Brel. All rights reserved.
//

import Foundation

class SignUpPresenter {
    weak var coordinatorDelegate: AuthorizationCoordinatorProtocol?
    weak var camDelegate: CAMDelegate?
    var isRoot: Bool = false
    
    func backToPreviousScreen() {
        coordinatorDelegate?.popCurrentScreen()
        if isRoot {
            coordinatorDelegate?.finishAuthorizationFlow(isUserLogged: false)
        }
    }
    
    func showLoginScreen() {
        if isRoot {
            coordinatorDelegate?.showLoginScreen(isCoordinatorRootController: false)
        } else {
            coordinatorDelegate?.popCurrentScreen()
        }
    }
    
    func close() {
        coordinatorDelegate?.finishAuthorizationFlow(isUserLogged: false)
    }
}
