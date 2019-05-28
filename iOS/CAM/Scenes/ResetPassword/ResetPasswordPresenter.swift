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
    func updateTable(fields: [AuthField])
}

class ResetPasswordPresenter {
    weak var view: ResetPasswordViewProtocol?
    weak var coordinatorDelegate: AuthorizationCoordinatorProtocol?
    weak var camDelegate: CAMDelegate?
    
    func viewDidLoad() {
        if let json = camDelegate?.getPluginConfig()[CAMKeys.authFields.rawValue],
            let data = json.data(using: .utf8) {
            if let jsonAuthFields = try? JSONDecoder().decode(AuthFields.self, from: data),
                let loginFields = jsonAuthFields.password {
                view?.updateTable(fields: loginFields)
            }
        }
    }
    
    func showResetPasswordScreen() {
        coordinatorDelegate?.showResetPasswordScreen()
    }
    
    func backToPreviousScreen() {
        coordinatorDelegate?.popCurrentScreen()
    }
    
    func resetPassword(data: [(key: String, value: String?)]) {
        self.view?.showLoadingScreen(true)
        camDelegate?.resetPassword(data: data, completion: { (result) in
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
