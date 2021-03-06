package com.applicaster.cam.config.ui

enum class UIKey(
    val text: String? = null,
    val textLink: String? = null,
    val textStyle: StyleKey? = null,
    val textLinkStyle: StyleKey? = null,
    val image: String? = null
) {
    // @formatter:off
    TOOLBAR_BACK_BUTTON(image = UI_KEY_TOOLBAR_BACK_IMAGE),
    TOOLBAR_CLOSE_BUTTON(image = UI_KEY_TOOLBAR_CLOSE_IMAGE),
    TOOLBAR_HEADER_LOGO_IMAGE(image = UI_KEY_TOOLBAR_LOGO_IMAGE),
    BACKGROUND_IMAGE(image = UI_KEY_BACKGROUND_IMAGE),

    LOGIN_TITLE(text = UI_KEY_LOGIN_TITLE_TEXT, textStyle = StyleKey.SCREEN_TITLE),
    LOGIN_RESET_PWD_TEXT(text = UI_KEY_LOGIN_RESET_PWD_TEXT, textStyle = StyleKey.RESET_PASSWORD),
    LOGIN_ALT_AUTH_TEXT(text = UI_KEY_THIRD_PARTY_AUTH_TEXT, textStyle = StyleKey.ALT_AUTH_PROMPT),
    LOGIN_BUTTON(text = UI_KEY_LOGIN_BUTTON_TEXT, image = UI_KEY_LOGIN_BUTTON_IMAGE, textStyle = StyleKey.ACTION_BUTTON),
    LOGIN_PROMPT_TEXT(text = UI_KEY_LOGIN_PROMPT_TEXT, textLink = UI_KEY_LOGIN_PROMPT_ACTION_TEXT, textStyle = StyleKey.PROMPT, textLinkStyle = StyleKey.LINK),
    LOGIN_LINK_1_TEXT(text = UI_KEY_LOGIN_LINK_1_DESC_TEXT, textLink = UI_KEY_LOGIN_LINK_1_URL_TEXT, textStyle = StyleKey.CUSTOM_LINK),
    LOGIN_LINK_2_TEXT(text = UI_KEY_LOGIN_LINK_2_DESC_TEXT, textLink = UI_KEY_LOGIN_LINK_2_URL_TEXT, textStyle = StyleKey.CUSTOM_LINK),
    SIGN_UP_TITLE(text = UI_KEY_SIGN_UP_TITLE_TEXT, textStyle = StyleKey.SCREEN_TITLE),
    SIGN_UP_ALT_AUTH_TEXT(text = UI_KEY_THIRD_PARTY_AUTH_TEXT, textStyle = StyleKey.ALT_AUTH_PROMPT),
    SIGN_UP_BUTTON(text = UI_KEY_SIGN_UP_BUTTON_TEXT, image = UI_KEY_SIGN_UP_BUTTON_IMAGE, textStyle = StyleKey.ACTION_BUTTON),
    SIGN_UP_PROMPT_TEXT(text = UI_KEY_SIGN_UP_PROMPT_TEXT, textLink = UI_KEY_SIGN_UP_PROMPT_ACTION_TEXT, textStyle = StyleKey.PROMPT, textLinkStyle = StyleKey.LINK),
    SIGN_UP_LINK_1_TEXT(text = UI_KEY_SIGN_UP_LINK_1_DESC_TEXT, textLink = UI_KEY_SIGN_UP_LINK_1_URL_TEXT, textStyle = StyleKey.CUSTOM_LINK),
    SIGN_UP_LINK_2_TEXT(text = UI_KEY_SIGN_UP_LINK_2_DESC_TEXT, textLink = UI_KEY_SIGN_UP_LINK_2_URL_TEXT, textStyle = StyleKey.CUSTOM_LINK),
    AUTH_SEPARATOR_TEXT(text = UI_KEY_THIRD_PARTY_SEPARATOR_TEXT, textStyle = StyleKey.ALT_AUTH_SEPARATOR),
    AUTH_LEFT_DIVIDER_IMAGE(image = UI_KEY_THIRD_PARTY_DIVIDER_LEFT_IMAGE),
    AUTH_RIGHT_DIVIDER_IMAGE(image = UI_KEY_THIRD_PARTY_DIVIDER_RIGHT_IMAGE),
    AUTH_INPUT_FIELD(image = UI_KEY_INPUT_FIELD_IMAGE, textStyle = StyleKey.INPUT_FIELD_LABEL),
    AUTH_VALIDATION_POPUP(image = UI_KEY_VALIDATION_PARENT_IMAGE),
    AUTH_VALIDATION_TEXT(image = UI_KEY_VALIDATION_BUBBLE_IMAGE, textStyle = StyleKey.INPUT_FIELD_LABEL),
    AUTH_FACEBOOK_IMAGE(image = UI_KEY_FACEBOOK_IMAGE),

    ACCOUNT_ACTIVATION_TITLE_TEXT(text = UI_KEY_ACTIVATION_TITLE_TEXT, textStyle = StyleKey.SCREEN_TITLE),
    ACCOUNT_ACTIVATION_DESC_TEXT(text = UI_KEY_ACTIVATION_DESC_TEXT, textStyle = StyleKey.SCREEN_DESC),
    ACCOUNT_ACTIVATION_ACTION_BUTTON(text = UI_KEY_ACTIVATION_BUTTON_TEXT, textStyle = StyleKey.ACTION_BUTTON, image = UI_KEY_ACTIVATION_BUTTON_IMAGE),
    ACCOUNT_ACTIVATION_RESEND_CODE_BUTTON(text = UI_KEY_ACTIVATION_RESEND_TEXT, textStyle = StyleKey.RESEND_CODE),

    PASSWORD_RESET_TITLE_TEXT(text = UI_KEY_PWD_RESET_TITLE_TEXT, textStyle = StyleKey.SCREEN_TITLE),
    PASSWORD_RESET_DESC_TEXT(text = UI_KEY_PWD_RESET_DESC_TEXT, textStyle = StyleKey.SCREEN_DESC),
    PASSWORD_RESET_ACTION_BUTTON(text = UI_KEY_PWD_RESET_BUTTON_TEXT, textStyle = StyleKey.ACTION_BUTTON, image = UI_KEY_PWD_RESET_BUTTON_IMAGE),
    BILLING_ITEM_SUBS_BUTTON(text = UI_KEY_BILLING_ITEM_SUBS_BUTTON_TEXT, textStyle = StyleKey.ACTION_BUTTON, image = UI_KEY_BILLING_ITEM_SUBS_BUTTON_IMAGE),

    PWD_ACTIVATION_CODE_BUTTON_TEXT(text = UI_KEY_PWD_ACTIVATION_CODE_BUTTON_TEXT, textStyle = StyleKey.ACTION_BUTTON, image = UI_KEY_PWD_RESET_BUTTON_IMAGE),
    PASSWORD_UPDATE_TITLE_TEXT(text = UI_KEY_PWD_UPDATE_TITLE_TEXT, textStyle = StyleKey.SCREEN_TITLE),
    PASSWORD_UPDATE_DESC_TEXT(text = UI_KEY_PWD_UPDATE_DESC_TEXT, textStyle = StyleKey.SCREEN_DESC),
    PASSWORD_UPDATE_ACTION_BUTTON(text = UI_KEY_PWD_UPDATE_BUTTON_TEXT, textStyle = StyleKey.ACTION_BUTTON, image = UI_KEY_PWD_RESET_BUTTON_IMAGE),

    BILLING_ITEM_PARENT(image = UI_KEY_BILLING_ITEM_IMAGE),
    BILLING_ITEM_TITLE(textStyle = StyleKey.PAYMENT_OPTIONS_TITLE),
    BILLING_ITEM_DETAILS_TEXT(textStyle = StyleKey.PAYMENT_OPTIONS_DESC),
    BILLING_ITEM_REDEEM_TEXT(text = UI_KEY_BILLING_ITEM_REDEEM_TEXT, textStyle = StyleKey.SCREEN_DESC),
    BILLING_TITLE(text = UI_KEY_BILLING_TITLE_TEXT, textStyle = StyleKey.SCREEN_TITLE),
    BILLING_RESTORE_HINT_DESC_TEXT(text = UI_KEY_BILLING_RESTORE_DESC, textLink = UI_KEY_BILLING_RESTORE_ACTION, textStyle = StyleKey.PROMPT, textLinkStyle = StyleKey.LINK),
    STOREFRONT_LINK_1_TEXT(text = UI_KEY_STOREFRONT_LINK_1_DESC_TEXT, textLink = UI_KEY_STOREFRONT_LINK_1_URL_TEXT, textStyle = StyleKey.CUSTOM_LINK),
    STOREFRONT_LINK_2_TEXT(text = UI_KEY_STOREFRONT_LINK_2_DESC_TEXT, textLink = UI_KEY_STOREFRONT_LINK_2_URL_TEXT, textStyle = StyleKey.CUSTOM_LINK),
    CONFIRMATION_DIALOG_IMAGE(image = UI_KEY_ALERT_COMPONENT_IMAGE),
    BILLING_CONFIRMATION_TITLE_TEXT(text = UI_KEY_PAYMENT_CONFIRMATION_TITLE_TEXT, textStyle = StyleKey.CONFIRMATION_TITLE),
    BILLING_CONFIRMATION_DESC_TEXT(text = UI_KEY_PAYMENT_CONFIRMATION_DESC_TEXT, textStyle = StyleKey.CONFIRMATION_DESC),
    BILLING_CONFIRMATION_BUTTON_TEXT(text = UI_KEY_PAYMENT_CONFIRMATION_BUTTON_TEXT, textStyle = StyleKey.CONFIRMATION_BUTTON, image = UI_KEY_ALERT_BUTTON_IMAGE),

    RESET_PWD_CONFIRMATION_IMAGE(image = UI_KEY_ALERT_COMPONENT_IMAGE),
    RESET_PWD_CONFIRMATION_TITLE_TEXT(text = UI_KEY_PWD_CONFIRMATION_TITLE_TEXT, textStyle = StyleKey.CONFIRMATION_TITLE),
    RESET_PWD_CONFIRMATION_DESC_TEXT(text = UI_KEY_PWD_CONFIRMATION_DESC_TEXT, textStyle = StyleKey.CONFIRMATION_DESC),
    RESET_PWD_CONFIRMATION_BUTTON_TEXT(text = UI_KEY_PWD_CONFIRMATION_BUTTON_TEXT, textStyle = StyleKey.CONFIRMATION_BUTTON, image = UI_KEY_ALERT_BUTTON_IMAGE),

    RESTORE_CONFIRMATION_IMAGE(image = UI_KEY_ALERT_COMPONENT_IMAGE),
    RESTORE_CONFIRMATION_TITLE_TEXT(text = UI_KEY_RESTORE_CONFIRMATION_TITLE_TEXT, textStyle = StyleKey.CONFIRMATION_TITLE),
    RESTORE_CONFIRMATION_DESC_TEXT(text = UI_KEY_RESTORE_CONFIRMATION_DESC_TEXT, textStyle = StyleKey.CONFIRMATION_DESC),
    RESTORE_CONFIRMATION_BUTTON_TEXT(text = UI_KEY_RESTORE_CONFIRMATION_BUTTON_TEXT, textStyle = StyleKey.CONFIRMATION_BUTTON, image = UI_KEY_ALERT_BUTTON_IMAGE),

    LOGOUT_TITLE_TEXT(text = UI_KEY_LOGOUT_TITLE_TEXT, textStyle = StyleKey.CONFIRMATION_TITLE),
    LOGOUT_DESC_TEXT(text = UI_KEY_LOGOUT_DESC_TEXT, textStyle = StyleKey.CONFIRMATION_DESC),
    LOGOUT_OK_BUTTON_TEXT(text = UI_KEY_LOGOUT_BUTTON_TEXT, textStyle = StyleKey.CONFIRMATION_BUTTON, image = UI_KEY_ALERT_BUTTON_IMAGE),
    LOGOUT_CANCEL_BUTTON_TEXT(text = UI_KEY_LOGOUT_CANCEL_BUTTON_TEXT, textStyle = StyleKey.CANCEL_BUTTON, image = UI_KEY_CANCEL_BUTTON_IMAGE)
    // @formatter:on
}

