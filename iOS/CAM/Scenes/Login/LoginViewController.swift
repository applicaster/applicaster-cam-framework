//
//  LoginViewController.swift
//  CAMFramework
//
//  Created by Egor Brel on 4/26/19.
//  Copyright © 2019 Egor Brel. All rights reserved.
//

import UIKit

class LoginViewController: UIViewController {
    var activeTextCell: AuthTableCell?
    let cellHeight: CGFloat = 48.0
    let cellSpacing: CGFloat = 7.0
    
    var loadingPopover = LoadingPopover.nibInstance()
    var authFields = [AuthField]()
    @IBOutlet var backgroundImageView: UIImageView!
    @IBOutlet var closeButton: UIButton!
    @IBOutlet var backButton: UIButton!
    @IBOutlet var logoImageView: UIImageView!
    
    @IBOutlet var titleLabel: UILabel!
    @IBOutlet var authFieldsTable: UITableView!
    @IBOutlet var loginButton: UIButton!
    @IBOutlet var resetPasswordButton: UIButton!
    
    @IBOutlet var socialNetworksContainer: UIView!
    
    @IBOutlet var rightSeparatorView: UIImageView!
    @IBOutlet var leftSeparatorView: UIImageView!
    @IBOutlet var alternateLabel: UILabel!
    @IBOutlet var socialNetworksLabel: UILabel!
    @IBOutlet var stackView: UIStackView!
    
    @IBOutlet var signUpContainer: UIView!
    @IBOutlet var signUpTextView: UITextView!
    
    @IBOutlet var camLinksContainer: CamLinksView!
    
    @IBOutlet var camLinksHeightConstraint: NSLayoutConstraint!
    @IBOutlet var inputContainerYConstraint: NSLayoutConstraint!
    @IBOutlet var socialNetworksContainerTopConstraint: NSLayoutConstraint!
    @IBOutlet var inputContainerHeightConstraint: NSLayoutConstraint!
    @IBOutlet var authFieldsTableHeightConstraint: NSLayoutConstraint!
    @IBOutlet var resetPasswordHeightConstraint: NSLayoutConstraint!
    @IBOutlet var signUpContainerBottom: NSLayoutConstraint!
    
    var configDictionary: [String: String] {
        return presenter?.camDelegate.getPluginConfig() ?? [String: String]()
    }
    var presenter: LoginPresenter?
    
    var isCustomLinksVisible: Bool {
        let firstLink = CamScreen.login.firstLink
        let secondLink = CamScreen.login.secondLink
        var isFirstLinkVisible = false
        var isSecondLinkVisible = false
    
        if let link = configDictionary[firstLink.link.rawValue], !link.isEmpty,
           let text = configDictionary[firstLink.text.rawValue], !text.isEmpty {
            isFirstLinkVisible = true
        }
        
        if let link = configDictionary[secondLink.link.rawValue], !link.isEmpty,
           let text = configDictionary[secondLink.text.rawValue], !text.isEmpty {
            isSecondLinkVisible = true
        }
        return isFirstLinkVisible || isSecondLinkVisible
    }
    
    var visibleAuthFieldsCount: Int {
        let centerFreeSpace = signUpContainer.frame.minY - logoImageView.frame.maxY
        let topSpace: CGFloat = 50.0
        let bottomSpace = socialNetworksContainer.isHidden ? 50 : socialNetworksContainer.frame.height + 20 // 20 - min spacing
        let inputComponentMaxHeight = centerFreeSpace - topSpace - bottomSpace
        let tableMaxHeight = inputComponentMaxHeight - resetPasswordButton.bounds.height - loginButton.bounds.height
        var maxCount = Int((tableMaxHeight - cellSpacing) / (cellHeight + cellSpacing))
        let fieldsCount = authFields.count
        if UIDevice.current.userInterfaceIdiom == .phone {
            maxCount = maxCount > 4 ? 4 : maxCount
        } else {
            maxCount = maxCount > 6 ? 6 : maxCount
        }
        return maxCount > fieldsCount ? fieldsCount : maxCount
    }
    
