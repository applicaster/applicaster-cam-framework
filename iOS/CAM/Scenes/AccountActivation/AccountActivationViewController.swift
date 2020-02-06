//
//  CodeActivationViewController.swift
//  CAM
//
//  Created by Egor Brel on 1/22/20.
//

import UIKit
import ZappPlugins

class AccountActivationViewController: UIViewController {
    
    var loadingPopover = LoadingPopover.nibInstance()
    var codeActivationFields = [AuthField]()
    @IBOutlet var backgroundImageView: UIImageView!
    @IBOutlet var backButton: UIButton!
    @IBOutlet var closeButton: UIButton!
    @IBOutlet var logoImageView: UIImageView!
    @IBOutlet var titleLabel: UILabel!
    @IBOutlet var infoLabel: UILabel!
    @IBOutlet var codeActivationFieldsTable: UITableView!
    @IBOutlet var activateAccountButton: UIButton!
    @IBOutlet var resendCodeButton: UIButton!
    @IBOutlet var activationTableHeightConstraint: NSLayoutConstraint!
    var presenter: AccountActivationPresenter?

    var configDictionary: [String: String] {
        return presenter?.camDelegate.getPluginConfig() ?? [String: String]()
    }

    var codeActivationFieldsTableHeight: CGFloat {
        return CGFloat(codeActivationFields.count) * 48 + CGFloat((codeActivationFields.count - 1) * 7)
    }

    override func viewDidLoad() {
        super.viewDidLoad()
        presenter?.viewDidLoad()
        setupUI()
        subscribeKeyboardNotifications()
        configureElements()
    }

    override func viewDidLayoutSubviews() {
        super.viewDidLayoutSubviews()
        loadingPopover.frame = self.view.bounds
        setupConstraints()
    }
    
    override func viewDidAppear(_ animated: Bool) {
        super.viewDidAppear(animated)
    }
    
    func configureElements() {
        backgroundImageView.setStyle(asset: .background)
        backButton.setStyle(iconAsset: .backButton)
        closeButton.setStyle(iconAsset: .closeButton)
        logoImageView.setStyle(asset: .headerLogo)
        titleLabel.setStyle(config: configDictionary,
                            camTextKey: .accountActivationScreenTitleText,
                            style: .screenTitleFont)
        infoLabel.setStyle(config: configDictionary,
                           camTextKey: .accountActivationScreenDescriptionText,
                           style: .screenDescriptionFont)
        activateAccountButton.setStyle(config: configDictionary,
                                       backgroundAsset: .actionButton,
                                       camTitleKey: .accountActivationButtonText,
                                       style: .actionButtonFont)
        resendCodeButton.setStyle(config: configDictionary,
                                  camTitleKey: .resendAccountActivationCodeButtonText,
                                  style: .resendCodeButtonFont)
        
    }
    
    func setupConstraints() {
        activationTableHeightConstraint.constant = codeActivationFieldsTableHeight
        self.view.layoutIfNeeded()
    }
    
    func setupUI() {
        codeActivationFieldsTable.backgroundView = UIView()
        codeActivationFieldsTable.allowsSelection = false
        if let resendCodeText = configDictionary[CAMKeys.resendAccountActivationCodeButtonText.rawValue],
               resendCodeText.isEmpty {
            resendCodeButton.isHidden = true
        }
        closeButton.isHidden = presenter?.camDelegate.analyticsStorage().trigger == .appLaunch
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

    @IBAction func close(_ sender: Any) {
        presenter?.close()
    }

    @IBAction func backToPreviousScreen(_ sender: Any) {
        presenter?.backToPreviousScreen()
    }

    @IBAction func activateAccount(_ sender: Any) {
        hideKeyboard()
        presenter?.activateAccount(data: codeActivationFields)
    }

    @IBAction func resendCode(_ sender: Any) {
        presenter?.sendActivationCode(isResend: true)
    }

    deinit {
        NotificationCenter.default.removeObserver(self)
    }
}

// MARK: - Table Delegate

extension AccountActivationViewController: UITableViewDelegate, UITableViewDataSource {

    func tableView(_ tableView: UITableView, numberOfRowsInSection section: Int) -> Int {
        return codeActivationFields.count
    }

    func tableView(_ tableView: UITableView, heightForRowAt indexPath: IndexPath) -> CGFloat {
        if indexPath.row == codeActivationFields.count - 1 {
            return 48
        }
        return 55
    }

    func tableView(_ tableView: UITableView, cellForRowAt indexPath: IndexPath) -> UITableViewCell {
        guard let cell = tableView.dequeueReusableCell(withIdentifier: "AuthCell",
                                                       for: indexPath) as? AuthTableCell else {
                                                        return UITableViewCell()
        }
        cell.textField.setStyle(config: configDictionary, backgroundAsset: .authField, style: .inputFieldFont, placeholder: codeActivationFields[indexPath.row].hint)
        cell.configureInputField(data: codeActivationFields[indexPath.row])
        cell.backgroundColor = .clear
        cell.showPopover = { [weak self] in
            self?.showErrorPopover(config: self?.configDictionary ?? [String: String](),
                                   message: self?.codeActivationFields[indexPath.row].errorDescription,
                                   sourceView: cell)
        }

        cell.textChanged = { [weak self] text in
            self?.codeActivationFields[indexPath.row].state = .none
            self?.codeActivationFields[indexPath.row].errorDescription = ""
            self?.codeActivationFields[indexPath.row].text = text
        }
        return cell
    }
}

// MARK: - AccountActivationViewProtocol
extension AccountActivationViewController: AccountActivationViewProtocol {

    func updateTable(fields: [AuthField]) {
        codeActivationFields = fields
        codeActivationFieldsTable.reloadData()
    }

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
}

extension AccountActivationViewController: UIPopoverPresentationControllerDelegate {
    func adaptivePresentationStyle(for controller: UIPresentationController, traitCollection: UITraitCollection) -> UIModalPresentationStyle {
        return .none
    }
}