// region Common UI keys
const val UI_KEY_TOOLBAR_BACK_IMAGE = "cam_back_button"
const val UI_KEY_TOOLBAR_CLOSE_IMAGE = "cam_close_button"
const val UI_KEY_TOOLBAR_LOGO_IMAGE = "cam_header_logo"
const val UI_KEY_BACKGROUND_IMAGE = "cam_background_image"
const val UI_KEY_ALERT_COMPONENT_IMAGE = "cam_alert_component"
const val UI_KEY_ALERT_BUTTON_IMAGE = "cam_alert_button_asset"
const val UI_KEY_CANCEL_BUTTON_IMAGE = "cam_cancel_button_asset"
// endregion

// region auth UI keys
const val UI_KEY_SIGN_UP_TITLE_TEXT = "sign_up_title_text"
const val UI_KEY_SIGN_UP_BUTTON_TEXT = "sign_up_button_text"
const val UI_KEY_SIGN_UP_BUTTON_IMAGE = "cam_action_button_asset"
const val UI_KEY_LOGIN_RESET_PWD_TEXT = "password_reset_link_text"
const val UI_KEY_SIGN_UP_PROMPT_TEXT = "login_prompt_text"
const val UI_KEY_SIGN_UP_PROMPT_ACTION_TEXT = "login_link_text"
const val UI_KEY_LOGIN_TITLE_TEXT = "login_title_text"
const val UI_KEY_LOGIN_BUTTON_TEXT = "login_button_text"
const val UI_KEY_LOGIN_BUTTON_IMAGE = "cam_action_button_asset"
const val UI_KEY_LOGIN_PROMPT_TEXT = "sign_up_prompt_text"
const val UI_KEY_LOGIN_PROMPT_ACTION_TEXT = "sign_up_link_text"
const val UI_KEY_LOGIN_LINK_1_DESC_TEXT = "login_screen_custom_link_1_text"
const val UI_KEY_LOGIN_LINK_1_URL_TEXT = "login_screen_custom_link_1"
const val UI_KEY_LOGIN_LINK_2_DESC_TEXT = "login_screen_custom_link_2_text"
const val UI_KEY_LOGIN_LINK_2_URL_TEXT = "login_screen_custom_link_2"
const val UI_KEY_SIGN_UP_LINK_1_DESC_TEXT = "sign_up_screen_custom_link_1_text"
const val UI_KEY_SIGN_UP_LINK_1_URL_TEXT = "sign_up_screen_custom_link_1"
const val UI_KEY_SIGN_UP_LINK_2_DESC_TEXT = "sign_up_screen_custom_link_2_text"
const val UI_KEY_SIGN_UP_LINK_2_URL_TEXT = "sign_up_screen_custom_link_2"
const val UI_KEY_THIRD_PARTY_AUTH_TEXT = "alternative_authentication_prompt_text"
const val UI_KEY_THIRD_PARTY_SEPARATOR_TEXT = "alternative_authentication_separator_text"
const val UI_KEY_THIRD_PARTY_DIVIDER_LEFT_IMAGE = "cam_separator_asset_left"
const val UI_KEY_THIRD_PARTY_DIVIDER_RIGHT_IMAGE = "cam_separator_asset_right"
const val UI_KEY_INPUT_FIELD_IMAGE = "cam_input_field_asset"
const val UI_KEY_INPUT_ERROR_IMAGE = "cam_input_alert_indicator"
const val UI_KEY_VALIDATION_PARENT_IMAGE = "cam_field_alert_bubble_shadow"
const val UI_KEY_VALIDATION_BUBBLE_IMAGE = "cam_field_alert_bubble"
const val UI_KEY_FACEBOOK_IMAGE = "cam_icon_1"
// endregion

