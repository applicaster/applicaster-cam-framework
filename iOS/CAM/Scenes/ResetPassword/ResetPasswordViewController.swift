//
//  ResetPasswordViewController.swift
//  CAMFramework
//
//  Created by Egor Brel on 4/30/19.
//  Copyright © 2019 Egor Brel. All rights reserved.
//

import UIKit

class ResetPasswordViewController: UIViewController {

    var loadingPopover = LoadingPopover.nibInstance()
    @IBOutlet var backgroundImageView: UIImageView!
    @IBOutlet var backButton: UIButton!
    @IBOutlet var closeButton: UIButton!
    @IBOutlet var logoImageView: UIImageView!
    @IBOutlet var titleLabel: UILabel!
    @IBOutlet var infoLabel: UILabel!
    
    @IBOutlet var emailTextField: UITextField!
    @IBOutlet var resetButton: UIButton!
    
    @IBOutlet var titleTopSpaceConstraint: NSLayoutConstraint!
    
    var configDictionary: [String: String] {
        return presenter?.camDelegate?.getPluginConfig() ?? [String: String]()
    }
    var presenter: ResetPasswordPresenter?
    
    // MARK: - Flow & UI Setup
    
    override func viewDidLoad() {
        super.viewDidLoad()
        subscribeKeyboardNotifications()
        configureElements()
    }
    
    override func viewDidLayoutSubviews() {
        super.viewDidLayoutSubviews()
        loadingPopover.frame = self.view.bounds
        setupConstraints()
    }
    
    func configureElements() {
        backgroundImageView.setZappStyle(withAsset: .backgroundImage)
        backButton.setZappStyle(withIconAsset: .backButtonImage)
        closeButton.setZappStyle(withIconAsset: .closeButtonImage)
        logoImageView.setZappStyle(withAsset: .headerLogo)
        titleLabel.setZappStyle(text: configDictionary[CAMKeys.passwordResetTitleText.rawValue], style: .screenTitle)
        infoLabel.setZappStyle(text: configDictionary[CAMKeys.passwordResetInfoText.rawValue], style: .screenDescription)
        emailTextField.setZappStyle(backgroundAsset: .authFieldImage, textStyle: .inputField, placeholder:
                                    configDictionary[CAMKeys.passwordInputFieldPlaceholder.rawValue])
        resetButton.setZappStyle(backgroundAsset: .passwordResetButtonImage, title: configDictionary[CAMKeys.passwordResetButtonText.rawValue], style: .actionButton)
    }
    
    func setupConstraints() {
        titleTopSpaceConstraint.constant = (emailTextField.frame.minY - logoImageView.frame.maxY) / 2 - 46
        self.view.layoutIfNeeded()
    }
    
    // MARK: - Keyboard
    
    @IBAction func hideKeyboard() {
        view.endEditing(true)
    }
    
    func subscribeKeyboardNotifications() {
        NotificationCenter.default.addObserver(self, selector: #selector(keyboardNotification(_:)), name: UIResponder.keyboardWillShowNotification, object: nil)
        NotificationCenter.default.addObserver(self, selector: #selector(keyboardNotification(_:)), name: UIResponder.keyboardWillHideNotification, object: nil)
    }
    
    @objc func keyboardNotification(_ notification: NSNotification) {
        if notification.name == UIResponder.keyboardWillShowNotification {
            setViewYCoordinate(value: -100)
        } else {
            setViewYCoordinate(value: 0)
        }
    }
    
    func setViewYCoordinate(value: CGFloat) {
        if self.view.frame.origin.y > value || value == 0 {
            self.view.frame.origin.y = value
        }
    }
    
    // MARK: - Actions
    
    @IBAction func resetPassword(_ sender: UIButton) {
        hideKeyboard()
        guard let email = emailTextField.text else {
            let message = configDictionary[CAMKeys.emptyFieldsMessage.rawValue]
            showError(description: message)
            return
        }
        if email.isEmpty {
            let message = configDictionary[CAMKeys.emptyFieldsMessage.rawValue]
            showError(description: message)
            return
        }
        presenter?.resetPassword(email: email)
    }
    
    @IBAction func backToPreviousScreen(_ sender: UIButton) {
        presenter?.backToPreviousScreen()
    }
    
    @IBAction func close(_ sender: UIButton) {
        presenter?.close()
    }
    
    deinit {
        NotificationCenter.default.removeObserver(self)
    }
}

// MARK: - ResetPasswordViewProtocol
extension ResetPasswordViewController: ResetPasswordViewProtocol {
    
    func showLoadingScreen(_ show: Bool) {
        if show {
            self.view.addSubview(loadingPopover)
        } else {
            loadingPopover.removeFromSuperview()
        }
    }
    
    func showError(description: String?) {
        self.showAlert(description: description)
    }
    
    func showConfirmationScreenIfNeeded() {
        if let title = configDictionary[CAMKeys.passwordAlertTitleText.rawValue],
           let description = configDictionary[CAMKeys.passwordAlertInfoText.rawValue],
           let buttonText = configDictionary[CAMKeys.alertButtonText.rawValue] {
            self.showConfirmationScreen(title: title, description: description, buttonText: buttonText, action: { [weak self] in
                self?.presenter?.backToPreviousScreen()
            })
        } else {
            presenter?.backToPreviousScreen()
        }
    }
}

extension ResetPasswordViewController: UITextFieldDelegate {
    
    func textFieldShouldReturn(_ textField: UITextField) -> Bool {
        return textField.resignFirstResponder()
    }
}
