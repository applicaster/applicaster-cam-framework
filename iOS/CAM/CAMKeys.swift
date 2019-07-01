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
    case defaultAuthScreen = "default_login_screen"
    case authFields = "authentication_input_fields"
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
    
    case alertButtonText = "confirmation_button_text"
    case passwordAlertTitleText = "password_reset_confirmation_title_text"
    case passwordAlertInfoText = "password_reset_confirmation_description_text"
   
    // Payment alert
    
    case paymentAlertTitle = "payment_confirmation_title_text"
    case paymentAlertInfo = "payment_confirmation_description_text"
    
    // Payment Options
    
    case paymentScreenTitle = "storefront_screen_title_text"
    case purchaseButtonText = "payment_option_button_text"
    case restoreHint = "restore_prompt_text"
    case restoreButtonText = "restore_link_text"
    case legalDetailsText = "legal_details_text"
}

public enum CAMStyles: String {
    
    case inputFieldFont = "input_field_label"
    
    case actionButtonFont = "action_button"
    
    case promptFont = "prompt"
    
    case linkFont = "link"
    
    case screenTitleFont = "screen_title"
    
    case screenDescriptionFont = "screen_description"
    
    case separatorFont = "alternative_authentication_separator"
   
    case alternativeAuthenticationFont = "alternative_authentication_prompt"
    
    case resetPasswordFont = "reset_password"
    
    case paymentOptionTitleFont = "payment_option_title"
    
    case paymentOptionDescriptionFont = "payment_option_description"
    
    case legalDetailsFont = "legal_details"
    
    case legalDetailsBackgroundColor = "legal_details_background"
    
    case confirmationTitleFont = "confirmation_title"
    
    case confirmationDescriptionFont = "confirmation_description"
    
    case confirmationButtonFont = "confirmation_button"
}
