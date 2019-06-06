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
    
    func backToPreviousScreen() {
        coordinatorDelegate?.popCurrentScreen()
        if isRoot {
            coordinatorDelegate?.finishAuthorizationFlow(isUserLogged: false)
        }
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
        }
    }
    
    func validate(data: [AuthField]) -> [String: String]? {
        var result = [String: String]()
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
