//
//  CAMKeys.swift
//  CAM
//
//  Created by Egor Brel on 5/14/19.
//

import Foundation

public enum CAMKeys: String {

    case passwordResetEnabled = "pwd_reset_required"
    case facebookLoginEnabled = "facebook_login_required"
    case facebookImage = "facebook_login_image"
    case authFields = "auth_fields"
    case authFieldImage = "auth_field_image"
    case defaultAuthScreen = "default_auth_screen"
    
    case backButtonImage = "back_button"
    case closeButtonImage = "close_button"
    case headerLogo = "header_logo"
    case backgroundImage = "background_image"
    case separatorText = "separator_text"
    
    case emptyFieldsMessage = "madatory_field_empty_error"
    
    //Login
    
    case loginScreenTitleText = "login_screen_title_text"
    case loginButtonText = "login_button_text"
    case loginButtonImage = "login_button_image"
    case loginResetPasswordButtonText = "reset_password_text"
    case alternativeLoginPromtText = "alternative_login_action_prompt_text"
    case loginSingUpPromtText = "login_promt_text"
    case loginSingUpActionText = "login_promt_action_text"
    
    //SignUp
    
    case signUpScreenTitleText = "sign_up_screen_title_text"
    case signUpButtonText = "sign_up_button_text"
    case signUpButtonImage = "sign_up_button_image"
    case alternativeSignUpPromtText = "alternative_sign_up_action_promt_text"
    case singUpLoginPromtText = "sign_up_promt_text"
    case singUpLoginActionText = "sign_up_promt_action_text"
    
    //Reset Password
    
    case passwordResetTitleText = "password_reset_title_text"
    case passwordResetInfoText = "password_reset_description_text"
    case passwordResetButtonText = "password_reset_button_text"
    case passwordResetButtonImage = "password_reset_button_image"
    case passwordInputFieldPlaceholder = "password_input_field_placeholder"
    
    //Alert
    
    case passwordAlertTitleText = "password_alert_title_text"
    case passwordAlertInfoText = "password_alert_description_text"
    case alertButtonText = "alert_button_text"
    case alertButtonImage = "alert_button_image"
    
    // Payment Options
    
    case purchaseButtonText = "payment_option_button_text"
    case purchaseButtonImage = "purchase_button_image"
    
    //
}

public enum CAMStyles: String {
    case screenTitle = "screen_title_text"
    case screenDescription = "screen_description_text"
    case inputField = "input_label_text"
    case actionButton = "action_button_text"
    case resetPassword = "restore_password_text"
    case promtText = "promt_text"
    case promtAction = "promt_action_text"
    case separator = "separator_text"
    case alternativeLoginText = "alternative_login_promt_text"
    case alternateActionBannerColor = "alternate_action_banner_bg_color"
    case alertTitle = "alert_title_text"
    case alertDescription = "alert_description_text"
}
