//
//  LoginViewController.swift
//  CAMFramework
//
//  Created by Egor Brel on 4/26/19.
//  Copyright © 2019 Egor Brel. All rights reserved.
//

import UIKit

class LoginViewController: UIViewController {
    
    var loadingPopover = LoadingPopover.nibInstance()
    var authFields = [AuthField]()
    @IBOutlet var backgroundImageView: UIImageView!
    @IBOutlet var backButton: UIButton!
    @IBOutlet var closeButton: UIButton!
    @IBOutlet var logoImageView: UIImageView!
    
    @IBOutlet var titleLabel: UILabel!
    
    @IBOutlet var authFieldsTable: UITableView!
    @IBOutlet var loginButton: UIButton!
    @IBOutlet var resetPasswordButton: UIButton!
    
    @IBOutlet var restoreContainer: UIView!
    @IBOutlet var restoreCheckBox: UICheckBox!
    @IBOutlet var restoreInfoLabel: UILabel!
    
    @IBOutlet var socialNetworksContainer: UIView!
    @IBOutlet var alternateLabel: UILabel!
    @IBOutlet var socialNetworksLabel: UILabel!
    
    @IBOutlet var signUpContainer: UIView!
    @IBOutlet var signUpButton: UIButton!
    
    @IBOutlet var inputContainerYConstraint: NSLayoutConstraint!
    @IBOutlet var socialNetworksContainerTopConstraint: NSLayoutConstraint!
    @IBOutlet var inputContainerHeightConstraint: NSLayoutConstraint!
    @IBOutlet var authFieldsTableHeightConstraint: NSLayoutConstraint!

    var configDictionary: [String: String] {
        return presenter?.camDelegate?.getPluginConfig() ?? [String: String]()
    }
    var presenter: LoginPresenter?
    
    var visibleAuthFieldsCount: Int {
        let centerFreeSpace = signUpContainer.frame.minY - logoImageView.frame.maxY
        let topSpace: CGFloat = 50.0
        var bottomSpace = restoreContainer.isHidden ? 0 : restoreContainer.frame.height
        bottomSpace += socialNetworksContainer.isHidden ? 0 : socialNetworksContainer.frame.height + 20 // 20 - min spacing
        bottomSpace = bottomSpace == 0 ? 50 : bottomSpace
        let inputComponentMaxHeight = centerFreeSpace - topSpace - bottomSpace
        let tableMaxHeight = inputComponentMaxHeight - 33 - 46
        var maxCount = Int((tableMaxHeight - 7) / (48 + 7))
        let fieldsCount = authFields.count
        if UIDevice.current.userInterfaceIdiom == .phone {
            maxCount = maxCount > 4 ? 4 : maxCount
        } else {
            maxCount = maxCount > 6 ? 6 : maxCount
        }
        return maxCount > fieldsCount ? fieldsCount : maxCount
    }
    
    var authFieldsTableHeight: CGFloat {
        let height = CGFloat(visibleAuthFieldsCount * 48 + (visibleAuthFieldsCount - 1) * 7)
        return height
    }
    
    // MARK: - Flow & UI Setup
    
    override func viewDidLoad() {
        super.viewDidLoad()
        setupUI()
        subscribeKeyboardNotifications()
        presenter?.viewDidLoad()
    }

    override func viewDidLayoutSubviews() {
        super.viewDidLayoutSubviews()
        loadingPopover.frame = self.view.bounds
        setupConstraints()
        authFieldsTable.isScrollEnabled = authFieldsTable.contentSize.height > authFieldsTable.frame.height
    }
    
    func setupUI() {
        self.navigationController?.isNavigationBarHidden = true
        if let isHidden = presenter?.isRoot {
            backButton.isHidden = isHidden
        }
        signUpButton.titleLabel?.numberOfLines = 0
        signUpButton.titleLabel?.textAlignment = .center
        restoreContainer.isHidden = true
        socialNetworksContainer.isHidden = !(configDictionary[CAMKeys.facebookLoginEnabled.rawValue] ?? "false").bool
        resetPasswordButton.isHidden = !(configDictionary[CAMKeys.authFields.rawValue] ?? "false").bool
        authFieldsTable.backgroundView = UIView()
        authFieldsTable.allowsSelection = false
        setupResetPasswordButton()
        configureElements()
    }
    
    func setupResetPasswordButton() {
        if let json = configDictionary[CAMKeys.authFields.rawValue],
            let data = json.data(using: .utf8) {
            if let jsonAuthFields = try? JSONDecoder().decode(AuthFields.self, from: data) {
                resetPasswordButton.isHidden = jsonAuthFields.password == nil
                return
            }
        }
        resetPasswordButton.isHidden = true
    }
    
