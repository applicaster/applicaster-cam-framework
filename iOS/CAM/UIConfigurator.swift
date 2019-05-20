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
    func configureWith(text: String? = nil, color: UIColor? = .black, fontName: String? = nil, fontSize: CGFloat = 12, placeholder: String? = nil, cornerRadius: CGFloat = 0, inputType: AuthFieldInputType = .text) {
        self.text = text
        self.textColor = color
        if let fontName = fontName, let font = UIFont(name: fontName, size: fontSize) {
            self.font = font
        }
        self.placeholder = placeholder
        self.layer.cornerRadius = cornerRadius
        self.clipsToBounds = true
        switch inputType {
        case .text, .unknown:
            self.keyboardType = .default
        case .number:
            self.keyboardType = .numberPad
        case .password:
            self.keyboardType = .default
            self.isSecureTextEntry = true
        }
        
    }
}

class UIConfigurator {
    
    static func configureAuthField(view: UITextField, data: AuthField, dict: Dictionary<String, Any>?) {
        view.configureWith(text: data.text, placeholder: data.hint, cornerRadius: 26.0, inputType: data.type)
    }
    
    static func configureView(type: UIElement, view: UIView, dict: Dictionary<String, Any>?) {
        switch type {
        case .backButton:
            if let backButton = view as? UIButton {
                backButton.configureWith(bgImageName: dict?[CAMKeys.back_button.rawValue] as? String)
            }
        case .closeButton:
            if let closeButton = view as? UIButton {
                closeButton.configureWith(bgImageName: dict?[CAMKeys.close_button.rawValue] as? String)
            }
        case .headerImageView:
            if let headerImageView = view as? UIImageView {
                headerImageView.configureWith(bgImageName: dict?[CAMKeys.header_logo.rawValue] as? String)
            }
        case .backgroungImageView:
            if let backgroundImageView = view as? UIImageView {
                backgroundImageView.configureWith(bgImageName: dict?[CAMKeys.background_image.rawValue] as? String)
            }
        case .separatorLabel:
            if let separatorLabel = view as? UILabel {
                separatorLabel.configureWith(text: dict?[CAMKeys.separator_text.rawValue] as? String)
            }
        case .networksAuthLabel:
            if let networksAuthLabel = view as? UILabel {
                networksAuthLabel.configureWith(text: dict?[CAMKeys.networks_auth_action_text.rawValue] as? String)
            }
        case .bottomBannerView:
            view.configureWith(bgColor: dict?[CAMKeys.bottom_banner_bg_color.rawValue] as? UIColor)
        case .loginTitleLabel:
            if let loginTitleLabel = view as? UILabel {
                loginTitleLabel.configureWith(text: dict?[CAMKeys.login_screen_title_text.rawValue] as? String)
            }
        case .loginResetPasswordButton:
            if let restorePasswordLabel = view as? UIButton {
                restorePasswordLabel.configureWith(text: dict?[CAMKeys.reset_password_text.rawValue] as? String, state: .normal)
            }
        case .loginAlternativeActionButton:
            if let loginAlternativeActionButton = view as? UIButton {
                loginAlternativeActionButton.configureWith(text: dict?[CAMKeys.alternative_login_promt_text.rawValue] as? String)
            }
        case .loginButton:
            if let loginButton = view as? UIButton {
                loginButton.configureWith(text: dict?[CAMKeys.login_button_text.rawValue] as? String,
                                          cornerRadius: 24,
                                          bgImageName: dict?[CAMKeys.login_button_image.rawValue] as? String,
                                          state: .normal)
            }
        case .signUpTitleLabel:
            if let signUpTitleLabel = view as? UILabel {
                signUpTitleLabel.configureWith(text: dict?[CAMKeys.signup_screen_title_text.rawValue] as? String)
            }
        case .signUpAlternativeActionButton:
            if let signUpAlternativeActionLabel = view as? UIButton {
                signUpAlternativeActionLabel.configureWith(text: dict?[CAMKeys.alternative_signup_promt_text.rawValue] as? String)
            }
        case .signUpButton:
            if let signUpButton = view as? UIButton {
                signUpButton.configureWith(text: dict?[CAMKeys.signup_button_text.rawValue] as? String,
                                           cornerRadius: 24,
                                           bgImageName: dict?[CAMKeys.signup_button_image.rawValue] as? String,
                                           state: .normal)
            }
        case .resetPasswordTitleLabel:
            if let resetPasswordTitleLabel = view as? UILabel {
                resetPasswordTitleLabel.configureWith(text: dict?[CAMKeys.password_reset_title_text.rawValue] as? String)
            }
        case .resetPasswordInfoLabel:
            if let resetPasswordInfoLabel = view as? UILabel {
                resetPasswordInfoLabel.configureWith(text: dict?[CAMKeys.password_reset_info_text.rawValue] as? String)
            }
        case .resetPasswordTextField:
            if let resetPasswordTextField = view as? UITextField {
                resetPasswordTextField.configureWith(placeholder: "Email")
            }
        case .resetPasswordButton:
            if let resetPasswordButton = view as? UIButton {
                resetPasswordButton.configureWith(text: dict?[CAMKeys.password_reset_button_text.rawValue] as? String,
                                           bgImageName: dict?[CAMKeys.password_alert_button_image.rawValue] as? String,
                                           state: .normal)
            }
        case .passwordAlert:
            if let alertView = view as? ConfirmationPopover {
                alertView.titleLabel.configureWith(text: dict?["password_alert_title_text"] as? String)
                alertView.DescriptionLabel.configureWith(text: dict?["password_alert_info_text"] as? String)
                alertView.actionButton.configureWith(text: dict?["password_alert_button_text"] as? String,
                                          bgImageName: dict?["password_alert_button_image"] as? String,
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
    case signUpAlternativeActionButton
    case signUpButton
    
    case resetPasswordTitleLabel
    case resetPasswordInfoLabel
    case resetPasswordTextField
    case resetPasswordButton
    
    case passwordAlert
}
