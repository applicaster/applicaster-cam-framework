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
    SIGN_UP_TITLE(text = UI_KEY_SIGN_UP_TITLE_TEXT, textColor = UI_KEY_SIGN_UP_TITLE_COLOR),
    SIGN_UP_BUTTON(text = UI_KEY_SIGN_UP_BUTTON_TEXT, textSize = UI_KEY_SIGN_UP_BUTTON_TEXT_SIZE),
    THIRD_PARTY_AUTH_DESC(text= UI_KEY_THIRD_PARTY_AUTH_TEXT, image = UI_KEY_THIRD_PARTY_AUTH_BCKG),
    //billing
    BILLING_ITEM_SUBS_BUTTON(text = UI_KEY_BILLING_ITEM_SUBS_BUTTON_TEXT, textSize = UI_KEY_BILLING_ITEM_SUBS_BUTTON_TEXT_SIZE, image = UI_KEY_BILLING_ITEM_SUBS_BUTTON_BCKG),
    BILLING_ITEM_TITLE(textSize = UI_KEY_BILLING_ITEM_TITLE_TEXT_SIZE),
    BILLING_ITEM_DETAILS(textSize = UI_KEY_BILLING_ITEM_DETAILS_TEXT_SIZE),
    BILLING_ITEM_REDEEM(text = UI_KEY_BILLING_ITEM_REDEEM_TEXT, textSize = UI_KEY_BILLING_ITEM_REDEEM_TEXT_SIZE),
    BILLING_LAYOUT(image = UI_KEY_BILLING_BCKG),
    BILLING_TITLE(text = UI_KEY_BILLING_TITLE_TEXT, textSize = UI_KEY_BILLING_TITLE_TEXT_SIZE),
    BILLING_PROMPT(text = UI_KEY_BILLING_RESTORE_DESC, textSize = UI_KEY_BILLING_RESTORE_DESC_SIZE),
    BILLING_RESTORE_ACTION(text = UI_KEY_BILLING_RESTORE_ACTION, textSize = UI_KEY_BILLING_RESTORE_ACTION_SIZE),
    BILLING_RESTORE_HINT_DESC(text = UI_KEY_BILLING_RESTORE_DESC, textSize = UI_KEY_BILLING_RESTORE_DESC_SIZE)
    // @formatter:on
}

// region Sign up UI keys
const val UI_KEY_SIGN_UP_TITLE_TEXT = "key_sign_up_title"
const val UI_KEY_SIGN_UP_TITLE_COLOR = "key_sign_up_color"
const val UI_KEY_SIGN_UP_BUTTON_TEXT = "key_sign_up_button"
const val UI_KEY_SIGN_UP_BUTTON_TEXT_SIZE = "key_sign_up_button_size"
const val UI_KEY_THIRD_PARTY_AUTH_TEXT = "key_third_party_auth_title"
const val UI_KEY_THIRD_PARTY_AUTH_BCKG = "key_third_party_auth_img"
// endregion

// region Billing item UI keys
const val UI_KEY_BILLING_ITEM_SUBS_BUTTON_BCKG = "payment_option_button_img"
const val UI_KEY_BILLING_ITEM_SUBS_BUTTON_TEXT = "payment_option_button_text"
const val UI_KEY_BILLING_ITEM_SUBS_BUTTON_TEXT_SIZE = "payment_option_button_text_size"
const val UI_KEY_BILLING_ITEM_TITLE_TEXT = "payment_option_title_text"
const val UI_KEY_BILLING_ITEM_TITLE_TEXT_SIZE = "payment_option_title_text_size"
const val UI_KEY_BILLING_ITEM_DETAILS_TEXT = "payment_option_details_text"
const val UI_KEY_BILLING_ITEM_DETAILS_TEXT_SIZE = "payment_option_details_text_size"
const val UI_KEY_BILLING_ITEM_REDEEM_TEXT = "payment_option_redeem_text"
const val UI_KEY_BILLING_ITEM_REDEEM_TEXT_SIZE = "payment_option_redeem_text_size"
const val UI_KEY_BILLING_ITEM_LABEL_BCKG = "payment_option_promo_img"
const val UI_KEY_BILLING_ITEM_LABEL_TEXT = "payment_option_promo_text"
// region Billing fragments
const val UI_KEY_BILLING_BCKG = "payment_option_screen_background_img"
const val UI_KEY_BILLING_TITLE_TEXT = "payment_option_screen_title_text"
const val UI_KEY_BILLING_TITLE_TEXT_SIZE = "payment_option_screen_title_text_size"
const val UI_KEY_BILLING_RESTORE_DESC = "payment_option_screen_hint_desc"
const val UI_KEY_BILLING_RESTORE_DESC_SIZE = "payment_option_screen_hint_desc_size"
const val UI_KEY_BILLING_RESTORE_ACTION = "payment_option_screen_hint_action"
const val UI_KEY_BILLING_RESTORE_ACTION_SIZE = "payment_option_screen_hint_action_size"
// endregion
// endregion

// region Other
// endregion