// region Account activation UI keys
const val UI_KEY_ACTIVATION_TITLE_TEXT = "account_activation_screen_title_text"
const val UI_KEY_ACTIVATION_DESC_TEXT = "account_activation_description_text"
const val UI_KEY_ACTIVATION_BUTTON_TEXT = "activate_account_button_text"
const val UI_KEY_ACTIVATION_RESEND_TEXT = "resend_code_text"
const val UI_KEY_ACTIVATION_BUTTON_IMAGE= "cam_action_button_asset"
// endregion

// region Password reset UI keys
const val UI_KEY_PWD_RESET_TITLE_TEXT = "password_reset_title_text"
const val UI_KEY_PWD_RESET_DESC_TEXT = "password_reset_description_text"
const val UI_KEY_PWD_RESET_BUTTON_TEXT = "password_reset_button_text"
const val UI_KEY_PWD_RESET_BUTTON_IMAGE= "cam_action_button_asset"
// endregion

// region Password update UI keys
const val UI_KEY_PWD_ACTIVATION_CODE_BUTTON_TEXT = "send_pw_activation_code_button_text"
const val UI_KEY_PWD_UPDATE_TITLE_TEXT = "password_update_title_text"
const val UI_KEY_PWD_UPDATE_DESC_TEXT = "password_update_description_text"
const val UI_KEY_PWD_UPDATE_BUTTON_TEXT = "password_update_button_text"
// endregion

