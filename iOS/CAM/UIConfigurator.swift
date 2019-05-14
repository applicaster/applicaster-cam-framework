//
//  CustomizableFields.swift
//  CAM
//
//  Created by Egor Brel on 5/10/19.
//

import UIKit

extension UIButton {
    func configureWith(text: String? = nil, color: UIColor? = nil, fontName: String? = nil, fontSize: CGFloat = 12,
                          cornerRadius: CGFloat = 0, bgImageName: String? = nil, state: UIControl.State = .normal) {
        self.layer.cornerRadius = cornerRadius
        self.setTitle(text, for: state)
        self.setTitleColor(color, for: state)
        if let imageName = bgImageName, let image = UIImage(named: imageName) {
            self.setImage(image, for: state)
        }
        if let fontName = fontName, let font = UIFont(name: fontName, size: fontSize) {
            self.titleLabel?.font = font
        }
    }
}

extension UIView {
    func configureWith(bgColor: UIColor? = nil) {
        self.backgroundColor = bgColor
    }
}

extension UIImageView {
    func configureWith(bgImageName : String? = nil) {
        if let imageName = bgImageName, let image = UIImage(named: imageName) {
            self.image = image
        }
    }
}

extension UILabel {
    func configureWith(text: String? = nil, color: UIColor? = nil, fontName: String? = nil, fontSize: CGFloat = 12) {
        self.text = text
        self.textColor = color
        if let fontName = fontName, let font = UIFont(name: fontName, size: fontSize) {
            self.font = font
        }
    }
}

extension UITextField {
    func configureWith(text: String? = nil, color: UIColor? = .black, fontName: String? = nil, fontSize: CGFloat = 12, placeholder: String? = nil, cornerRadius: CGFloat = 0) {
        self.text = text
        self.textColor = color
        if let fontName = fontName, let font = UIFont(name: fontName, size: fontSize) {
            self.font = font
        }
        self.placeholder = placeholder
        self.layer.cornerRadius = cornerRadius
        self.clipsToBounds = true
    }
}

class UIConfigurator {
    
    static func configureAuthField(view: UITextField, data: AuthField, configProvider: CAMDelegate?) {
        view.configureWith(text: data.text, placeholder: data.hint, cornerRadius: 26.0)
    }
    
    static func configureView(type: UIElement, view: UIView, configProvider: CAMDelegate?) {
        let dict = configProvider?.getPluginConfig()
        switch type {
        case .backButton:
            if let backButton = view as? UIButton {
                backButton.configureWith(bgImageName: dict?["back_button"] as? String)
            }
        case .closeButton:
            if let closeButton = view as? UIButton {
                closeButton.configureWith(bgImageName: dict?["close_button"] as? String)
            }
        case .headerImageView:
            if let headerImageView = view as? UIImageView {
                headerImageView.configureWith(bgImageName: dict?["header_logo"] as? String)
            }
        case .backgroungImageView:
            if let backgroundImageView = view as? UIImageView {
                backgroundImageView.configureWith(bgImageName: dict?["background_image"] as? String)
            }
        case .separatorLabel:
            if let separatorLabel = view as? UILabel {
                separatorLabel.configureWith(text: dict?["separator_text"] as? String)
            }
        case .networksAuthLabel:
            if let networksAuthLabel = view as? UILabel {
                networksAuthLabel.configureWith(text: dict?["networks_auth_action_text"] as? String)
            }
        case .bottomBannerView:
            view.configureWith(bgColor: dict?["bottom_banner_bg_color"] as? UIColor)
        case .loginTitleLabel:
            if let loginTitleLabel = view as? UILabel {
                loginTitleLabel.configureWith(text: dict?["login_screen_title_text"] as? String)
            }
        case .loginResetPasswordButton:
            if let restorePasswordLabel = view as? UIButton {
                restorePasswordLabel.configureWith(text: dict?["reset_password_text"] as? String, state: .normal)
            }
        case .loginAlternativeActionButton:
            if let loginAlternativeActionButton = view as? UIButton {
                loginAlternativeActionButton.configureWith(text: dict?["alternative_login_promt_text"] as? String)
            }
        case .loginButton:
            if let loginButton = view as? UIButton {
                loginButton.configureWith(text: dict?["login_button_text"] as? String,
                                          bgImageName: dict?["login_button_image"] as? String,
                                          state: .normal)
            }
        case .signUpTitleLabel:
            if let signUpTitleLabel = view as? UILabel {
                signUpTitleLabel.configureWith(text: dict?["signup_screen_title_text"] as? String)
            }
        case .signUpAlternativeActionLabel:
            if let signUpAlternativeActionLabel = view as? UILabel {
                signUpAlternativeActionLabel.configureWith(text: dict?["alternative_signup_promt_text"] as? String)
            }
        case .signUpButton:
            if let signUpButton = view as? UIButton {
                signUpButton.configureWith(text: dict?["signup_button_text"] as? String,
                                          bgImageName: dict?["signup_button_image"] as? String,
                                          state: .normal)
            }
        case .resetPasswordTitleLabel:
            if let resetPasswordTitleLabel = view as? UILabel {
                resetPasswordTitleLabel.configureWith(text: dict?["password_reset_title_text"] as? String)
            }
        case .resetPasswordInfoLabel:
            if let resetPasswordInfoLabel = view as? UILabel {
                resetPasswordInfoLabel.configureWith(text: dict?["password_reset_info_text"] as? String)
            }
        case .resetPasswordButton:
            if let resetPasswordButton = view as? UIButton {
                resetPasswordButton.configureWith(text: dict?["password_reset_button_text"] as? String,
                                           bgImageName: dict?["password_reset_button_image"] as? String,
                                           state: .normal)
            }
        case .alertTitleLabel:
            if let alertTitleLabel = view as? UILabel {
                alertTitleLabel.configureWith(text: dict?["alert_title_text"] as? String)
            }
        case .alertInfoLabel:
            if let alertInfoLabel = view as? UILabel {
                alertInfoLabel.configureWith(text: dict?["alert_info_text"] as? String)
            }
        case .alertButton:
            if let alertButton = view as? UIButton {
                alertButton.configureWith(text: dict?["alert_button_text"] as? String,
                                                  bgImageName: dict?["alert_button_image"] as? String,
                                                  state: .normal)
            }
        }
    }
}

enum UIElement {
    case backButton
    case closeButton
    case headerImageView
    case backgroungImageView
    
    case separatorLabel
    case networksAuthLabel
    case bottomBannerView
    
    case loginTitleLabel
    case loginResetPasswordButton
    case loginAlternativeActionButton
    case loginButton
    
    case signUpTitleLabel
    case signUpAlternativeActionLabel
    case signUpButton
    
    case resetPasswordTitleLabel
    case resetPasswordInfoLabel
    case resetPasswordButton
    
    
    case alertTitleLabel
    case alertInfoLabel
    case alertButton
}
