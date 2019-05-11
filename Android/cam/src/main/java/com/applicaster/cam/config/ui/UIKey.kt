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
    THIRD_PARTY_AUTH_DESC(text= UI_KEY_THIRD_PARTY_AUTH_TEXT, image = UI_KEY_THIRD_PARTY_AUTH_BCKG)
    // @formatter:on
}

const val UI_KEY_SIGN_UP_TITLE_TEXT = "key_sign_up_title"
const val UI_KEY_SIGN_UP_TITLE_COLOR = "key_sign_up_color"
const val UI_KEY_SIGN_UP_BUTTON_TEXT = "key_sign_up_button"
const val UI_KEY_SIGN_UP_BUTTON_TEXT_SIZE = "key_sign_up_button_size"
const val UI_KEY_THIRD_PARTY_AUTH_TEXT = "key_third_party_auth_title"
const val UI_KEY_THIRD_PARTY_AUTH_BCKG = "key_third_party_auth_img"

