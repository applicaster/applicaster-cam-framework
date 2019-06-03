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
    case leftSeparatorImage = "separator_asset_left"
    case rightSeparatorImage = "separator_asset_right"
    
    case backButtonImage = "back_button"
    case closeButtonImage = "close_button"
    case headerLogo = "header_logo"
    case backgroundImage = "background_image"
    case separatorText = "separator_text"
    
    case emptyFieldsMessage = "alert_mandatory_field_empty"
    
    //Login
    
    case loginScreenTitleText = "login_screen_title_text"
    case loginButtonText = "sign_in_button_text"
    case loginButtonImage = "login_button_image"
    case loginResetPasswordButtonText = "reset_password_action_text"
    case alternativeLoginPromtText = "alternative_login_action_prompt_text"
    case loginSingUpPromtText = "login_no_account_text"
    case loginSingUpActionText = "sign_up_text"
    
    //SignUp
    
    case signUpScreenTitleText = "sign_up_screen_title_text"
    case signUpButtonText = "sign_up_button_text"
    case signUpButtonImage = "sign_up_button_image"
    case alternativeSignUpPromtText = "alternative_sign_up_action_promt_text"
    case singUpLoginPromtText = "have_account_text"
    case singUpLoginActionText = "sign_up_prompt_action_text"
    
    //Reset Password
    
    case passwordResetTitleText = "reset_password_title_text"
    case passwordResetInfoText = "reset_password_details_text"
    case passwordResetButtonText = "reset_password_action_button_text"
    case passwordResetButtonImage = "password_reset_button_image"
    
    //Alert
    
    case passwordAlertTitleText = "pwd_confirmation_title_text"
    case passwordAlertInfoText = "pwd_confirmation_description_text"
    case passwordAlertButtonText = "pwd_confirmation_button_text"
    case alertButtonImage = "alert_button_image"
   
    // Payment Options
    
    case paymentScreenTitle = "storefront_screen_title_text"
    case purchaseButtonText = "storefront_button_text"
    case purchaseButtonImage = "purchase_button_image"
    case purchaseBackgroundImage = "payment_option_component_asset"
    case restoreHint = "storefront_screen_hint_desc"
    case restoreButtonText = "storefront_screen_hint_action"
    
    // Payment alert
    
    case paymentAlertTitle = "payment_confirmation_title_text"
    case paymentAlertInfo = "payment_confirmation_description_text"
    case paymentAlertButtonText = "payment_confirmation_button_text"
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
