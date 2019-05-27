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
    TOOLBAR_HEADER_LOGO(image = UI_KEY_TOOLBAR_LOGO_IMAGE),
    BACKGROUND_IMAGE(image = UI_KEY_BACKGROUND_IMAGE),
    LOGIN_TITLE(text = UI_KEY_LOGIN_TITLE_TEXT, textStyle = UI_KEY_LOGIN_TITLE_TEXT),
    LOGIN_RESET_PWD(text = UI_KEY_LOGIN_RESET_PWD_TEXT, textStyle = UI_KEY_LOGIN_RESET_PWD_TEXT),
    LOGIN_ALT_AUTH_TEXT(text = UI_KEY_THIRD_PARTY_LOGIN_TEXT, textStyle = UI_KEY_THIRD_PARTY_LOGIN_TEXT),
    LOGIN_BTN_TEXT(text = UI_KEY_LOGIN_BUTTON_TEXT, image = UI_KEY_LOGIN_BUTTON_IMAGE, textStyle = UI_KEY_LOGIN_BUTTON_TEXT),
    LOGIN_PROMPT_TEXT(text = UI_KEY_LOGIN_PROMPT_TEXT, textStyle = UI_KEY_LOGIN_PROMPT_TEXT),
    LOGIN_PROMPT_ACTION_TEXT(text = UI_KEY_LOGIN_PROMPT_ACTION_TEXT, textStyle = UI_KEY_LOGIN_PROMPT_ACTION_TEXT),
    SIGN_UP_TITLE(text = UI_KEY_SIGN_UP_TITLE_TEXT, textStyle = UI_KEY_SIGN_UP_TITLE_TEXT),
    SIGN_UP_ALT_AUTH_TEXT(text = UI_KEY_THIRD_PARTY_SIGN_UP_TEXT, textStyle = UI_KEY_THIRD_PARTY_SIGN_UP_TEXT),
    SIGN_UP_BUTTON(text = UI_KEY_SIGN_UP_BUTTON_TEXT, image = UI_KEY_SIGN_UP_BUTTON_IMAGE, textStyle = UI_KEY_SIGN_UP_BUTTON_TEXT),
    SIGN_UP_PROMPT_TEXT(text = UI_KEY_SIGN_UP_PROMPT_TEXT, textStyle = UI_KEY_SIGN_UP_PROMPT_TEXT),
    SIGN_UP_PROMPT_ACTION_TEXT(text = UI_KEY_SIGN_UP_PROMPT_ACTION_TEXT, textStyle = UI_KEY_SIGN_UP_PROMPT_ACTION_TEXT),
    AUTH_SEPARATOR_TEXT(text = UI_KEY_THIRD_PARTY_SEPARATOR_TEXT, textStyle = UI_KEY_THIRD_PARTY_SEPARATOR_TEXT),
    AUTH_LEFT_DIVIDER(image = UI_KEY_THIRD_PARTY_DIVIDER_LEFT_IMAGE),
    AUTH_RIGHT_DIVIDER(image = UI_KEY_THIRD_PARTY_DIVIDER_RIGHT_IMAGE),
    AUTH_INPUT_FIELD(image = UI_KEY_INPUT_FIELD_IMAGE),
    AUTH_FACEBOOK_IMAGE(image = UI_KEY_FACEBOOK_IMAGE),
    BILLING_ITEM_SUBS_BUTTON(text = UI_KEY_BILLING_ITEM_SUBS_BUTTON_TEXT, textStyle = UI_KEY_BILLING_ITEM_SUBS_BUTTON_TEXT, image = UI_KEY_BILLING_ITEM_SUBS_BUTTON_IMAGE),
    BILLING_ITEM_PARENT(image = UI_KEY_BILLING_ITEM_BCKG),
    BILLING_ITEM_TITLE(textStyle = UI_KEY_BILLING_ITEM_TITLE_TEXT),
    BILLING_ITEM_DETAILS(textStyle = UI_KEY_BILLING_ITEM_DETAILS_TEXT),
    BILLING_ITEM_REDEEM(text = UI_KEY_BILLING_ITEM_REDEEM_TEXT, textStyle = UI_KEY_BILLING_ITEM_REDEEM_TEXT),
    BILLING_TITLE(text = UI_KEY_BILLING_TITLE_TEXT, textStyle = UI_KEY_BILLING_TITLE_TEXT),
    BILLING_PROMPT(text = UI_KEY_BILLING_RESTORE_DESC, textStyle = UI_KEY_BILLING_RESTORE_DESC),
    BILLING_RESTORE_ACTION(text = UI_KEY_BILLING_RESTORE_ACTION, textStyle = UI_KEY_BILLING_RESTORE_ACTION),
    BILLING_RESTORE_HINT_DESC(text = UI_KEY_BILLING_RESTORE_DESC, textStyle = UI_KEY_BILLING_RESTORE_DESC)
    // @formatter:on
}

// region Common UI keys
const val UI_KEY_TOOLBAR_BACK_IMAGE = "back_button"
const val UI_KEY_TOOLBAR_CLOSE_IMAGE = "close_button"
const val UI_KEY_TOOLBAR_LOGO_IMAGE = "header_logo"
const val UI_KEY_BACKGROUND_IMAGE = "background_image"
// endregion

// region Sign up UI keys
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

// region Billing item UI keys
const val UI_KEY_BILLING_ITEM_SUBS_BUTTON_IMAGE = "payment_option_button_asset"
const val UI_KEY_BILLING_ITEM_SUBS_BUTTON_TEXT = "payment_option_button_text"
const val UI_KEY_BILLING_ITEM_BCKG = "payment_option_component_asset"
const val UI_KEY_BILLING_ITEM_TITLE_TEXT = "payment_option_title_text"
const val UI_KEY_BILLING_ITEM_DETAILS_TEXT = "payment_option_details_text"
const val UI_KEY_BILLING_ITEM_REDEEM_TEXT = "payment_option_redeem_text"
const val UI_KEY_BILLING_ITEM_LABEL_BCKG = "payment_option_promo_img"
const val UI_KEY_BILLING_ITEM_LABEL_TEXT = "payment_option_promo_text"
// region Billing fragments
const val UI_KEY_BILLING_TITLE_TEXT = "payment_option_screen_title_text"
const val UI_KEY_BILLING_RESTORE_DESC = "payment_option_screen_hint_desc"
const val UI_KEY_BILLING_RESTORE_ACTION = "payment_option_screen_hint_action"
// endregion
// endregion

// region Other
// endregion




