//
//  UpdatePasswordViewController.swift
//  CAM
//
//  Created by Egor Brel on 1/29/20.
//

import UIKit

class UpdatePasswordViewController: UIViewController {

    var loadingPopover = LoadingPopover.nibInstance()
    var updatePasswordFields = [AuthField]()
    @IBOutlet var scrollView: UIScrollView!
    @IBOutlet var backgroundImageView: UIImageView!
    @IBOutlet var backButton: UIButton!
    @IBOutlet var closeButton: UIButton!
    @IBOutlet var logoImageView: UIImageView!
    @IBOutlet var titleLabel: UILabel!
    @IBOutlet var infoLabel: UILabel!
    @IBOutlet var updatePasswordFieldsTable: UITableView!
    @IBOutlet var updatePasswordButton: UIButton!
    
    @IBOutlet var tableHeightConstraint: NSLayoutConstraint!
    
    
    var configDictionary: [String: String] {
        return presenter?.camDelegate.getPluginConfig() ?? [String: String]()
    }
    
    var presenter: UpdatePasswordPresenter?
    
    var resetPasswordFieldsTableHeight: CGFloat {
        return CGFloat(updatePasswordFields.count) * 48 + CGFloat((updatePasswordFields.count - 1) * 7)
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
        
        AnalyticsEvents.userFlow.append("Reset Password")
    }
    
    func configureElements() {
        backgroundImageView.setStyle(asset: .background)
        backButton.setStyle(iconAsset: .backButton)
        closeButton.setStyle(iconAsset: .closeButton)
        logoImageView.setStyle(asset: .headerLogo)
        titleLabel.setStyle(config: configDictionary, camTextKey: .passwordUpdateTitleText, style: .screenTitleFont)
        infoLabel.setStyle(config: configDictionary, camTextKey: .passwordUpdateInfoText,
                               style: .screenDescriptionFont)
        updatePasswordButton.setStyle(config: configDictionary,
                             backgroundAsset: .actionButton,
                             camTitleKey: .passwordUpdateButtonText,
                             style: .actionButtonFont)
    }
    
    func setupConstraints() {
        tableHeightConstraint.constant = resetPasswordFieldsTableHeight
        self.view.layoutIfNeeded()
    }
    
    func setupUI() {
        updatePasswordFieldsTable.backgroundView = UIView()
        updatePasswordFieldsTable.allowsSelection = false
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
    
    @IBAction func updatePassword(_ sender: UIButton) {
        hideKeyboard()
        presenter?.updatePassword(data: updatePasswordFields)
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
extension UpdatePasswordViewController: ResetPasswordViewProtocol {
    
    func updateTable(fields: [AuthField]) {
        updatePasswordFields = fields
        updatePasswordFieldsTable.reloadData()
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
    
    func showConfirmationScreenIfNeeded() {
        if let _ = configDictionary[CAMKeys.passwordAlertTitleText.rawValue],
           let _ = configDictionary[CAMKeys.passwordAlertInfoText.rawValue],
           let _ = configDictionary[CAMKeys.alertButtonText.rawValue] {
            self.showConfirmationScreen(config: configDictionary,
                                        titleKey: .passwordAlertTitleText,
                                        descriptionKey: .passwordAlertInfoText,
                                        buttonKey: .alertButtonText,
                                        action: { [weak self] in
                self?.presenter?.finishFlow()
            })
        } else {
            presenter?.finishFlow()
        }
    }
}

// MARK: - Table Delegate

extension UpdatePasswordViewController: UITableViewDelegate, UITableViewDataSource {
    
    func tableView(_ tableView: UITableView, numberOfRowsInSection section: Int) -> Int {
        return updatePasswordFields.count
    }
    
    func tableView(_ tableView: UITableView, heightForRowAt indexPath: IndexPath) -> CGFloat {
        if indexPath.row == updatePasswordFields.count - 1 {
            return 48
        }
        return 55
    }
    
    func tableView(_ tableView: UITableView, cellForRowAt indexPath: IndexPath) -> UITableViewCell {
        guard let cell = tableView.dequeueReusableCell(withIdentifier: "AuthCell",
                                                       for: indexPath) as? AuthTableCell else {
                                                        return UITableViewCell()
        }
        cell.textField.setStyle(config: configDictionary, backgroundAsset: .authField, style: .inputFieldFont, placeholder: updatePasswordFields[indexPath.row].hint)
        cell.configureInputField(data: updatePasswordFields[indexPath.row])
        cell.backgroundColor = .clear
        cell.showPopover = { [weak self] in
            self?.showErrorPopover(config: self?.configDictionary ?? [String: String](),
                                   message: self?.updatePasswordFields[indexPath.row].errorDescription,
                                   sourceView: cell)
        }
        
        cell.textChanged = { [weak self] text in
            self?.updatePasswordFields[indexPath.row].state = .none
            self?.updatePasswordFields[indexPath.row].errorDescription = ""
            self?.updatePasswordFields[indexPath.row].text = text
        }
        return cell
    }
}

extension UpdatePasswordViewController: UIPopoverPresentationControllerDelegate {
    func adaptivePresentationStyle(for controller: UIPresentationController, traitCollection: UITraitCollection) -> UIModalPresentationStyle {
        return .none
    }
}
