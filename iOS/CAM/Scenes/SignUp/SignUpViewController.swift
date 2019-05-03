//
//  SignUpViewController.swift
//  CAM
//
//  Created by Egor Brel on 4/30/19.
//

import UIKit

class SignUpViewController: UIViewController {

    @IBOutlet weak var backgroundImageView: UIImageView!
    
    @IBOutlet weak var backButton: UIButton!
    @IBOutlet weak var closeButton: UIButton!
    
    @IBOutlet weak var logoImageView: UIImageView!
    @IBOutlet weak var titleLabel: UILabel!
    
    @IBOutlet weak var authFieldsTable: UITableView!
    @IBOutlet weak var signUpButton: UIButton!
    
    @IBOutlet weak var restoreContainer: UIView!
    @IBOutlet weak var restoreCheckBox: UICheckBox!
    @IBOutlet weak var restoreInfoLabel: UILabel!
    
    @IBOutlet weak var socialNetworksContainer: UIView!
    @IBOutlet weak var alternateLabel: UILabel!
    @IBOutlet weak var socialNetworksLabel: UILabel!
    
    @IBOutlet weak var loginContainer: UIView!
    @IBOutlet weak var loginLabel: UILabel!
    
    @IBOutlet weak var titleLabelTopSpaceConstraint: NSLayoutConstraint!
    @IBOutlet weak var socialNetworksContainerTopSpaceConstraint: NSLayoutConstraint!
    @IBOutlet weak var inputComponentHeightConstraint: NSLayoutConstraint!
    
    weak var configProvider: CAMConfigProtocol?
    var presenter: SignUpPresenter?
    
    var centerFreeSpaceValue: CGFloat {
        return loginContainer.frame.minY - logoImageView.frame.maxY
    }
    
    var additionalComponentTopHeight: CGFloat {
        let result = titleLabel.isHidden ? 0 : titleLabel.frame.height + 40 // 20 - min spacing
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
    
    override func loadView() {
        super.loadView()
        loginLabel.isUserInteractionEnabled = true
        self.navigationController?.isNavigationBarHidden = true
    }
    
    override func viewDidLoad() {
        super.viewDidLoad()
        self.navigationController?.isNavigationBarHidden = true
        // Do any additional setup after loading the view.
    }

    override func viewDidLayoutSubviews() {
        super.viewDidLayoutSubviews()
        setupConstraints()
    }
    
    func setupUI() {
        
    }
    
    func setupConstraints() {
        inputComponentHeightConstraint.constant = inputComponentHeight
        let inputComponentMinY = (self.view.frame.height - inputComponentHeight) / 2 - 70
        let inputComponentMaxY = inputComponentMinY + inputComponentHeight
        titleLabelTopSpaceConstraint.constant = (inputComponentMinY - logoImageView.frame.maxY - titleLabel.frame.height) / 2
        if !socialNetworksContainer.isHidden {
            let restoreContainerHeight = restoreContainer.isHidden ? 0 : restoreContainer.frame.height
            socialNetworksContainerTopSpaceConstraint.constant = (loginContainer.frame.minY - inputComponentMaxY + restoreContainerHeight - 100) / 2
        }
        self.view.layoutIfNeeded()
    }
    
    @IBAction func backToPreviousScreen(_ sender: UIButton) {
        presenter?.backToPreviousScreen()
    }
    
    @IBAction func close(_ sender: UIButton) {
        presenter?.close()
    }
    
    @IBAction func signUp(_ sender: UIButton) {
        
    }
    
    @IBAction func showLoginScreen(_ sender: Any) {
        presenter?.showLoginScreen()
    }
}
