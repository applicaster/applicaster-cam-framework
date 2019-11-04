package com.applicaster.cam.config.ui

enum class StyleKey(
    private val key: String? = null
) {
    // @formatter:off
    INPUT_FIELD_LABEL(STYLE_KEY_INPUT_FIELD_LABEL),
    ACTION_BUTTON(STYLE_KEY_ACTION_BUTTON),
    PROMPT(STYLE_KEY_PROMPT),
    LINK(STYLE_KEY_LINK),
    SCREEN_TITLE(STYLE_KEY_SCREEN_TITLE),
    SCREEN_DESC(STYLE_KEY_SCREEN_DESC),
    ALT_AUTH_SEPARATOR(STYLE_KEY_ALT_AUTH_SEPARATOR),
    ALT_AUTH_PROMPT(STYLE_KEY_ALT_AUTH_PROMPT),
    RESET_PASSWORD(STYLE_KEY_RESET_PASSWORD),
    PAYMENT_OPTIONS_TITLE(STYLE_KEY_PAYMENT_OPTIONS_TITLE),
    PAYMENT_OPTIONS_DESC(STYLE_KEY_PAYMENT_OPTIONS_DESC),
    CONFIRMATION_TITLE(STYLE_KEY_CONFIRMATION_TITLE),
    CONFIRMATION_DESC(STYLE_KEY_CONFIRMATION_DESC),
    CONFIRMATION_BUTTON(STYLE_KEY_CONFIRMATION_BUTTON);
    // @formatter:on

    fun getFontName() = key + KEY_FONT
    fun getTextSizePhone() = key + KEY_SIZE_PHONE
    fun getTextSizeTablet() = key + KEY_SIZE_TABLET
    fun getHexColor() = key + KEY_COLOR
}

const val STYLE_KEY_INPUT_FIELD_LABEL = "input_field_label"
const val STYLE_KEY_ACTION_BUTTON = "action_button"
const val STYLE_KEY_PROMPT = "prompt"
const val STYLE_KEY_LINK = "link"
const val STYLE_KEY_SCREEN_TITLE = "screen_title"
const val STYLE_KEY_SCREEN_DESC = "screen_description"
const val STYLE_KEY_ALT_AUTH_SEPARATOR = "alternative_authentication_separator"
const val STYLE_KEY_ALT_AUTH_PROMPT = "alternative_authentication_prompt"
const val STYLE_KEY_RESET_PASSWORD = "reset_password"
const val STYLE_KEY_PAYMENT_OPTIONS_TITLE = "payment_option_title"
const val STYLE_KEY_PAYMENT_OPTIONS_DESC = "payment_option_description"
const val STYLE_KEY_CONFIRMATION_TITLE = "confirmation_title"
const val STYLE_KEY_CONFIRMATION_DESC = "confirmation_description"
const val STYLE_KEY_CONFIRMATION_BUTTON = "confirmation_button"

const val KEY_FONT = "_font_android"
const val KEY_SIZE_PHONE = "_size_phone"
const val KEY_SIZE_TABLET = "_size_tablet"
const val KEY_COLOR = "_color"