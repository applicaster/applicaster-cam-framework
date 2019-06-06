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
    
    func resetPassword(data: [AuthField]) {
        self.view?.showLoadingScreen(true)
        if let data = validate(data: data) {
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
    }
    
    func validate(data: [AuthField]) -> [String: String?]? {
        var result = [String: String?]()
        for obj in data {
            if obj.mandatory && (obj.text ?? "").isEmpty {
                let message = camDelegate?.getPluginConfig()[CAMKeys.emptyFieldsMessage.rawValue]
                self.view?.showLoadingScreen(false)
                view?.showError(description: message)
                return nil
            }
            if let key = obj.key {
                result[key] = obj.text
            }
        }
        return result
    }
    
    func close() {
        coordinatorDelegate?.finishAuthorizationFlow(isUserLogged: false)
    }
}