    var authFieldsTableHeight: CGFloat {
        let height = CGFloat(visibleAuthFieldsCount) * cellHeight + CGFloat(visibleAuthFieldsCount - 1) * cellSpacing
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
    
    override func viewDidAppear(_ animated: Bool) {
        super.viewDidAppear(animated)
        
        AnalyticsEvents.userFlow.append("Login")
    }
    
    func setupUI() {
        self.navigationController?.isNavigationBarHidden = true
        if let isHidden = presenter?.isRoot {
            backButton.isHidden = isHidden
        }
        closeButton.isHidden = presenter?.camDelegate.analyticsStorage().trigger == .appLaunch
        setupSignUpTextView()
        socialNetworksContainer.isHidden = !(configDictionary[CAMKeys.isAlternativeAuthenticationEnabled.rawValue]?.bool ?? false)
        authFieldsTable.backgroundView = UIView()
        authFieldsTable.allowsSelection = false
        setupCamLinks()
        setupResetPasswordButton()
        setupSocialNetworksContainer()
        configureElements()
    }
    
    func setupResetPasswordButton() {
        if let json = configDictionary[CAMKeys.authFields.rawValue],
           let data = json.data(using: .utf8),
           let resetPasswordText = configDictionary[CAMKeys.loginResetPasswordButtonText.rawValue],
           !resetPasswordText.isEmpty {
            if let jsonAuthFields = try? JSONDecoder().decode(AuthFields.self, from: data) {
                resetPasswordButton.isHidden = jsonAuthFields.resetPassword == nil
                return
            }
        }
        resetPasswordButton.isHidden = true
    }
    
    func setupSocialNetworksContainer() {
        let facebookButton = UIButton()
        facebookButton.setStyle(iconAsset: .facebook)
        facebookButton.translatesAutoresizingMaskIntoConstraints = false
        facebookButton.heightAnchor.constraint(equalToConstant: 36).isActive = true
        facebookButton.widthAnchor.constraint(equalToConstant: 36).isActive = true
        facebookButton.addTarget(self, action: #selector(facebookLogin), for: .touchUpInside)
       
        stackView.axis = .horizontal
        stackView.distribution = .equalCentering
        stackView.alignment = .center
        stackView.spacing = 20
        stackView.addArrangedSubview(facebookButton)
    }
    
    func setupCamLinks() {
        camLinksContainer.openLinkErrorAction = { [unowned self] in
            self.showAlert(description: self.configDictionary[CAMKeys.defaultAlertText.rawValue])
        }
        camLinksContainer.setupParameters(camScreen: .login, configDictionary: configDictionary)
    }
    
    func configureElements() {
        backgroundImageView.setStyle(asset: .background)
        closeButton.setStyle(iconAsset: .closeButton)
        backButton.setStyle(iconAsset: .backButton)
        logoImageView.setStyle(asset: .headerLogo)
        titleLabel.setStyle(config: configDictionary, camTextKey: .loginScreenTitleText, style: .screenTitleFont)
        loginButton.setStyle(config: configDictionary, backgroundAsset: .actionButton, camTitleKey: .loginButtonText, style: CAMStyles.actionButtonFont)
        resetPasswordButton.setStyle(config: configDictionary, camTitleKey: .loginResetPasswordButtonText, style: CAMStyles.resetPasswordFont)
        leftSeparatorView.setStyle(asset: .leftSeparator)
        rightSeparatorView.setStyle(asset: .rightSeparator)
        alternateLabel.setStyle(config: configDictionary, camTextKey: .separatorText, style: .separatorFont)
        socialNetworksLabel.setStyle(config: configDictionary,
                                     camTextKey: .alternativeAuthenticationPromtText,
                                     style: .alternativeAuthenticationFont)
    }
    
    func setupConstraints() {
        resetPasswordHeightConstraint.constant = resetPasswordButton.isHidden ? 12 : 33
        camLinksHeightConstraint.constant = isCustomLinksVisible ? 39 : 0
        signUpContainerBottom.constant = isCustomLinksVisible ? 0 : 39
        let inputContainerHeight = authFieldsTableHeight + loginButton.frame.height + resetPasswordButton.frame.height
        authFieldsTableHeightConstraint.constant = authFieldsTableHeight
        inputContainerHeightConstraint.constant = inputContainerHeight
        let inputContainerMinY = (self.view.frame.height - inputContainerHeight) / 2 - 50 // 50 - space from center
        let inputContainerMaxY = inputContainerMinY + inputContainerHeight
        if !socialNetworksContainer.isHidden {
            socialNetworksContainerTopConstraint.constant = (signUpContainer.frame.minY - inputContainerMaxY - 100) / 2
        } else {
            self.inputContainerYConstraint.constant = 0
        }
        self.view.layoutIfNeeded()
    }
    
    private func setupSignUpTextView() {
        let config = configDictionary
        
        let switchToLoginTextPrompt = NSAttributedString(string: config[CAMKeys.loginSingUpPromtText.rawValue] ?? "",
                                                         attributes: [.font: UIConfigurator.font(from: config,
                                                                                                 for: .promptFont),
                                                                      .foregroundColor: UIConfigurator.color(from: config,
                                                                                                             for: .promptFont)])
        
        let switchToLoginTextLink = NSAttributedString(string: config[CAMKeys.loginSingUpActionText.rawValue] ?? "",
                                                       attributes: [.font: UIConfigurator.font(from: config,
                                                                                               for: .linkFont),
                                                                    .foregroundColor: UIConfigurator.color(from: config,
                                                                                                           for: .linkFont),
                                                                    .underlineStyle: NSUnderlineStyle.single.rawValue])
        let paragraph = NSMutableParagraphStyle()
        paragraph.alignment = .center
        
        let switchToLoginText = NSMutableAttributedString()
        switchToLoginText.append(switchToLoginTextPrompt)
        switchToLoginText.append(switchToLoginTextLink)
        switchToLoginText.addAttribute(.paragraphStyle,
                                 value: paragraph,
                                 range: NSRange(location: 0, length: switchToLoginText.length))
        
        self.signUpTextView.attributedText = switchToLoginText
    }
    
    // MARK: - Keyboard
    
    @IBAction func hideKeyboard() {
        view.endEditing(true)
    }
    
    func subscribeKeyboardNotifications() {
        NotificationCenter.default.addObserver(self, selector: #selector(keyboardWillShow(_:)), name: UIResponder.keyboardWillShowNotification, object: nil)
        NotificationCenter.default.addObserver(self, selector: #selector(keyboardWillHide(_:)), name: UIResponder.keyboardWillHideNotification, object: nil)
    }
    
    @objc func keyboardWillShow(_ notification: NSNotification) {
        self.keyboardWillShow(notification, tableView: authFieldsTable, activeCell: activeTextCell)
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
    
    @IBAction func login(_ sender: UIButton) {
        hideKeyboard()
        presenter?.login(data: authFields)
    }
    
    @IBAction func switchToSignUpTapped(_ sender: UITapGestureRecognizer) {
        if let textView = sender.view as? UITextView {
            var location = sender.location(in: textView)
            location.x -= textView.textContainerInset.left
            location.y -= textView.textContainerInset.top
            
            let tappedCharacterIndex = textView.layoutManager.characterIndex(for: location,
                                                                             in: textView.textContainer,
                                                                             fractionOfDistanceBetweenInsertionPoints: nil)
            
            let linkRange = (textView.text as NSString).range(of: configDictionary[CAMKeys.loginSingUpActionText.rawValue]!)
            if linkRange.contains(tappedCharacterIndex) {
                hideKeyboard()
                presenter?.showSignUpScreen()
            }
        }
    }
    
    @objc private func facebookLogin() {
        presenter?.showFacebookAuthScreen()
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
        cell.textField.setStyle(config: configDictionary, backgroundAsset: .authField, style: .inputFieldFont, placeholder: authFields[indexPath.row].hint)
        cell.configureInputField(data: authFields[indexPath.row])
        cell.backgroundColor = .clear
        cell.showPopover = { [weak self] in
            self?.showErrorPopover(config: self?.configDictionary ?? [String: String](),
                                   message: self?.authFields[indexPath.row].errorDescription,
                                   sourceView: cell)
        }
        cell.textChanged = { [weak self] text in
            self?.authFields[indexPath.row].state = .none
            self?.authFields[indexPath.row].errorDescription = ""
            self?.authFields[indexPath.row].text = text
        }
        
        cell.updateFirstResponder = { [weak self] tableCell in
            self?.activeTextCell = tableCell
        }
        return cell
    }
}

// MARK: - Login View Protocol
extension LoginViewController: LoginViewProtocol {
    
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

extension LoginViewController: UIPopoverPresentationControllerDelegate {
    func adaptivePresentationStyle(for controller: UIPresentationController, traitCollection: UITraitCollection) -> UIModalPresentationStyle {
        return .none
    }
}
