package com.applicaster.cam.config.ui

enum class UIKey(
    val text: String? = null,
    val hint: String? = null,
    val textStyle: String? = null,
    val image: String? = null
) {
    // @formatter:off
    TOOLBAR_BACK_BUTTON(image = UI_KEY_TOOLBAR_BACK_IMAGE),
    TOOLBAR_CLOSE_BUTTON(image = UI_KEY_TOOLBAR_CLOSE_IMAGE),
    TOOLBAR_HEADER_LOGO_IMAGE(image = UI_KEY_TOOLBAR_LOGO_IMAGE),
    BACKGROUND_IMAGE(image = UI_KEY_BACKGROUND_IMAGE),

    LOGIN_TITLE(text = UI_KEY_LOGIN_TITLE_TEXT, textStyle = UI_KEY_TITLE_TEXT_STYLE),
    LOGIN_RESET_PWD_TEXT(text = UI_KEY_LOGIN_RESET_PWD_TEXT, textStyle = UI_KEY_LOGIN_RESET_PWD_TEXT),
    LOGIN_ALT_AUTH_TEXT(text = UI_KEY_THIRD_PARTY_LOGIN_TEXT, textStyle = UI_KEY_THIRD_PARTY_LOGIN_TEXT),
    LOGIN_BUTTON(text = UI_KEY_LOGIN_BUTTON_TEXT, image = UI_KEY_LOGIN_BUTTON_IMAGE, textStyle = UI_KEY_ACTION_BUTTON_TEXT_STYLE),
    LOGIN_PROMPT_TEXT(text = UI_KEY_LOGIN_PROMPT_TEXT, textStyle = UI_KEY_LOGIN_PROMPT_TEXT),
    LOGIN_PROMPT_ACTION_TEXT(text = UI_KEY_LOGIN_PROMPT_ACTION_TEXT, textStyle = UI_KEY_LOGIN_PROMPT_ACTION_TEXT),
    SIGN_UP_TITLE(text = UI_KEY_SIGN_UP_TITLE_TEXT, textStyle = UI_KEY_TITLE_TEXT_STYLE),
    SIGN_UP_ALT_AUTH_TEXT(text = UI_KEY_THIRD_PARTY_SIGN_UP_TEXT, textStyle = UI_KEY_THIRD_PARTY_SIGN_UP_TEXT),
    SIGN_UP_BUTTON(text = UI_KEY_SIGN_UP_BUTTON_TEXT, image = UI_KEY_SIGN_UP_BUTTON_IMAGE, textStyle = UI_KEY_ACTION_BUTTON_TEXT_STYLE),
    SIGN_UP_PROMPT_TEXT(text = UI_KEY_SIGN_UP_PROMPT_TEXT, textStyle = UI_KEY_SIGN_UP_PROMPT_TEXT),
    SIGN_UP_PROMPT_ACTION_TEXT(text = UI_KEY_SIGN_UP_PROMPT_ACTION_TEXT, textStyle = UI_KEY_SIGN_UP_PROMPT_ACTION_TEXT),
    AUTH_SEPARATOR_TEXT(text = UI_KEY_THIRD_PARTY_SEPARATOR_TEXT, textStyle = UI_KEY_THIRD_PARTY_SEPARATOR_TEXT),
    AUTH_LEFT_DIVIDER_IMAGE(image = UI_KEY_THIRD_PARTY_DIVIDER_LEFT_IMAGE),
    AUTH_RIGHT_DIVIDER_IMAGE(image = UI_KEY_THIRD_PARTY_DIVIDER_RIGHT_IMAGE),
    AUTH_INPUT_FIELD(image = UI_KEY_INPUT_FIELD_IMAGE),
    AUTH_FACEBOOK_IMAGE(image = UI_KEY_FACEBOOK_IMAGE),

    PASSWORD_RESET_TITLE_TEXT(text = UI_KEY_PWD_RESET_TITLE_TEXT, textStyle = UI_KEY_TITLE_TEXT_STYLE),
    PASSWORD_RESET_DESC_TEXT(text = UI_KEY_PWD_RESET_DESC_TEXT, textStyle = UI_KEY_DESC_TEXT_STYLE),
    PASSWORD_RESET_ACTION_BUTTON(text = UI_KEY_PWD_RESET_BUTTON_TEXT, image = UI_KEY_PWD_RESET_BUTTON_IMAGE, textStyle = UI_KEY_ACTION_BUTTON_TEXT_STYLE),
    BILLING_ITEM_SUBS_BUTTON(text = UI_KEY_BILLING_ITEM_SUBS_BUTTON_TEXT, textStyle = UI_KEY_BILLING_ITEM_SUBS_BUTTON_TEXT, image = UI_KEY_BILLING_ITEM_SUBS_BUTTON_IMAGE),

    BILLING_ITEM_PARENT(image = UI_KEY_BILLING_ITEM_IMAGE),
    BILLING_ITEM_TITLE(textStyle = UI_KEY_BILLING_ITEM_TITLE_TEXT),
    BILLING_ITEM_DETAILS_TEXT(textStyle = UI_KEY_BILLING_ITEM_DETAILS_TEXT),
    BILLING_ITEM_REDEEM_TEXT(text = UI_KEY_BILLING_ITEM_REDEEM_TEXT, textStyle = UI_KEY_BILLING_ITEM_REDEEM_TEXT),
    BILLING_TITLE(text = UI_KEY_BILLING_TITLE_TEXT, textStyle = UI_KEY_TITLE_TEXT_STYLE),
    BILLING_PROMPT_TEXT(text = UI_KEY_BILLING_RESTORE_DESC, textStyle = UI_KEY_BILLING_RESTORE_DESC),
    BILLING_RESTORE_ACTION_TEXT(text = UI_KEY_BILLING_RESTORE_ACTION, textStyle = UI_KEY_BILLING_RESTORE_ACTION),
    BILLING_RESTORE_HINT_DESC_TEXT(text = UI_KEY_BILLING_RESTORE_DESC, textStyle = UI_KEY_BILLING_RESTORE_DESC),

    BILLING_CONFIRMATION_IMAGE(image = UI_KEY_ALERT_COMPONENT_IMAGE),
    BILLING_CONFIRMATION_TITLE_TEXT(text = UI_KEY_PAYMENT_CONFIRMATION_TITLE_TEXT, textStyle = UI_KEY_ALERT_TITLE_TEXT_STYLE),
    BILLING_CONFIRMATION_DESC_TEXT(text = UI_KEY_PAYMENT_CONFIRMATION_DESC_TEXT, textStyle =UI_KEY_ALERT_DESC_TEXT_STYLE),
    BILLING_CONFIRMATION_BUTTON_TEXT(text = UI_KEY_PAYMENT_CONFIRMATION_BUTTON_TEXT, textStyle = UI_KEY_ALERT_BUTTON_TEXT_STYLE, image = UI_KEY_ALERT_BUTTON_IMAGE),

    RESET_PWD_CONFIRMATION_IMAGE(image = UI_KEY_ALERT_COMPONENT_IMAGE),
    RESET_PWD_CONFIRMATION_TITLE_TEXT(text = UI_KEY_PWD_CONFIRMATION_TITLE_TEXT, textStyle = UI_KEY_ALERT_TITLE_TEXT_STYLE),
    RESET_PWD_CONFIRMATION_DESC_TEXT(text = UI_KEY_PWD_CONFIRMATION_DESC_TEXT, textStyle = UI_KEY_ALERT_DESC_TEXT_STYLE),
    RESET_PWD_CONFIRMATION_BUTTON_TEXT(text = UI_KEY_PWD_CONFIRMATION_BUTTON_TEXT, textStyle = UI_KEY_ALERT_BUTTON_TEXT_STYLE, image = UI_KEY_ALERT_BUTTON_IMAGE),

    RESTORE_CONFIRMATION_IMAGE(image = UI_KEY_ALERT_COMPONENT_IMAGE),
    RESTORE_CONFIRMATION_TITLE_TEXT(text = UI_KEY_RESTORE_CONFIRMATION_TITLE_TEXT, textStyle = UI_KEY_ALERT_TITLE_TEXT_STYLE),
    RESTORE_CONFIRMATION_DESC_TEXT(text = UI_KEY_RESTORE_CONFIRMATION_DESC_TEXT, textStyle = UI_KEY_ALERT_DESC_TEXT_STYLE),
    RESTORE_CONFIRMATION_BUTTON_TEXT(text = UI_KEY_RESTORE_CONFIRMATION_BUTTON_TEXT, textStyle = UI_KEY_ALERT_BUTTON_TEXT_STYLE, image = UI_KEY_ALERT_BUTTON_IMAGE)
    // @formatter:on
}

