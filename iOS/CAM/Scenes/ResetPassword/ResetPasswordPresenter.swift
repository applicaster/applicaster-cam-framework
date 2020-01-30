//
//  ResetPasswordPresenter.swift
//  CAMFramework
//
//  Created by Egor Brel on 4/30/19.
//  Copyright © 2019 Egor Brel. All rights reserved.
//

import Foundation
import ZappPlugins

protocol ResetPasswordViewProtocol: AnyObject {
    func showError(description: String?)
    func showLoadingScreen(_ show: Bool)
    func showConfirmationScreenIfNeeded()
    func updateTable(fields: [AuthField])
}

class ResetPasswordPresenter {
    
    unowned var view: ResetPasswordViewProtocol
    unowned var coordinatorDelegate: ResetPasswordCoordinatorProtocol
    unowned var camDelegate: CAMDelegate
    
    init(view: ResetPasswordViewProtocol,
         coordinatorDelegate: ResetPasswordCoordinatorProtocol,
         camDelegate: CAMDelegate) {
        self.view = view
        self.coordinatorDelegate = coordinatorDelegate
        self.camDelegate = camDelegate
    }
    
    func viewDidLoad() {
        if let json = camDelegate.getPluginConfig()[CAMKeys.authFields.rawValue],
            let data = json.data(using: .utf8) {
            if let jsonAuthFields = try? JSONDecoder().decode(AuthFields.self, from: data),
                let loginFields = jsonAuthFields.resetPassword {
                view.updateTable(fields: loginFields)
            }
        }
    }
    
    func finishFlow() {
        coordinatorDelegate.finishCoordinatorFlow()
    }
    
    func resetPassword(data: [AuthField]) {
        ZAAppConnector.sharedInstance().analyticsDelegate.trackEvent(event: AnalyticsEvents.resetPassword)
        self.view.showLoadingScreen(true)
        if let data = validate(data: data) {
            camDelegate.resetPassword(data: data, completion: { [weak self] (result) in
                guard let self = self else { return }
                switch result {
                case .success:
                    self.view.showConfirmationScreenIfNeeded()
                case .failure(let error):
                    self.view.showLoadingScreen(false)
                    self.view.showError(description: error.localizedDescription)
                    
                    let viewAlertEvent = AnalyticsEvents.makeViewAlert(from: error)
                    ZAAppConnector.sharedInstance().analyticsDelegate.trackEvent(event: viewAlertEvent)
                    AnalyticsEvents.userFlow.append("Failed Attempt")
                }
            })
        } else {
            view.showLoadingScreen(false)
        }
    }
    
    func sendPasswordActivationCode(data: [AuthField]) {
        let playableInfo = camDelegate.playableItemInfo
        let activateAccountEvent = AnalyticsEvents.sendActivationCode(playableInfo,
                                                                      codePurpose: "PasswordUpdate",
                                                                      isResend: true)
        ZAAppConnector.sharedInstance().analyticsDelegate.trackEvent(event: activateAccountEvent)
        self.view.showLoadingScreen(true)
        if let data = validate(data: data) {
            camDelegate.sendPasswordActivationCode(data: data, completion: { [weak self] (result) in
                guard let self = self else { return }
                switch result {
                case .success:
                    self.view.showLoadingScreen(false)
                    self.coordinatorDelegate.showUpdatePasswordScreen()
                case .failure(let error):
                    self.view.showLoadingScreen(false)
                    self.view.showError(description: error.localizedDescription)
                    
                    let viewAlertEvent = AnalyticsEvents.makeViewAlert(from: error)
                    ZAAppConnector.sharedInstance().analyticsDelegate.trackEvent(event: viewAlertEvent)
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
