//
//  AccountActivationPresenter.swift
//  CAM
//
//  Created by Egor Brel on 1/23/20.
//

import Foundation
import ZappPlugins

protocol AccountActivationViewProtocol: AnyObject {
    func showError(description: String?)
    func showLoadingScreen(_ show: Bool)
    func updateTable(fields: [AuthField])
}

class AccountActivationPresenter {
    unowned var view: AccountActivationViewProtocol
    unowned var coordinatorDelegate: AccountActivationCoordinatorProtocol
    unowned var camDelegate: CAMDelegate
    
    init(view: AccountActivationViewProtocol,
         coordinatorDelegate: AccountActivationCoordinatorProtocol,
         camDelegate: CAMDelegate) {
        self.view = view
        self.coordinatorDelegate = coordinatorDelegate
        self.camDelegate = camDelegate
    }
    
    func viewDidLoad() {
        if let json = camDelegate.getPluginConfig()[CAMKeys.authFields.rawValue],
            let data = json.data(using: .utf8) {
            if let jsonAuthFields = try? JSONDecoder().decode(AuthFields.self, from: data),
                let loginFields = jsonAuthFields.accountActivation {
                view.updateTable(fields: loginFields)
            }
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
                data[index].errorDescription = camDelegate.getPluginConfig()[CAMKeys.emptyFieldsMessage.rawValue] ?? ""
                continue
            }
            if data[index].type == .email && !(data[index].text ?? "").isEmailValid() {
                isSucceed = false
                data[index].state = .error
                data[index].errorDescription = camDelegate.getPluginConfig()[CAMKeys.wrongEmailMessage.rawValue] ?? ""
                continue
            }
            if let key = data[index].key {
                result[key] = data[index].text
            }
        }
        if isSucceed {
            return result
        } else {
            view.showLoadingScreen(false)
            view.updateTable(fields: data)
        }
        return nil
    }
    
    func activateAccount(data: [AuthField]) {
        self.view.showLoadingScreen(true)
        if let data = validate(data: data) {
            camDelegate.activateAccount(data: data, completion: { [weak self] (result) in
                guard let self = self else { return }
                switch result {
                case .success:
                    self.coordinatorDelegate.finishCoordinatorFlow(result: true)
                case .failure(let error):
                    self.view.showLoadingScreen(false)
                    self.view.showError(description: error.localizedDescription)
                }
            })
        } else {
            view.showLoadingScreen(false)
        }
    }
    
    func backToPreviousScreen() {
        self.coordinatorDelegate.popCurrentScreen()
    }
    
    func resendCode(data: [AuthField]) {
        self.view.showLoadingScreen(true)
        if let data = validate(data: data) {
            camDelegate.sendActivationCode(data: data, completion: { [weak self] (result) in
                guard let self = self else { return }
                switch result {
                case .success:
                    self.view.showLoadingScreen(false)
                case .failure(let error):
                    self.view.showLoadingScreen(false)
                    self.view.showError(description: error.localizedDescription)
                }
            })
        } else {
            view.showLoadingScreen(false)
        }
    }
    
    func close() {
        coordinatorDelegate.finishCAMFlow()
    }
}
