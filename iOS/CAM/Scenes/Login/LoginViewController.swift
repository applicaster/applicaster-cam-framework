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
    @IBOutlet var socialNetworksContainerTopSpaceConstraint: NSLayoutConstraint!
    @IBOutlet var inputComponentHeightConstraint: NSLayoutConstraint!
    @IBOutlet var authFieldsTableHeightConstraint: NSLayoutConstraint!

    var configDictionary: Dictionary<String, Any>? {
        return presenter?.camDelegate?.getPluginConfig()
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
    
    //MARK: - Flow & UI Setup
    
    override func loadView() {
        super.loadView()
        setupUI()
    }
    
    override func viewDidLoad() {
        super.viewDidLoad()
    }

    override func viewDidLayoutSubviews() {
        super.viewDidLayoutSubviews()
        loadingPopover.frame = self.view.bounds
        setupConstraints()
        authFieldsTable.isScrollEnabled = authFieldsTable.contentSize.height > authFieldsTable.frame.height
    }
    
    func setupUI() {
        self.navigationController?.isNavigationBarHidden = true
        restoreContainer.isHidden = true
        socialNetworksContainer.isHidden = true
        let tapGesture = UITapGestureRecognizer(target: self, action: #selector(hideKeyboard))
        view.addGestureRecognizer(tapGesture)
        setupTable()
        configureElements()
    }
    
    func setupTable() {
        if let json = configDictionary?[CAMKeys.auth_fields.rawValue] as? String, let data = json.data(using: .utf8) {
            if let jsonAuthFields = try? JSONDecoder().decode(AuthFields.self, from: data), let loginFields = jsonAuthFields.login {
                authFields = loginFields
            }
        }
        
        if authFields.count == visibleAuthFieldsCount {
            authFieldsTable.isScrollEnabled = false
        }
    }
    
    func configureElements() {
        let array: [(UIView, UIElement)] = [(backgroundImageView, .backgroungImageView), (backButton, .backButton),
                                            (closeButton, .closeButton), (logoImageView, .headerImageView),
                                            (titleLabel, .loginTitleLabel), (loginButton, .loginButton),
                                            (resetPasswordButton, .loginResetPasswordButton), (alternateLabel, .separatorLabel),
                                            (socialNetworksLabel, .networksAuthLabel), (signUpContainer, .bottomBannerView),
                                            (signUpButton, .loginAlternativeActionButton)]
        array.forEach {
            UIConfigurator.configureView(type: $0.1, view: $0.0, dict: configDictionary)
        }
    }
    
    func setupConstraints() {
        let inputComponentHeight = authFieldsTableHeight + loginButton.frame.height + resetPasswordButton.frame.height
        authFieldsTableHeightConstraint.constant = authFieldsTableHeight
        inputComponentHeightConstraint.constant = authFieldsTableHeight + loginButton.frame.height + resetPasswordButton.frame.height
        let inputComponentMinY = (self.view.frame.height - inputComponentHeight) / 2 - 50 // 50 - space from center
        let inputComponentMaxY = inputComponentMinY + inputComponentHeight
        if !socialNetworksContainer.isHidden {
            let restoreContainerHeight = restoreContainer.isHidden ? 0 : restoreContainer.frame.height
            socialNetworksContainerTopSpaceConstraint.constant = (signUpContainer.frame.minY - inputComponentMaxY + restoreContainerHeight - 100) / 2
        } else {
            if restoreContainer.isHidden {
                self.inputContainerYConstraint.constant = 0
            }
        }
        self.view.layoutIfNeeded()
    }
    
    //MARK: - Keyboard
    
    @objc func hideKeyboard() {
        view.endEditing(true)
    }
    
    //MARK: - Actions
    
    @IBAction func close(_ sender: UIButton) {
        presenter?.close()
    }
    
    @IBAction func backToPreviousScreen(_ sender: UIButton) {
        presenter?.backToPreviousScreen()
    }
    
    @IBAction func resetPassword(_ sender: Any) {
        presenter?.showResetPasswordScreen()
    }
    
    @IBAction func showSignUpScreen(_ sender: Any) {
        presenter?.showSignUpScreen()
    }
    
    @IBAction func login(_ sender: UIButton) {
        hideKeyboard()
        var result = [(key: String, value: String?)]()
        for obj in authFields {
            if obj.mandatory && (obj.text ?? "").isEmpty {
                showError(description: "Mandatory field is Empty!")
                return
            }
            result.append((key: (obj.key ?? ""), value: obj.text))
        }
        presenter?.login(data: result)
    }
}

extension LoginViewController: UITableViewDelegate, UITableViewDataSource {
    // MARK: - Table Delegate
    
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
        guard let cell = tableView.dequeueReusableCell(withIdentifier: "LoginAuthCell", for: indexPath) as? LoginAuthTableCell else {
            return UITableViewCell()
        }
        UIConfigurator.configureAuthField(view: cell.textField, data: authFields[indexPath.row], dict: configDictionary)
        cell.backgroundColor = .clear
        cell.textChanged = { text in
            self.authFields[indexPath.row].text = text
        }
        return cell
    }
}

extension LoginViewController: LoginViewProtocol {
    // MARK: - Login View Protocol
    
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
}
