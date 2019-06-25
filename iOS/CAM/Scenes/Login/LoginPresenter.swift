//
//  LoginPresenter.swift
//  CAMFramework
//
//  Created by Egor Brel on 4/29/19.
//  Copyright © 2019 Egor Brel. All rights reserved.
//

import Foundation
import ApplicasterSDK

protocol LoginViewProtocol: AnyObject {
    func showError(description: String?)
    func showLoadingScreen(_ show: Bool)
    func updateTable(fields: [AuthField])
}

class LoginPresenter {
    weak var view: LoginViewProtocol?
    weak var coordinatorDelegate: AuthorizationCoordinatorProtocol?
    weak var camDelegate: CAMDelegate?
    var isRoot: Bool = false
    
    func viewDidLoad() {
        if let json = camDelegate?.getPluginConfig()[CAMKeys.authFields.rawValue],
           let data = json.data(using: .utf8) {
            if let jsonAuthFields = try? JSONDecoder().decode(AuthFields.self, from: data),
               let loginFields = jsonAuthFields.login {
                view?.updateTable(fields: loginFields)
            }
        }
    }
    
    func showResetPasswordScreen() {
        coordinatorDelegate?.showResetPasswordScreen()
    }
    
    func showSignUpScreen() {
        if isRoot {
            coordinatorDelegate?.showSingUpScreen(isCoordinatorRootController: false)
        } else {
            coordinatorDelegate?.popCurrentScreen()
        }
    }
    
    func close() {
        coordinatorDelegate?.finishAuthorizationFlow(isUserLogged: false)
    }
    
    func login(data: [AuthField]) {
        view?.showLoadingScreen(true)
        if let data = validate(data: data) {
            camDelegate?.login(authData: data, completion: { (result) in
                switch result {
                case .success:
                    self.coordinatorDelegate?.finishAuthorizationFlow(isUserLogged: true)
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
    
    func showFacebookAuthScreen() {
        view?.showLoadingScreen(true)
        let facebookID = Bundle.main.object(forInfoDictionaryKey: "FacebookAppID") as? String
        let facebookDisplayName = Bundle.main.object(forInfoDictionaryKey: "CFBundleName") as? String
        let facebookClient =  APFacebookSDKClient.facebookSDK(withFacebookAppID: facebookID, andAppDisplayName: facebookDisplayName)
        facebookClient.authorizeFacebook(true, completion: { (isUserLogged, error) in
            if isUserLogged {
                self.getFacebookUser()
            } else {
                self.view?.showLoadingScreen(false)
                if let error = error {
                    self.view?.showError(description: error.localizedDescription)
                }
            }
        })
    }
    
    func getFacebookUser() {
        APFacebookSDKClient.sharedInstance()?.getCurrentUser(completionHandler: { (user, error) in
            self.view?.showLoadingScreen(false)
            if let error = error {
                self.view?.showError(description: error.localizedDescription)
                return
            }
            if let user = user, let email = user.email, let userId = APFacebookSDKClient.sharedInstance()?.userID() {
                self.facebookLogin(email: email, userId: userId)
            }
        })
    }
    
    func facebookLogin(email: String, userId: String) {
        self.camDelegate?.facebookLogin(userData: (email: email, userId: userId), completion: { (result) in
            switch result {
            case .success:
                self.coordinatorDelegate?.finishAuthorizationFlow(isUserLogged: true)
            case .failure(description: let description):
                self.view?.showError(description: description)
            }
        })
    }
}
