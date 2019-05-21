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
    
    var configDictionary: [String: Any] {
        return presenter?.camDelegate?.getPluginConfig() ?? [String: Any]()
    }
    var presenter: ResetPasswordPresenter?
    
    // MARK: - Flow & UI Setup
    
    override func viewDidLoad() {
        super.viewDidLoad()
        configureElements()
    }
    
    override func viewDidLayoutSubviews() {
        super.viewDidLayoutSubviews()
        loadingPopover.frame = self.view.bounds
        setupConstraints()
    }
    
    func configureElements() {
        backgroundImageView.configureWith(bgImageName: configDictionary[CAMKeys.backgroundImage.rawValue] as? String)
        backButton.configureWith(bgImageName: configDictionary[CAMKeys.backButtonImage.rawValue] as? String)
        closeButton.configureWith(bgImageName: configDictionary[CAMKeys.closeButtonImage.rawValue] as? String)
        logoImageView.configureWith(bgImageName: configDictionary[CAMKeys.headerLogo.rawValue] as? String)
        titleLabel.configureWith(text: configDictionary[CAMKeys.passwordResetTitleText.rawValue] as? String)
        infoLabel.configureWith(text: configDictionary[CAMKeys.passwordResetInfoText.rawValue] as? String)
        emailTextField.configureWith(text: configDictionary[CAMKeys.passwordInputFieldPlaceholder.rawValue] as? String)
        resetButton.configureWith(text: configDictionary[CAMKeys.passwordResetButtonText.rawValue] as? String,
                                  bgImageName: configDictionary[CAMKeys.passwordResetButtonImage.rawValue] as? String)
    }
    
    func setupConstraints() {
        titleTopSpaceConstraint.constant = (emailTextField.frame.minY - logoImageView.frame.maxY) / 2 - 46
        self.view.layoutIfNeeded()
    }
    
    // MARK: - Keyboard
    
    @IBAction func hideKeyboard() {
        view.endEditing(true)
    }
    
    // MARK: - Actions
    
    @IBAction func resetPassword(_ sender: UIButton) {
        hideKeyboard()
        guard let email = emailTextField.text else {
            let message = configDictionary[CAMKeys.emptyFieldsMessage.rawValue] as? String
            showError(description: message)
            return
        }
        if email.isEmpty {
            let message = configDictionary[CAMKeys.emptyFieldsMessage.rawValue] as? String
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
        let alert = UIAlertController(title: "Error", message: description, preferredStyle: .alert)
        alert.addAction(UIAlertAction(title: "Ok", style: .default, handler: nil))
        self.present(alert, animated: true, completion: nil)
    }
    
    func showConfirmationScreenIfNeeded() {
        if configDictionary[CAMKeys.passwordAlertTitleText.rawValue] != nil &&
           configDictionary[CAMKeys.passwordAlertInfoText.rawValue] != nil &&
           configDictionary[CAMKeys.passwordAlertButtonText.rawValue] != nil {
            let confirmationPopover = ConfirmationPopover.nibInstance()
            confirmationPopover.frame = self.view.frame
            confirmationPopover.buttonPressedAction = { [weak self] in
                self?.presenter?.backToPreviousScreen()
            }
            confirmationPopover.titleLabel.configureWith(text: configDictionary[CAMKeys.passwordAlertTitleText.rawValue] as? String)
            confirmationPopover.descriptionLabel.configureWith(text: configDictionary[CAMKeys.passwordAlertInfoText.rawValue] as? String)
            confirmationPopover.actionButton.configureWith(text: configDictionary[CAMKeys.passwordAlertButtonText.rawValue] as? String,
                                                           bgImageName: configDictionary[CAMKeys.passwordAlertButtonImage.rawValue] as? String)
            self.view.addSubview(confirmationPopover)
        } else {
            presenter?.backToPreviousScreen()
        }
    }
}
