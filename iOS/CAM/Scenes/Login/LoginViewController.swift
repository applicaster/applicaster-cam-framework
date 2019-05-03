//
//  LoginViewController.swift
//  CAMFramework
//
//  Created by Egor Brel on 4/26/19.
//  Copyright © 2019 Egor Brel. All rights reserved.
//

import UIKit

class LoginViewController: UIViewController {    
    
    @IBOutlet weak var backButton: UIButton!
    @IBOutlet weak var closeButton: UIButton!
    @IBOutlet weak var logoImageView: UIImageView!
    
    @IBOutlet weak var titleLabel: UILabel!
    
    @IBOutlet weak var authFieldsTable: UITableView!
    @IBOutlet weak var loginButton: UIButton!
    @IBOutlet weak var resetPasswordButton: UIButton!
    
    @IBOutlet weak var restoreContainer: UIView!
    @IBOutlet weak var restoreCheckBox: UICheckBox!
    @IBOutlet weak var restoreInfoLabel: UILabel!
    
    @IBOutlet weak var socialNetworksContainer: UIView!
    @IBOutlet weak var alternateLabel: UILabel!
    @IBOutlet weak var socialNetworksLabel: UILabel!
    
    @IBOutlet weak var signUpContainer: UIView!
    @IBOutlet weak var signUpLabel: UILabel!
    @IBOutlet var signUpGestureRecognizer: UITapGestureRecognizer!
    
    
    @IBOutlet weak var socialNetworksContainerTopSpaceConstraint: NSLayoutConstraint!
    @IBOutlet weak var inputComponentHeightConstraint: NSLayoutConstraint!
    @IBOutlet weak var authFieldsTableHeightConstraint: NSLayoutConstraint!
    @IBOutlet weak var titleLabelTopSpaceConstraint: NSLayoutConstraint!

    
    weak var configProvider: CAMConfigProtocol?
    var presenter: LoginPresenter?
    
    var centerFreeSpaceValue: CGFloat {
        return signUpContainer.frame.minY - logoImageView.frame.maxY
    }
    
    var additionalComponentTopHeight: CGFloat {
        let result = titleLabel.isHidden ? 0 : titleLabel.frame.height + 40// 20 - min spacing
        return result == 0 ? 50 : result
    }
    
    var additionalComponentBottomHeight: CGFloat {
        var result = restoreContainer.isHidden ? 0 : restoreContainer.frame.height
        result += socialNetworksContainer.isHidden ? 0 : socialNetworksContainer.frame.height + 20 // 20 - min spacing
        return result == 0 ? 50 : result
    }
    
    var inputComponentHeight: CGFloat {
        return centerFreeSpaceValue - additionalComponentTopHeight - additionalComponentBottomHeight
    }
    
    var authFieldsTableHeight: CGFloat {
        return inputComponentHeight - loginButton.frame.height - resetPasswordButton.frame.height
    }
    
    //MARK: - Flow & UI Setup
    
    override func loadView() {
        super.loadView()
        self.navigationController?.isNavigationBarHidden = true
        signUpLabel.isUserInteractionEnabled = true
        resetPasswordButton.isUserInteractionEnabled = true
    }
    
    override func viewDidLoad() {
        super.viewDidLoad()
        self.navigationController?.isNavigationBarHidden = true
    }

    override func viewDidLayoutSubviews() {
        super.viewDidLayoutSubviews()
        setupConstraints()
    }
    
    func setupUI() {
        signUpLabel.isUserInteractionEnabled = true
    }
    
    func setupConstraints() {
        inputComponentHeightConstraint.constant = inputComponentHeight
        authFieldsTableHeightConstraint.constant = authFieldsTableHeight
        let inputComponentMinY = (self.view.frame.height - inputComponentHeight) / 2 - 70
        let inputComponentMaxY = inputComponentMinY + inputComponentHeight
        titleLabelTopSpaceConstraint.constant = (inputComponentMinY - logoImageView.frame.maxY - titleLabel.frame.height) / 2
        if !socialNetworksContainer.isHidden {
            let restoreContainerHeight = restoreContainer.isHidden ? 0 : restoreContainer.frame.height
            socialNetworksContainerTopSpaceConstraint.constant = (signUpContainer.frame.minY - inputComponentMaxY + restoreContainerHeight - 100) / 2
        }
        self.view.layoutIfNeeded()
    }
    
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
        
    }
}

extension LoginViewController: UITableViewDelegate, UITableViewDataSource {
    
    func tableView(_ tableView: UITableView, numberOfRowsInSection section: Int) -> Int {
        return 1
    }
    
    func tableView(_ tableView: UITableView, cellForRowAt indexPath: IndexPath) -> UITableViewCell {
        return UITableViewCell()
    }
}
