//
//  SignUpPresenter.swift
//  CAMFramework
//
//  Created by Egor Brel on 4/30/19.
//  Copyright © 2019 Egor Brel. All rights reserved.
//

import Foundation
import ZappPlugins

protocol SignUpViewProtocol: AnyObject {
    func showError(description: String?)
    func showLoadingScreen(_ show: Bool)
    func updateTable(fields: [AuthField])
}

class SignUpPresenter {
    
    unowned var view: SignUpViewProtocol
    unowned var coordinatorDelegate: AuthorizationCoordinatorProtocol
    unowned var camDelegate: CAMDelegate
    
    var isRoot: Bool = false
    
    init(view: SignUpViewProtocol,
         coordinatorDelegate: AuthorizationCoordinatorProtocol,
         camDelegate: CAMDelegate) {
        self.view = view
        self.coordinatorDelegate = coordinatorDelegate
        self.camDelegate = camDelegate
    }
    
    func viewDidLoad() {
        if let json = camDelegate.getPluginConfig()[CAMKeys.authFields.rawValue],
           let data = json.data(using: .utf8) {
            if let jsonAuthFields = try? JSONDecoder().decode(AuthFields.self, from: data),
                let signUpFields = jsonAuthFields.signup {
                view.updateTable(fields: signUpFields)
            }
        }
    }
    
    func backToPreviousScreen() {
        coordinatorDelegate.popCurrentScreen()
        if isRoot {
            coordinatorDelegate.finishAuthorizationFlow(isUserLogged: false)
        }
    }
    
    func showLoginScreen() {
        ZAAppConnector.sharedInstance().analyticsDelegate.trackEvent(name: AnalyticsEvents.switchToLoginScreen.key,
                                                                     parameters: AnalyticsEvents.switchToLoginScreen.metadata)
        
        if isRoot {
            coordinatorDelegate.showLoginScreen(isCoordinatorRootController: false)
        } else {
            coordinatorDelegate.popCurrentScreen()
        }
    }
    
    func close() {
        coordinatorDelegate.finishAuthorizationFlow(isUserLogged: false)
    }
    
    func signUp(data: [AuthField]) {
        let playableInfo = PlayableItemInfo(name: camDelegate.itemName(),
                                            type: camDelegate.itemType())
        let signupEvent = AnalyticsEvents.tapStandardSignUpButton(playableInfo)
        ZAAppConnector.sharedInstance().analyticsDelegate.trackEvent(name: signupEvent.key,
                                                                     parameters: signupEvent.metadata)
        
        view.showLoadingScreen(true)
        if let data = validate(data: data) {
            camDelegate.signUp(authData: data, completion: { [weak self] (result) in
                guard let self = self else { return }
                switch result {
                case .success:
                    let signupSuccessEvent = AnalyticsEvents.standardSignUpSuccess(playableInfo)
                    ZAAppConnector.sharedInstance().analyticsDelegate.trackEvent(name: signupSuccessEvent.key,
                                                                                 parameters: signupSuccessEvent.metadata)
                    self.coordinatorDelegate.finishAuthorizationFlow(isUserLogged: true)
                case .failure(let error):
                    let signupFailureEvent = AnalyticsEvents.standardSignUpFailure(playableInfo)
                    ZAAppConnector.sharedInstance().analyticsDelegate.trackEvent(name: signupFailureEvent.key,
                                                                                 parameters: signupFailureEvent.metadata)
                    let viewAlertEvent = AnalyticsEvents.makeViewAlert(from: error)
                    ZAAppConnector.sharedInstance().analyticsDelegate.trackEvent(name: viewAlertEvent.key,
                                                                                 parameters: viewAlertEvent.metadata)
                    
                    self.view.showLoadingScreen(false)
                    self.view.showError(description: error.localizedDescription)
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
    
    func showFacebookAuthScreen() {
        let playableInfo = PlayableItemInfo(name: camDelegate.itemName(),
                                            type: camDelegate.itemType())
        let alternativeSignUpEvent = AnalyticsEvents.tapAlternativeSignUp(playableInfo)
        ZAAppConnector.sharedInstance().analyticsDelegate.trackEvent(name: alternativeSignUpEvent.key,
                                                                     parameters: alternativeSignUpEvent.metadata)
        view.showLoadingScreen(true)
        guard let facebookClient = ZAAppConnector.sharedInstance().facebookAccountKitDelegate else {
            self.view.showLoadingScreen(false)
            return
        }
        facebookClient.authorizeFacebook(true, readPermissions: ["public_profile", "email"],
                                         completion: { [weak self] (isUserLogged, error) in
            guard let self = self else { return }
            if isUserLogged {
                self.getFacebookUser(client: facebookClient)
            } else {
                self.view.showLoadingScreen(false)
                let failureEvent = AnalyticsEvents.alternativeSignUpFailure(playableInfo)
                ZAAppConnector.sharedInstance().analyticsDelegate.trackEvent(name: failureEvent.key,
                                                                             parameters: failureEvent.metadata)
                if let error = error {
                    self.view.showError(description: error.localizedDescription)
                }
            }
        })
    }
    
    func getFacebookUser(client: ZAAppDelegateConnectorFacebookAccountKitProtocol) {
        client.clientRequest(withGraphPath: "me", withParams: ["fields": "id, email"], withHTTPMethod: "GET",
                             withCompletionHandler: { [weak self] (_, result, error) in
            guard let self = self else { return }
            if let error = error {
                self.view.showLoadingScreen(false)
                self.view.showError(description: error.localizedDescription)
                return
            }
            if let fields = result as? [String: Any],
                let userId = fields["id"] as? String,
                let email = fields["email"] as? String {
                self.facebookSignUp(email: email, userId: userId)
            }
        })
    }
    
    func facebookSignUp(email: String, userId: String) {
        let playableInfo = PlayableItemInfo(name: camDelegate.itemName(),
                                            type: camDelegate.itemType())
        
        self.camDelegate.facebookSignUp(userData: (email: email, userId: userId), completion: { [weak self] (result) in
            guard let self = self else { return }
            self.view.showLoadingScreen(false)
            switch result {
            case .success:
                let successEvent = AnalyticsEvents.alternativeSignUpSuccess(playableInfo)
                ZAAppConnector.sharedInstance().analyticsDelegate.trackEvent(name: successEvent.key,
                                                                             parameters: successEvent.metadata)
                self.coordinatorDelegate.finishAuthorizationFlow(isUserLogged: true)
            case .failure(let error):
                let failureEvent = AnalyticsEvents.alternativeSignUpFailure(playableInfo)
                ZAAppConnector.sharedInstance().analyticsDelegate.trackEvent(name: failureEvent.key,
                                                                             parameters: failureEvent.metadata)
                self.view.showError(description: error.localizedDescription)
            }
        })
    }
}