// region Common UI keys
const val UI_KEY_TOOLBAR_BACK_IMAGE = "back_button"
const val UI_KEY_TOOLBAR_CLOSE_IMAGE = "close_button"
const val UI_KEY_TOOLBAR_LOGO_IMAGE = "header_logo"
const val UI_KEY_BACKGROUND_IMAGE = "background_image"
const val UI_KEY_ACTION_BUTTON_TEXT_STYLE = "Action_button_text"
const val UI_KEY_TITLE_TEXT_STYLE = "Screen_title_text"
const val UI_KEY_DESC_TEXT_STYLE = "Screen_description_text"
const val UI_KEY_ALERT_COMPONENT_IMAGE = "alert_component"
const val UI_KEY_ALERT_TITLE_TEXT_STYLE = "Alert_title"
const val UI_KEY_ALERT_DESC_TEXT_STYLE = "Alert_description"
const val UI_KEY_ALERT_BUTTON_TEXT_STYLE = "alert_button_text"
const val UI_KEY_ALERT_BUTTON_IMAGE = "alert_button_asset"
// endregion

// region auth UI keys
const val UI_KEY_SIGN_UP_TITLE_TEXT = "sign_up_screen_title_text"
const val UI_KEY_SIGN_UP_BUTTON_TEXT = "sign_up_button_text"
const val UI_KEY_SIGN_UP_BUTTON_IMAGE = "action_button_asset"
const val UI_KEY_LOGIN_RESET_PWD_TEXT = "reset_password_text"
const val UI_KEY_SIGN_UP_PROMPT_TEXT = "sign_up_prompt_text"
const val UI_KEY_SIGN_UP_PROMPT_ACTION_TEXT = "sign_up_prompt_action_text"
const val UI_KEY_LOGIN_TITLE_TEXT = "login_screen_title_text"
const val UI_KEY_LOGIN_BUTTON_TEXT = "login_button_text"
const val UI_KEY_LOGIN_BUTTON_IMAGE = "action_button_asset"
const val UI_KEY_LOGIN_PROMPT_TEXT = "login_prompt_text"
const val UI_KEY_LOGIN_PROMPT_ACTION_TEXT = "login_prompt_action_text"
const val UI_KEY_THIRD_PARTY_SIGN_UP_TEXT = "alternative_sign_up_action_prompt_text"
const val UI_KEY_THIRD_PARTY_LOGIN_TEXT = "alternative_login_action_prompt_text"
const val UI_KEY_THIRD_PARTY_SEPARATOR_TEXT = "separator_text"
const val UI_KEY_THIRD_PARTY_DIVIDER_LEFT_IMAGE = "separator_asset_left"
const val UI_KEY_THIRD_PARTY_DIVIDER_RIGHT_IMAGE = "separator_asset_right"
const val UI_KEY_INPUT_FIELD_IMAGE = "input_field_asset"
const val UI_KEY_FACEBOOK_IMAGE = "icon_1"
// endregion

