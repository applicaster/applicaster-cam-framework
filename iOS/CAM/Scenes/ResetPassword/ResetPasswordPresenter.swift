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
        } else {
            view?.showLoadingScreen(false)
        }
    }
    
    func validate(data: [AuthField]) -> [String: String]? {
        var data = data
        var isSucceed = true
        var result = [String: String]()
        for index in 0..<data.count {
            if data[index].mandatory && (data[index].text ?? "").isEmpty {
                isSucceed = false
                data[index].state = .error
                data[index].errorDescription = camDelegate?.getPluginConfig()[CAMKeys.emptyFieldsMessage.rawValue] ?? ""
                continue
            }
            if data[index].type == .email && !(data[index].text ?? "").isEmailValid() {
                isSucceed = false
                data[index].state = .error
                data[index].errorDescription = camDelegate?.getPluginConfig()[CAMKeys.wrongEmailMessage.rawValue] ?? ""
                continue
            }
            if let key = data[index].key {
                result[key] = data[index].text
            }
        }
        if isSucceed {
            return result
        } else {
            view?.showLoadingScreen(false)
            view?.updateTable(fields: data)
        }
        return nil
    }
    
    func close() {
        coordinatorDelegate?.finishAuthorizationFlow(isUserLogged: false)
    }
}
