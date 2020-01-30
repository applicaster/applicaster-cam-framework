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
    var userAuthScreenInputData = [String: String]()
    unowned var view: AccountActivationViewProtocol
    unowned var coordinatorDelegate: AuthorizationCoordinatorProtocol
    unowned var camDelegate: CAMDelegate
    
    init(userData: [String: String],
         view: AccountActivationViewProtocol,
         coordinatorDelegate: AuthorizationCoordinatorProtocol,
         camDelegate: CAMDelegate) {
        self.userAuthScreenInputData = userData
        self.view = view
        self.coordinatorDelegate = coordinatorDelegate
        self.camDelegate = camDelegate
    }
    
    func viewDidLoad() {
        sendActivationCode(isResend: false)
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
        let playableInfo = camDelegate.playableItemInfo
        let activateAccountEvent = AnalyticsEvents.activateAccount(playableInfo)
        ZAAppConnector.sharedInstance().analyticsDelegate.trackEvent(event: activateAccountEvent)
        
        self.view.showLoadingScreen(true)
        if let data = validate(data: data) {
            let data = data.merge(userAuthScreenInputData)
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
    
    func sendActivationCode(isResend: Bool) {
        let playableInfo = camDelegate.playableItemInfo
        let activateAccountEvent = AnalyticsEvents.sendActivationCode(playableInfo,
                                                                      codePurpose: "Account Activation",
                                                                      isResend: isResend)
        ZAAppConnector.sharedInstance().analyticsDelegate.trackEvent(event: activateAccountEvent)
        self.view.showLoadingScreen(true)
        camDelegate.sendAuthActivationCode(data: userAuthScreenInputData, completion: { [weak self] (result) in
            guard let self = self else { return }
            switch result {
            case .success:
                self.view.showLoadingScreen(false)
            case .failure(let error):
                self.view.showLoadingScreen(false)
                self.view.showError(description: error.localizedDescription)
            }
        })
    }
    
    func close() {
        coordinatorDelegate.finishCoordinatorFlow(result: false)
    }
}
