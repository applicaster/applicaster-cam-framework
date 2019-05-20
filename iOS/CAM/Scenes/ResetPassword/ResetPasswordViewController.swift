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
    
    var presenter: ResetPasswordPresenter?
    
    //MARK: - Flow & UI Setup
    
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
        let configDictionary = presenter?.camDelegate?.getPluginConfig()
        let array: [(UIView, UIElement)] = [(backgroundImageView, .backgroungImageView), (backButton, .backButton),
                                            (closeButton, .closeButton), (logoImageView, .headerImageView),
                                            (titleLabel, .resetPasswordTitleLabel), (infoLabel, .resetPasswordInfoLabel),
                                            (emailTextField, .resetPasswordTextField),(resetButton, .resetPasswordButton)]
        array.forEach {
            UIConfigurator.configureView(type: $0.1, view: $0.0, dict: configDictionary)
        }
    }
    
    func setupConstraints() {
        titleTopSpaceConstraint.constant = (emailTextField.frame.minY - logoImageView.frame.maxY) / 2 - 46
        self.view.layoutIfNeeded()
    }
    
    //MARK: - Keyboard
    
    @IBAction func hideKeyboard() {
        view.endEditing(true)
    }
    
    // MARK: - Actions
    
    @IBAction func resetPassword(_ sender: UIButton) {
        hideKeyboard()
        guard let email = emailTextField.text else {
            showError(description: "Mandatory field is Empty!")
            return
        }
        if email.isEmpty {
            showError(description: "Mandatory field is Empty!")
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

extension ResetPasswordViewController: ResetPasswordViewProtocol {
    
    // MARK: - ResetPasswordViewProtocol
    
    func showLoadingScreen(_ show: Bool) {
        if show {
            self.view.addSubview(loadingPopover)
        } else {
            loadingPopover.removeFromSuperview()
        }
    }
    
    func showError(description: String?) {
        let alert = UIAlertController(title: "Error", message: description, preferredStyle: UIAlertController.Style.alert)
        alert.addAction(UIAlertAction(title: "Ok", style: .default, handler: nil))
        self.present(alert, animated: true, completion: nil)
    }
    
    func showConfirmationScreenIfNeeded() {
        let dictionary = presenter?.camDelegate?.getPluginConfig()
        if let _ = dictionary?[CAMKeys.password_alert_title_text.rawValue] as? String,
           let _ = dictionary?[CAMKeys.password_alert_info_text.rawValue] as? String,
           let _ = dictionary?[CAMKeys.password_alert_button_text.rawValue] as? String {
            let confirmationPopover = ConfirmationPopover.nibInstance()
            confirmationPopover.frame = self.view.frame
            confirmationPopover.buttonPressedAction = { [weak self] in
                self?.presenter?.backToPreviousScreen()
            }
            UIConfigurator.configureView(type: .passwordAlert, view: confirmationPopover, dict: dictionary)
            self.view.addSubview(confirmationPopover)
        } else {
            presenter?.backToPreviousScreen()
        }
    }
}