    func configureElements() {
        backgroundImageView.setZappStyle(withAsset: .backgroundImage)
        backButton.setZappStyle(withIconAsset: .backButtonImage)
        closeButton.setZappStyle(withIconAsset: .closeButtonImage)
        logoImageView.setZappStyle(withAsset: .headerLogo)
        titleLabel.setZappStyle(text: configDictionary[CAMKeys.loginScreenTitleText.rawValue], style: .screenTitle)
        loginButton.setZappStyle(backgroundAsset: .loginButtonImage,
                                 title: configDictionary[CAMKeys.loginButtonText.rawValue],
                                 style: .actionButton)
        resetPasswordButton.setZappStyle(title: configDictionary[CAMKeys.loginResetPasswordButtonText.rawValue],
                                         style: .resetPassword)
        alternateLabel.setZappStyle(text: configDictionary[CAMKeys.separatorText.rawValue], style: .separator)
        socialNetworksLabel.setZappStyle(text: configDictionary[CAMKeys.alternativeLoginPromtText.rawValue],
                                         style: .alternativeLoginText)
        signUpButton.setAttributedZappStyle(attributedTitle: [(style: .promtText,
                                                               string: configDictionary[CAMKeys.loginSingUpPromtText.rawValue] ?? "",
                                                               additionalAttributes: nil),
                                                              (style: .promtAction,
                                                               string: "\n\(configDictionary[CAMKeys.loginSingUpActionText.rawValue] ?? "")",
                                                               additionalAttributes: nil)])
        signUpContainer.setZappStyle(withBackgroundColor: .alternateActionBannerColor)
    }
    
    func setupConstraints() {
        let inputContainerHeight = authFieldsTableHeight + loginButton.frame.height + resetPasswordButton.frame.height
        authFieldsTableHeightConstraint.constant = authFieldsTableHeight
        inputContainerHeightConstraint.constant = inputContainerHeight
        let inputContainerMinY = (self.view.frame.height - inputContainerHeight) / 2 - 50 // 50 - space from center
        let inputContainerMaxY = inputContainerMinY + inputContainerHeight
        if !socialNetworksContainer.isHidden {
            let restoreContainerHeight = restoreContainer.isHidden ? 0 : restoreContainer.frame.height
            socialNetworksContainerTopConstraint.constant = (signUpContainer.frame.minY - inputContainerMaxY + restoreContainerHeight - 100) / 2
        } else {
            if restoreContainer.isHidden {
                self.inputContainerYConstraint.constant = 0
            }
        }
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
    
    @IBAction func close(_ sender: UIButton) {
        presenter?.close()
    }
    
    @IBAction func backToPreviousScreen(_ sender: UIButton) {
        presenter?.backToPreviousScreen()
    }
    
    @IBAction func resetPassword(_ sender: Any) {
        hideKeyboard()
        presenter?.showResetPasswordScreen()
    }
    
    @IBAction func showSignUpScreen(_ sender: Any) {
        hideKeyboard()
        presenter?.showSignUpScreen()
    }
    
    @IBAction func login(_ sender: UIButton) {
        hideKeyboard()
        var result = [(key: String, value: String?)]()
        for obj in authFields {
            if obj.mandatory && (obj.text ?? "").isEmpty {
                let message = configDictionary[CAMKeys.emptyFieldsMessage.rawValue]
                showError(description: message)
                return
            }
            result.append((key: (obj.key ?? ""), value: obj.text))
        }
        presenter?.login(data: result)
    }
    
    deinit {
        NotificationCenter.default.removeObserver(self)
    }
}

// MARK: - Table Delegate
extension LoginViewController: UITableViewDelegate, UITableViewDataSource {
    
    func tableView(_ tableView: UITableView, numberOfRowsInSection section: Int) -> Int {
        return authFields.count
    }
    
    func tableView(_ tableView: UITableView, heightForRowAt indexPath: IndexPath) -> CGFloat {
        if indexPath.row == authFields.count - 1 {
            return 48
        }
        return 55
    }
    
    func tableView(_ tableView: UITableView, cellForRowAt indexPath: IndexPath) -> UITableViewCell {
        guard let cell = tableView.dequeueReusableCell(withIdentifier: "AuthCell",
                                                       for: indexPath) as? AuthTableCell else {
            return UITableViewCell()
        }
        cell.textField.setZappStyle(backgroundAsset: .authFieldImage,
                                    textStyle: .inputField,
                                    placeholder: authFields[indexPath.row].hint)
        cell.textField.configureInputField(data: authFields[indexPath.row])
        cell.backgroundColor = .clear
        cell.textChanged = { [weak self] text in
            self?.authFields[indexPath.row].text = text
        }
        return cell
    }
}

extension LoginViewController: LoginViewProtocol {
    
    // MARK: - Login View Protocol
    
    func updateTable(fields: [AuthField]) {
        authFields = fields
        authFieldsTable.reloadData()
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
