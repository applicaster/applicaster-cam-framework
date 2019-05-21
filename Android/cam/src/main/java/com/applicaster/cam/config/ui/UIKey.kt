package com.applicaster.cam.config.ui

enum class UIKey(
    val text: String? = null,
    val hint: String? = null,
    val textSize: String? = null,
    val textColor: String? = null,
    val font: String? = null,
    val image: String? = null
) {
    // @formatter:off
    TOOLBAR_BACK_BUTTON(image = UI_KEY_TOOLBAR_BACK),
    TOOLBAR_CLOSE_BUTTON(image = UI_KEY_TOOLBAR_CLOSE),
    TOOLBAR_HEADER_LOGO(image = UI_KEY_TOOLBAR_LOGO),
    BACKGROUND_IMAGE(image = UI_KEY_BACKGROUND_IMAGE),
    LOGIN_TITLE(text =UI_KEY_LOGIN_TITLE_TEXT),
    LOGIN_RESET_PWD(text = UI_KEY_LOGIN_RESET_PWD_TEXT),
    LOGIN_ALT_AUTH_TEXT(text = UI_KEY_THIRD_PARTY_LOGIN_TEXT),
    LOGIN_BTN_TEXT(text = UI_KEY_LOGIN_BUTTON_TEXT, image = UI_KEY_LOGIN_BUTTON_IMAGE),
    LOGIN_PROMPT_TEXT(text = UI_KEY_LOGIN_PROMPT_TEXT),
    LOGIN_PROMPT_ACTION_TEXT(text = UI_KEY_LOGIN_PROMPT_ACTION_TEXT),
    SIGN_UP_TITLE(text = UI_KEY_SIGN_UP_TITLE_TEXT),
    SIGN_UP_ALT_AUTH_TEXT(text = UI_KEY_THIRD_PARTY_SIGN_UP_TEXT),
    SIGN_UP_BUTTON(text = UI_KEY_SIGN_UP_BUTTON_TEXT, image = UI_KEY_SIGN_UP_BUTTON_IMAGE),
    SIGN_UP_PROMPT_TEXT(text = UI_KEY_SIGN_UP_PROMPT_TEXT),
    SIGN_UP_PROMPT_ACTION_TEXT(text = UI_KEY_SIGN_UP_PROMPT_ACTION_TEXT),
    SEPARATOR_TEXT(text = UI_KEY_THIRD_PARTY_SEPARATOR_TEXT),
    BILLING_ITEM_SUBS_BUTTON(text = UI_KEY_BILLING_ITEM_SUBS_BUTTON_TEXT, textSize = UI_KEY_BILLING_ITEM_SUBS_BUTTON_TEXT_SIZE, image = UI_KEY_BILLING_ITEM_SUBS_BUTTON_BCKG),
    BILLING_ITEM_TITLE(textSize = UI_KEY_BILLING_ITEM_TITLE_TEXT_SIZE),
    BILLING_ITEM_DETAILS(textSize = UI_KEY_BILLING_ITEM_DETAILS_TEXT_SIZE),
    BILLING_ITEM_REDEEM(text = UI_KEY_BILLING_ITEM_REDEEM_TEXT, textSize = UI_KEY_BILLING_ITEM_REDEEM_TEXT_SIZE),
    BILLING_LAYOUT(image = UI_KEY_BILLING_BCKG),
    BILLING_TITLE(text = UI_KEY_BILLING_TITLE_TEXT, textSize = UI_KEY_BILLING_TITLE_TEXT_SIZE),
    BILLING_PROMPT(text = UI_KEY_BILLING_RESTORE_TEXT, textSize = UI_KEY_BILLING_RESTORE_TEXT_SIZE),
    BILLING_LINK(text = UI_KEY_BILLING_LINK_TEXT, textSize = UI_KEY_BILLING_LINK_TEXT_SIZE)
    // @formatter:on
}

