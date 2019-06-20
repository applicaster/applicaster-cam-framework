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
    LOGIN_RESET_PWD_TEXT(text = UI_KEY_LOGIN_RESET_PWD_TEXT, textStyle = UI_KEY_LOGIN_RESET_PWD_STYLE),
    LOGIN_ALT_AUTH_TEXT(text = UI_KEY_THIRD_PARTY_AUTH_TEXT, textStyle = UI_KEY_THIRD_PARTY_AUTH_STYLE),
    LOGIN_BUTTON(text = UI_KEY_LOGIN_BUTTON_TEXT, image = UI_KEY_LOGIN_BUTTON_IMAGE, textStyle = UI_KEY_ACTION_BUTTON_TEXT_STYLE),
    LOGIN_PROMPT_TEXT(text = UI_KEY_LOGIN_PROMPT_TEXT, textStyle = UI_KEY_PROMPT_STYLE),
    LOGIN_PROMPT_ACTION_TEXT(text = UI_KEY_LOGIN_PROMPT_ACTION_TEXT, textStyle = UI_KEY_LINK_TEXT_STYLE),
    SIGN_UP_TITLE(text = UI_KEY_SIGN_UP_TITLE_TEXT, textStyle = UI_KEY_TITLE_TEXT_STYLE),
    SIGN_UP_ALT_AUTH_TEXT(text = UI_KEY_THIRD_PARTY_AUTH_TEXT, textStyle = UI_KEY_THIRD_PARTY_AUTH_STYLE),
    SIGN_UP_BUTTON(text = UI_KEY_SIGN_UP_BUTTON_TEXT, image = UI_KEY_SIGN_UP_BUTTON_IMAGE, textStyle = UI_KEY_ACTION_BUTTON_TEXT_STYLE),
    SIGN_UP_PROMPT_TEXT(text = UI_KEY_SIGN_UP_PROMPT_TEXT, textStyle = UI_KEY_PROMPT_STYLE),
    SIGN_UP_PROMPT_ACTION_TEXT(text = UI_KEY_SIGN_UP_PROMPT_ACTION_TEXT, textStyle = UI_KEY_LINK_TEXT_STYLE),
    AUTH_SEPARATOR_TEXT(text = UI_KEY_THIRD_PARTY_SEPARATOR_TEXT, textStyle = UI_KEY_THIRD_PARTY_SEPARATOR_STYLE),
    AUTH_LEFT_DIVIDER_IMAGE(image = UI_KEY_THIRD_PARTY_DIVIDER_LEFT_IMAGE),
    AUTH_RIGHT_DIVIDER_IMAGE(image = UI_KEY_THIRD_PARTY_DIVIDER_RIGHT_IMAGE),
    AUTH_INPUT_FIELD(image = UI_KEY_INPUT_FIELD_IMAGE),
    AUTH_VALIDATION_POPUP(image = UI_KEY_VALIDATION_PARENT_IMAGE),
    AUTH_VALIDATION_TEXT(image = UI_KEY_VALIDATION_BUBBLE_IMAGE),
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
    BILLING_RESTORE_ACTION_TEXT(text = UI_KEY_BILLING_RESTORE_ACTION, textStyle = UI_KEY_LINK_TEXT_STYLE),
    BILLING_RESTORE_HINT_DESC_TEXT(text = UI_KEY_BILLING_RESTORE_DESC, textStyle = UI_KEY_PROMPT_STYLE),

    CONFIRMATION_DIALOG_IMAGE(image = UI_KEY_ALERT_COMPONENT_IMAGE),
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
const val UI_KEY_SIGN_UP_TITLE_TEXT = "sign_up_title_text"
const val UI_KEY_SIGN_UP_BUTTON_TEXT = "sign_up_button_text"
const val UI_KEY_SIGN_UP_BUTTON_IMAGE = "action_button_asset"
const val UI_KEY_LOGIN_RESET_PWD_TEXT = "password_reset_link_text"
const val UI_KEY_LOGIN_RESET_PWD_STYLE = "restore_password"
const val UI_KEY_SIGN_UP_PROMPT_TEXT = "login_prompt_text"
const val UI_KEY_LINK_TEXT_STYLE= "Link_text"
const val UI_KEY_SIGN_UP_PROMPT_ACTION_TEXT = "login_link_text"
const val UI_KEY_LOGIN_TITLE_TEXT = "login_title_text"
const val UI_KEY_LOGIN_BUTTON_TEXT = "login_button_text"
const val UI_KEY_LOGIN_BUTTON_IMAGE = "action_button_asset"
const val UI_KEY_LOGIN_PROMPT_TEXT = "sign_up_prompt_text"
const val UI_KEY_PROMPT_STYLE = "Prompt_text"
const val UI_KEY_LOGIN_PROMPT_ACTION_TEXT = "sign_up_link_text"
const val UI_KEY_THIRD_PARTY_AUTH_TEXT = "alternative_authentication_prompt_text"
const val UI_KEY_THIRD_PARTY_AUTH_STYLE = "Alternative_login_prompt_text"
const val UI_KEY_THIRD_PARTY_SEPARATOR_TEXT = "alternative_authentication_separator_text"
const val UI_KEY_THIRD_PARTY_SEPARATOR_STYLE = "separator_text"
const val UI_KEY_THIRD_PARTY_DIVIDER_LEFT_IMAGE = "separator_asset_left"
const val UI_KEY_THIRD_PARTY_DIVIDER_RIGHT_IMAGE = "separator_asset_right"
const val UI_KEY_INPUT_FIELD_IMAGE = "input_field_asset"
const val UI_KEY_INPUT_ERROR_IMAGE = "input_alert_indicator"
const val UI_KEY_VALIDATION_PARENT_IMAGE = "field_alert_bubble_shadow"
const val UI_KEY_VALIDATION_BUBBLE_IMAGE = "field_alert_bubble"
const val UI_KEY_FACEBOOK_IMAGE = "icon_1"
// endregion