// region Password reset UI keys
const val UI_KEY_PWD_RESET_TITLE_TEXT = "reset_password_title_text"
const val UI_KEY_PWD_RESET_DESC_TEXT = "reset_password_details_text"
const val UI_KEY_PWD_RESET_BUTTON_TEXT = "reset_password_action_button_text"
const val UI_KEY_PWD_RESET_BUTTON_IMAGE= "action_button_asset"
// endregion

// region Billing item UI keys
const val UI_KEY_BILLING_ITEM_SUBS_BUTTON_IMAGE = "payment_option_button_asset"
const val UI_KEY_BILLING_ITEM_SUBS_BUTTON_TEXT = "payment_option_button_text"
const val UI_KEY_BILLING_ITEM_IMAGE = "payment_option_component_asset"
const val UI_KEY_BILLING_ITEM_TITLE_TEXT = "payment_option_title_text"
const val UI_KEY_BILLING_ITEM_DETAILS_TEXT = "payment_option_details_text"
const val UI_KEY_BILLING_ITEM_REDEEM_TEXT = "payment_option_redeem_text"
const val UI_KEY_BILLING_ITEM_LABEL_IMAGE = "payment_option_promo_img"
const val UI_KEY_BILLING_ITEM_LABEL_TEXT = "payment_option_promo_text"
// region Billing fragments
const val UI_KEY_BILLING_TITLE_TEXT = "payment_option_screen_title_text"
const val UI_KEY_BILLING_RESTORE_DESC = "payment_option_screen_hint_desc"
const val UI_KEY_BILLING_RESTORE_ACTION = "payment_option_screen_hint_action"
// endregion
// endregion

// region Confirmation dialog
// payments
const val UI_KEY_PAYMENT_CONFIRMATION_TITLE_TEXT = "payment_confirmation_title_text"
const val UI_KEY_PAYMENT_CONFIRMATION_DESC_TEXT = "payment_confirmation_description_text"
const val UI_KEY_PAYMENT_CONFIRMATION_BUTTON_TEXT = "payment_confirmation_button_text"
// reset password
const val UI_KEY_PWD_CONFIRMATION_TITLE_TEXT = "pwd_confirmation_title_text"
const val UI_KEY_PWD_CONFIRMATION_DESC_TEXT = "pwd_confirmation_description_text"
const val UI_KEY_PWD_CONFIRMATION_BUTTON_TEXT = "pwd_confirmation_button_text"
// restore purchases
const val UI_KEY_RESTORE_CONFIRMATION_TITLE_TEXT = "restore_confirmation_title_text"
const val UI_KEY_RESTORE_CONFIRMATION_DESC_TEXT = "restore_confirmation_description_text"
const val UI_KEY_RESTORE_CONFIRMATION_BUTTON_TEXT = "restore_confirmation_button_text"
// endregion

// region Other
// endregion