// region Billing item UI keys
const val UI_KEY_BILLING_ITEM_SUBS_BUTTON_IMAGE = "cam_payment_option_button_asset"
const val UI_KEY_BILLING_ITEM_SUBS_BUTTON_TEXT = "payment_option_button_text"
const val UI_KEY_BILLING_ITEM_IMAGE = "cam_payment_option_component_asset"
const val UI_KEY_BILLING_ITEM_REDEEM_TEXT = "payment_option_redeem_text"
// region Billing fragments
const val UI_KEY_BILLING_TITLE_TEXT = "storefront_screen_title_text"
const val UI_KEY_BILLING_RESTORE_DESC = "restore_prompt_text"
const val UI_KEY_BILLING_RESTORE_ACTION = "restore_link_text"
const val UI_KEY_STOREFRONT_LINK_1_DESC_TEXT = "storefront_screen_custom_link_1_text"
const val UI_KEY_STOREFRONT_LINK_1_URL_TEXT = "storefront_screen_custom_link_1"
const val UI_KEY_STOREFRONT_LINK_2_DESC_TEXT = "storefront_screen_custom_link_2_text"
const val UI_KEY_STOREFRONT_LINK_2_URL_TEXT = "storefront_screen_custom_link_2"
// endregion
// endregion

// region Confirmation dialog
// payments
const val UI_KEY_PAYMENT_CONFIRMATION_TITLE_TEXT = "payment_confirmation_title_text"
const val UI_KEY_PAYMENT_CONFIRMATION_DESC_TEXT = "payment_confirmation_description_text"
const val UI_KEY_PAYMENT_CONFIRMATION_BUTTON_TEXT = "confirmation_button_text"
// reset password
const val UI_KEY_PWD_CONFIRMATION_TITLE_TEXT = "password_reset_confirmation_title_text"
const val UI_KEY_PWD_CONFIRMATION_DESC_TEXT = "password_reset_confirmation_description_text"
const val UI_KEY_PWD_CONFIRMATION_BUTTON_TEXT = "confirmation_button_text"
// restore purchases
const val UI_KEY_RESTORE_CONFIRMATION_TITLE_TEXT = "restore_purchase_confirmation_title_text"
const val UI_KEY_RESTORE_CONFIRMATION_DESC_TEXT = "restore_purchase_confirmation_description_text"
const val UI_KEY_RESTORE_CONFIRMATION_BUTTON_TEXT = "confirmation_button_text"
// logout
const val UI_KEY_LOGOUT_TITLE_TEXT = "logout_title_text"
const val UI_KEY_LOGOUT_DESC_TEXT = "logout_description_text"
const val UI_KEY_LOGOUT_BUTTON_TEXT = "confirmation_button_text"
const val UI_KEY_LOGOUT_CANCEL_BUTTON_TEXT = "cancel_button_text"
// endregion

// region Other
// endregion