// region Common UI keys
const val UI_KEY_TOOLBAR_BACK = "back_button"
const val UI_KEY_TOOLBAR_CLOSE = "close_button"
const val UI_KEY_TOOLBAR_LOGO = "header_logo"
const val UI_KEY_BACKGROUND_IMAGE = "background_image"
// endregion

// region Sign up UI keys
const val UI_KEY_SIGN_UP_TITLE_TEXT = "signup_screen_title_text"
const val UI_KEY_SIGN_UP_BUTTON_TEXT = "signup_button_text"
const val UI_KEY_SIGN_UP_BUTTON_IMAGE = "signup_button_image"
const val UI_KEY_LOGIN_RESET_PWD_TEXT = "reset_password_text"
const val UI_KEY_SIGN_UP_PROMPT_TEXT = "sign_up_prompt_text"
const val UI_KEY_SIGN_UP_PROMPT_ACTION_TEXT = "sign_up_prompt_action_text"
const val UI_KEY_LOGIN_TITLE_TEXT = "login_screen_title_text"
const val UI_KEY_LOGIN_BUTTON_TEXT = "login_button_text"
const val UI_KEY_LOGIN_BUTTON_IMAGE = "login_button_image"
const val UI_KEY_LOGIN_PROMPT_TEXT = "login_prompt_text"
const val UI_KEY_LOGIN_PROMPT_ACTION_TEXT = "login_prompt_action_text"
const val UI_KEY_THIRD_PARTY_SIGN_UP_TEXT = "alternative_sign_up_action_prompt_text"
const val UI_KEY_THIRD_PARTY_LOGIN_TEXT = "alternative_login_action_prompt_text"
const val UI_KEY_THIRD_PARTY_SEPARATOR_TEXT = "separator_text"
// endregion

// region Billing item UI keys
const val UI_KEY_BILLING_ITEM_SUBS_BUTTON_BCKG = "key_billing_item_subs_bckg"
const val UI_KEY_BILLING_ITEM_SUBS_BUTTON_TEXT = "key_billing_item_subs_text"
const val UI_KEY_BILLING_ITEM_SUBS_BUTTON_TEXT_SIZE = "key_billing_item_subs_text_size"
const val UI_KEY_BILLING_ITEM_TITLE_TEXT = "key_billing_item_title_text"
const val UI_KEY_BILLING_ITEM_TITLE_TEXT_SIZE = "key_billing_item_title_text_size"
const val UI_KEY_BILLING_ITEM_DETAILS_TEXT = "key_billing_item_details_text"
const val UI_KEY_BILLING_ITEM_DETAILS_TEXT_SIZE = "key_billing_item_details_text_size"
const val UI_KEY_BILLING_ITEM_REDEEM_TEXT = "key_billing_item_redeem_text"
const val UI_KEY_BILLING_ITEM_REDEEM_TEXT_SIZE = "key_billing_item_redeem_text_size"
const val UI_KEY_BILLING_ITEM_LABEL_BCKG = "key_billing_item_label_img"
// region Billing fragments
const val UI_KEY_BILLING_BCKG = "key_billing_bckg"
const val UI_KEY_BILLING_TITLE_TEXT = "key_billing_title_text"
const val UI_KEY_BILLING_TITLE_TEXT_SIZE = "key_billing_title_text_size"
const val UI_KEY_BILLING_RESTORE_TEXT = "key_billing_prompt_text"
const val UI_KEY_BILLING_RESTORE_TEXT_SIZE = "key_billing_prompt_text_size"
const val UI_KEY_BILLING_RESTORE_ACTION = "key_billing_prompt_text"
const val UI_KEY_BILLING_RESTORE_ACTION_SIZE = "key_billing_prompt_text_size"
const val UI_KEY_BILLING_LINK_TEXT = "key_billing_link_text"
const val UI_KEY_BILLING_LINK_TEXT_SIZE = "key_billing_link_text_size"
// endregion
// endregion

// region Other
// endregion