// region Password reset UI keys
const val UI_KEY_PWD_RESET_TITLE_TEXT = "password_reset_title_text"
const val UI_KEY_PWD_RESET_DESC_TEXT = "password_reset_description_text"
const val UI_KEY_PWD_RESET_BUTTON_TEXT = "password_reset_button_text"
const val UI_KEY_PWD_RESET_BUTTON_IMAGE= "action_button_asset"
// endregion

// region Billing item UI keys
const val UI_KEY_BILLING_ITEM_SUBS_BUTTON_IMAGE = "storefront_button_asset"
const val UI_KEY_BILLING_ITEM_SUBS_BUTTON_TEXT = "storefront_button_text"
const val UI_KEY_BILLING_ITEM_IMAGE = "storefront_component_asset"
const val UI_KEY_BILLING_ITEM_TITLE_TEXT = "storefront_title_text"
const val UI_KEY_BILLING_ITEM_DETAILS_TEXT = "storefront_details_text"
const val UI_KEY_BILLING_ITEM_REDEEM_TEXT = "storefront_redeem_text"
const val UI_KEY_BILLING_ITEM_LABEL_IMAGE = "storefront_promo_img"
const val UI_KEY_BILLING_ITEM_LABEL_TEXT = "storefront_promo_text"
// region Billing fragments
const val UI_KEY_BILLING_TITLE_TEXT = "storefront_screen_title_text"
const val UI_KEY_BILLING_RESTORE_DESC = "restore_promt_text"
const val UI_KEY_BILLING_RESTORE_ACTION = "restore_link_text"
// endregion
// endregion

// region Confirmation dialog
// payments
const val UI_KEY_PAYMENT_CONFIRMATION_TITLE_TEXT = "payment_confirmation_title_text"
const val UI_KEY_PAYMENT_CONFIRMATION_DESC_TEXT = "payment_confirmation_description_text"
const val UI_KEY_PAYMENT_CONFIRMATION_BUTTON_TEXT = "payment_confirmation_button_text"
// reset password
const val UI_KEY_PWD_CONFIRMATION_TITLE_TEXT = "password_reset_confirmation_title_text"
const val UI_KEY_PWD_CONFIRMATION_DESC_TEXT = "password_reset_confirmation_description_text"
const val UI_KEY_PWD_CONFIRMATION_BUTTON_TEXT = "password_reset_confirmation_button_text"
// restore purchases
const val UI_KEY_RESTORE_CONFIRMATION_TITLE_TEXT = "restore_confirmation_title_text"
const val UI_KEY_RESTORE_CONFIRMATION_DESC_TEXT = "restore_confirmation_description_text"
const val UI_KEY_RESTORE_CONFIRMATION_BUTTON_TEXT = "restore_confirmation_button_text"
// endregion

// region Other
// endregion




