//
//  UpdatePasswordPresenter.swift
//  CAM
//
//  Created by Egor Brel on 1/29/20.
//

import Foundation
import ZappPlugins

protocol UpdatePasswordViewProtocol: AnyObject {
    func showError(description: String?)
    func showLoadingScreen(_ show: Bool)
    func showConfirmationScreenIfNeeded()
    func updateTable(fields: [AuthField])
}

class UpdatePasswordPresenter {
    
    var userResetPasswordInputData = [String: String]() //user input from previous screen
    unowned var view: ResetPasswordViewProtocol
    unowned var coordinatorDelegate: ResetPasswordCoordinatorProtocol
    unowned var camDelegate: CAMDelegate
    
    init(userData: [String: String],
         view: ResetPasswordViewProtocol,
         coordinatorDelegate: ResetPasswordCoordinatorProtocol,
         camDelegate: CAMDelegate) {
        self.userResetPasswordInputData = userData
        self.view = view
        self.coordinatorDelegate = coordinatorDelegate
        self.camDelegate = camDelegate
    }
    
    func viewDidLoad() {
        if let json = camDelegate.getPluginConfig()[CAMKeys.authFields.rawValue],
            let data = json.data(using: .utf8) {
            if let jsonAuthFields = try? JSONDecoder().decode(AuthFields.self, from: data),
                let loginFields = jsonAuthFields.updatePassword {
                view.updateTable(fields: loginFields)
            }
        }
    }
    
    func backToPreviousScreen() {
        coordinatorDelegate.popCurrentScreen()
    }
    
    func finishFlow() {
        coordinatorDelegate.finishCoordinatorFlow()
    }
    
    func updatePassword(data: [AuthField]) {
        ZAAppConnector.sharedInstance().analyticsDelegate.trackEvent(event: AnalyticsEvents.updatePassword)
        self.view.showLoadingScreen(true)
        if let data = validate(data: data) {
            let data = data.merge(userResetPasswordInputData)
            camDelegate.updatePassword(data: data, completion: { [weak self] (result) in
                guard let self = self else { return }
                switch result {
                case .success:
                    self.view.showConfirmationScreenIfNeeded()
                case .failure(let error):
                    self.view.showLoadingScreen(false)
                    self.view.showError(description: error.localizedDescription)
                    AnalyticsEvents.userFlow.append("Failed Attempt")
                }
            })
        } else {
            view.showLoadingScreen(false)
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
    
    func close() {
        coordinatorDelegate.close()
    }
}
