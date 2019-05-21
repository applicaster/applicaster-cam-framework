//
//  SignUpViewController.swift
//  CAM
//
//  Created by Egor Brel on 4/30/19.
//

import UIKit

class SignUpViewController: UIViewController {
    
    var loadingPopover = LoadingPopover.nibInstance()
    var authFields = [AuthField]()
    
    @IBOutlet var backgroundImageView: UIImageView!
    
    @IBOutlet var backButton: UIButton!
    @IBOutlet var closeButton: UIButton!
    
    @IBOutlet var logoImageView: UIImageView!
    @IBOutlet var titleLabel: UILabel!
    
    @IBOutlet var authFieldsTable: UITableView!
    @IBOutlet var signUpButton: UIButton!
    
    @IBOutlet var restoreContainer: UIView!
    @IBOutlet var restoreCheckBox: UICheckBox!
    @IBOutlet var restoreInfoLabel: UILabel!
    
    @IBOutlet var socialNetworksContainer: UIView!
    @IBOutlet var alternateLabel: UILabel!
    @IBOutlet var socialNetworksLabel: UILabel!
    
    @IBOutlet var loginContainer: UIView!
    @IBOutlet var loginButton: UIButton!
    
    @IBOutlet var authFieldsTableHeightConstraint: NSLayoutConstraint!
    @IBOutlet var socialNetworksContainerTopConstraint: NSLayoutConstraint!
    @IBOutlet var inputContainerYConstraint: NSLayoutConstraint!
    @IBOutlet var inputContainerHeightConstraint: NSLayoutConstraint!
    
    var configDictionary: [String: Any] {
        return presenter?.camDelegate?.getPluginConfig() ?? [String: Any]()
    }
    var presenter: SignUpPresenter?
    
    var visibleAuthFieldsCount: Int {
        let centerFreeSpace = loginContainer.frame.minY - logoImageView.frame.maxY
        let topSpace: CGFloat = 50.0
        var bottomSpace = restoreContainer.isHidden ? 0 : restoreContainer.frame.height
        bottomSpace += socialNetworksContainer.isHidden ? 0 : socialNetworksContainer.frame.height + 20 // 20 - min spacing
        bottomSpace = bottomSpace == 0 ? 50 : bottomSpace
        let inputComponentMaxHeight = centerFreeSpace - topSpace - bottomSpace
        let tableMaxHeight = inputComponentMaxHeight - 13 - 46
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
        restoreContainer.isHidden = true
        socialNetworksContainer.isHidden = (configDictionary[CAMKeys.facebookLoginEnabled.rawValue] as? String ?? "false").bool
        authFieldsTable.backgroundView = UIView()
        configureElements()
    }
    
    func setupConstraints() {
        let inputContainerHeight = authFieldsTableHeight + signUpButton.frame.height + 13
        authFieldsTableHeightConstraint.constant = authFieldsTableHeight
        inputContainerHeightConstraint.constant = inputContainerHeight
        let inputContainerMinY = (self.view.frame.height - inputContainerHeight) / 2 - 50 // 50 - space from center
        let inputContainerMaxY = inputContainerMinY + inputContainerHeight
        if !socialNetworksContainer.isHidden {
            let restoreContainerHeight = restoreContainer.isHidden ? 0 : restoreContainer.frame.height
            socialNetworksContainerTopConstraint.constant = (loginContainer.frame.minY - inputContainerMaxY + restoreContainerHeight - 100) / 2
        } else {
            if restoreContainer.isHidden {
                self.inputContainerYConstraint.constant = 0
            }
        }
        self.view.layoutIfNeeded()
    }
    
    func configureElements() {
        backgroundImageView.configureWith(bgImageName: configDictionary[CAMKeys.backgroundImage.rawValue] as? String)
        backButton.configureWith(bgImageName: configDictionary[CAMKeys.backButtonImage.rawValue] as? String)
        closeButton.configureWith(bgImageName: configDictionary[CAMKeys.closeButtonImage.rawValue] as? String)
        logoImageView.configureWith(bgImageName: configDictionary[CAMKeys.headerLogo.rawValue] as? String)
        titleLabel.configureWith(text: configDictionary[CAMKeys.signUpScreenTitleText.rawValue] as? String)
        signUpButton.configureWith(text: configDictionary[CAMKeys.signUpButtonText.rawValue] as? String,
                                  bgImageName: configDictionary[CAMKeys.signUpButtonImage.rawValue] as? String)
        alternateLabel.configureWith(text: configDictionary[CAMKeys.separatorText.rawValue] as? String)
        socialNetworksLabel.configureWith(text: configDictionary[CAMKeys.alternativeSignUpPromtText.rawValue] as? String)
        loginButton.configureWith(text: configDictionary[CAMKeys.singUpLoginPromtText.rawValue] as? String)
    }
    
    // MARK: - Keyboard
    
    @IBAction func hideKeyboard() {
        view.endEditing(true)
    }
    
    // MARK: - Actions
    
    @IBAction func backToPreviousScreen(_ sender: UIButton) {
        presenter?.backToPreviousScreen()
    }
    
    @IBAction func close(_ sender: UIButton) {
        presenter?.close()
    }
    
    @IBAction func signUp(_ sender: UIButton) {
        hideKeyboard()
        var result = [(key: String, value: String?)]()
        for obj in authFields {
            if obj.mandatory && (obj.text ?? "").isEmpty {
                let message = configDictionary[CAMKeys.emptyFieldsMessage.rawValue] as? String
                showError(description: message)
                return
            }
            result.append((key: (obj.key ?? ""), value: obj.text))
        }
        presenter?.signUp(data: result)
    }
    
    @IBAction func showLoginScreen(_ sender: Any) {
        presenter?.showLoginScreen()
    }
}

// MARK: - Table Delegate
extension SignUpViewController: UITableViewDelegate, UITableViewDataSource {
    
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
        guard let cell = tableView.dequeueReusableCell(withIdentifier: "AuthCell", for: indexPath) as? AuthTableCell else {
            return UITableViewCell()
        }
        cell.textField.configureInputField(data: authFields[indexPath.row])
        cell.backgroundColor = .clear
        cell.textChanged = { [weak self] text in
            self?.authFields[indexPath.row].text = text
        }
        return cell
    }
}

extension SignUpViewController: SignUpViewProtocol {
    
    // MARK: - SignUpViewProtocol
    
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
        let alert = UIAlertController(title: "Error", message: description, preferredStyle: .alert)
        alert.addAction(UIAlertAction(title: "Ok", style: .default, handler: nil))
        self.present(alert, animated: true, completion: nil)
    }
}
