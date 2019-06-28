//
//  CAMKeys.swift
//  CAM
//
//  Created by Egor Brel on 5/14/19.
//

import Foundation

public enum CAMKeys: String {

    case facebookImage = "facebook_login_image"
    case authFieldImage = "auth_field_image"
    case leftSeparatorImage = "separator_asset_left"
    case rightSeparatorImage = "separator_asset_right"
    case backButtonImage = "back_button"
    case closeButtonImage = "close_button"
    case backgroundImage = "background_image"
    case headerLogoImage = "header_logo"
    case validationSuccessImage = "success_validation_image"
    case validationFailedImage = "failed_validation_image"
    case errorPopoverShadowImage = "field_alert_bubble_shadow"
    case errorPopoverBubbleImage = "field_alert_bubble"
    case loginButtonImage = "login_button_image"
    case signUpButtonImage = "sign_up_button_image"
    case passwordResetButtonImage = "password_reset_button_image"
    case alertButtonImage = "alert_button_image"
    case purchaseButtonImage = "purchase_button_image"
    case purchaseBackgroundImage = "payment_option_component_asset"
    
    case facebookLoginEnabled = "facebook_login_required"
    case authFields = "authentication_input_fields"
    case defaultAuthScreen = "default_login_screen"
    case separatorText = "alternative_authentication_separator_text"
    case alternativeAuthentification = "alternative_authentication_prompt_text"
    
    case emptyFieldsMessage = "required_field_alert_text"
    case wrongEmailMessage = "invalid_email_alert_text"
    
    //Login
    
    case loginScreenTitleText = "login_title_text"
    case loginButtonText = "login_button_text"
    case loginResetPasswordButtonText = "password_reset_link_text"
    case loginSingUpPromtText = "sign_up_prompt_text"
    case loginSingUpActionText = "sign_up_link_text"
    
    //SignUp
    
    case signUpScreenTitleText = "sign_up_title_text"
    case signUpButtonText = "sign_up_button_text"
    case singUpLoginPromtText = "login_prompt_text"
    case singUpLoginActionText = "login_link_text"
    
    //Reset Password
    
    case passwordResetTitleText = "password_reset_title_text"
    case passwordResetInfoText = "password_reset_description_text"
    case passwordResetButtonText = "password_reset_button_text"
    
    //Alert
    
    case passwordAlertTitleText = "password_reset_confirmation_title_text"
    case passwordAlertInfoText = "password_reset_confirmation_description_text"
    case passwordAlertButtonText = "password_reset_confirmation_button_text"
   
    // Payment Options
    
    case paymentScreenTitle = "storefront_screen_title_text"
    case purchaseButtonText = "storefront_button_text"
    case restoreHint = "restore_promt_text"
    case restoreButtonText = "restore_link_text"
    
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
    case bubbleText = "bubble_text"
}
