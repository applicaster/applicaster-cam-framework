//
//  CAMKeys.swift
//  CAM
//
//  Created by Egor Brel on 5/14/19.
//

import Foundation

enum CAMKeys: String {

    case passwordResetEnabled = "pwd_reset_required"
    case facebookLoginEnabled = "facebook_login_required"
    case authFields = "auth_fields"
    case defaultAuthScreen = "default_auth_screen"
    case authFieldImage = "auth_field_image"
    
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
    case loginSingUpActionText = "login_prompt_action_text"
    
    //SignUp
    
    case signUpScreenTitleText = "signup_screen_title_text"
    case signUpButtonText = "signup_button_text"
    case signUpButtonImage = "signup_button_image"
    case alternativeSignUpPromtText = "alternative_signup_action_promt_text"
    case singUpLoginPromtText = "signup_promt_text"
    case singUpLoginActionText = "signup_prompt_action_text"
    
    //Reset Password
    
    case passwordResetTitleText = "password_reset_title_text"
    case passwordResetInfoText = "password_reset_description_text"
    case passwordResetButtonText = "password_reset_button_text"
    case passwordResetButtonImage = "password_reset_button_image"
    case passwordInputFieldPlaceholder = "password_input_field_placeholder"
    
    //Reset Password alert
    
    case passwordAlertTitleText = "password_alert_title_text"
    case passwordAlertInfoText = "password_alert_description_text"
    case passwordAlertButtonText = "password_alert_button_text"
    case passwordAlertButtonImage = "password_alert_button_image"
}
