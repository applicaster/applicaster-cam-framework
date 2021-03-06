//
//  CAMKeys.swift
//  CAM
//
//  Created by Egor Brel on 5/14/19.
//

import Foundation

public enum CAMKeys: String {
    
    enum Images: String {
        case actionButton = "cam_action_button_asset"
        case cancelButton = "cam_cancel_button_asset"
        case alertButton = "cam_alert_button_asset"
        case alertBackground = "cam_alert_component"
        case authField = "cam_input_field_asset"
        case backButton = "cam_back_button"
        case background = "cam_background_image"
        case closeButton = "cam_close_button"
        case errorPopoverShadow = "cam_field_alert_bubble_shadow"
        case errorPopoverBubble = "cam_field_alert_bubble"
        case facebook = "cam_icon_1"
        case headerLogo = "cam_header_logo"
        case leftSeparator = "cam_separator_asset_left"
        case rightSeparator = "cam_separator_asset_right"
        case purchaseButton = "cam_payment_option_button_asset"
        case purchaseBackground = "cam_payment_option_component_asset"
        case validationFailed = "cam_input_alert_indicator"
    }
   
    case facebookLoginEnabled = "facebook_login_required"
    case defaultAuthScreen = "default_authentication_screen"
    case authFields = "authentication_input_fields"
    case isAlternativeAuthenticationEnabled = "offer_alternative_authentication"
    case separatorText = "alternative_authentication_separator_text"
    case alternativeAuthenticationPromtText = "alternative_authentication_prompt_text"
    case signUpActivationCodeEnabled = "use_signup_activation_code_method"
    case resetPasswordCodeActivationEnabled = "use_pw_activation_code_method"
    
    case defaultAlertText = "default_alert_text"
    case emptyFieldsMessage = "required_field_alert_text"
    case wrongEmailMessage = "invalid_email_alert_text"
    
    //Login
    
    case loginScreenTitleText = "login_title_text"
    case loginButtonText = "login_button_text"
    case loginResetPasswordButtonText = "password_reset_link_text"
    case loginSingUpPromtText = "sign_up_prompt_text"
    case loginSingUpActionText = "sign_up_link_text"
    
    case loginScreenFirstCustomLink = "login_screen_custom_link_1"
    case loginScreenFirstCustomLinkText = "login_screen_custom_link_1_text"
    case loginScreenSecondCustomLink = "login_screen_custom_link_2"
    case loginScreenSecondCustomLinkText = "login_screen_custom_link_2_text"
    
    //Logout
    
    case logoutTitleText = "logout_title_text"
    case logoutInfoText = "logout_description_text"
    case logoutErrorText = "logout_error_alert_text"
    
    //SignUp
    
    case signUpScreenTitleText = "sign_up_title_text"
    case signUpButtonText = "sign_up_button_text"
    case singUpLoginPromtText = "login_prompt_text"
    case singUpLoginActionText = "login_link_text"
    
    case signUpScreenFirstCustomLink = "sign_up_screen_custom_link_1"
    case signUpScreenFirstCustomLinkText = "sign_up_screen_custom_link_1_text"
    case signUpScreenSecondCustomLink = "sign_up_screen_custom_link_2"
    case signUpScreenSecondCustomLinkText = "sign_up_screen_custom_link_2_text"
    
    //Reset Password
    
    case passwordResetTitleText = "password_reset_title_text"
    case passwordResetInfoText = "password_reset_description_text"
    case passwordResetButtonText = "password_reset_button_text"
    case sendPasswordCodeButtonText = "send_pw_activation_code_button_text"
    
    //Update Password
    
    case passwordUpdateTitleText = "password_update_title_text"
    case passwordUpdateInfoText = "password_update_description_text"
    case passwordUpdateButtonText = "password_update_button_text"
    
    //Account Activation
    
    case accountActivationScreenTitleText = "account_activation_screen_title_text"
    case accountActivationScreenDescriptionText = "account_activation_description_text"
    case accountActivationButtonText = "activate_account_button_text"
    case resendAccountActivationCodeButtonText = "resend_code_text"
    
    //Alert
    
    case alertButtonText = "confirmation_button_text"
    case passwordAlertTitleText = "password_reset_confirmation_title_text"
    case passwordAlertInfoText = "password_reset_confirmation_description_text"
    case cancelButtonText = "cancel_button_text"
    
    // Payment alert
    
    case paymentAlertTitle = "payment_confirmation_title_text"
    case paymentAlertInfo = "payment_confirmation_description_text"
    
    // Payment Options
    
    case paymentScreenTitle = "storefront_screen_title_text"
    case purchaseButtonText = "payment_option_button_text"
    case restoreHint = "restore_prompt_text"
    case restoreButtonText = "restore_link_text"
    case legalDetailsText = "legal_details_text"
    
    case storefrontScreenFirstCustomLink = "storefront_screen_custom_link_1"
    case storefrontScreenFirstCustomLinkText = "storefront_screen_custom_link_1_text"
    case storefrontScreenSecondCustomLink = "storefront_screen_custom_link_2"
    case storefrontScreenSecondCustomLinkText = "storefront_screen_custom_link_2_text"
    
    // Restore
    
    case restoreAlertTitle = "restore_purchase_confirmation_title_text"
    case restoreAlertDescription = "restore_purchase_confirmation_description_text"
    case restoreNonMatchingAlertText = "non_matching_restored_purchases_alert_text"
    case restoreNoPurchaseAlertText = "no_purchases_to_restore_alert_text"
    
    case paymentRequirement = "require_payment"
}

enum AuthRequirement: String {
    case never = "never_require"
    case always = "always_require"
    case purchasableItems = "require_on_all_purchasable_items"
    case dataSourceBased = "require_when_specified_on_the_data_source"
    
    static var key: String {
        return "authentication_requirement"
    }
}

public enum CAMStyles: String {
    
    case inputFieldFont = "input_field_label"
    
    case actionButtonFont = "action_button"
    
    case promptFont = "prompt"
    
    case linkFont = "link"
    
    case customlinkFont = "custom_link"
    
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
    
    case cancelButtonFont = "cancel_button"
    
    case resendCodeButtonFont = "resend_code"
}
