package com.applicaster.cam.config

import com.applicaster.cam.config.ui.*
import com.applicaster.cam.params.auth.AuthFieldConfig
import com.applicaster.cam.params.auth.AuthFieldsConverter
import com.applicaster.cam.params.auth.AuthScreenType

class PluginConfigurator(private val pluginConfig: Map<String, String>) : Configurator {

    private val confirmationKeysAmount = 3

    override fun getDefaultAuthScreen() =
        AuthScreenType.fromKey(pluginConfig.getValue(KEY_DEFAULT_AUTH_SCREEN))

    override fun isFacebookLoginRequired() =
        pluginConfig.getValue(KEY_FACEBOOK_LOGIN_REQ).toBoolean()

    /**
     * Check if need to show auth restore UI element on login screen depending on screen configs
     * If there is no "password reset" config then hide corresponding UI, otherwise show it
     */
    override fun isPasswordResetRequired() =
        !getPasswordResetAuthFields().authFields.isNullOrEmpty()

    override fun getSignInAuthFields(): AuthFieldConfig {
        val jsonConfig = pluginConfig.getValue(KEY_AUTH_FIELDS)
        return AuthFieldsConverter.getFromJsonString(jsonConfig, AuthScreenType.SIGNUP)
    }

    override fun getLoginAuthFields(): AuthFieldConfig {
        val jsonConfig = pluginConfig.getValue(KEY_AUTH_FIELDS)
        return AuthFieldsConverter.getFromJsonString(jsonConfig, AuthScreenType.LOGIN)
    }

    override fun getPasswordResetAuthFields(): AuthFieldConfig {
        val jsonConfig = pluginConfig.getValue(KEY_AUTH_FIELDS)
        return AuthFieldsConverter.getFromJsonString(jsonConfig, AuthScreenType.PASSWORD_RESET)
    }

    override fun getEmptyInputFieldError() = pluginConfig.getValue(KEY_EMPTY_INPUT_FIELD_ERROR)

    override fun getNotValidEmailInputFieldError() = pluginConfig.getValue(KEY_NOT_VALID_EMAIL_INPUT_FIELD_ERROR)

    override fun isAuthRestoreRequired() =
        false

    override fun isShowConfirmationPasswordReset(): Boolean {
        return pluginConfig.filterKeys { key: String ->
            key == UI_KEY_PWD_CONFIRMATION_TITLE_TEXT
                    || key == UI_KEY_PWD_CONFIRMATION_DESC_TEXT
                    || key == UI_KEY_PWD_CONFIRMATION_BUTTON_TEXT
        }.size == confirmationKeysAmount
    }

    override fun isShowConfirmationPayment(): Boolean {
        return pluginConfig.filterKeys { key: String ->
            key == UI_KEY_PAYMENT_CONFIRMATION_TITLE_TEXT
                    || key == UI_KEY_PAYMENT_CONFIRMATION_DESC_TEXT
                    || key == UI_KEY_PAYMENT_CONFIRMATION_BUTTON_TEXT
        }.size == confirmationKeysAmount
    }

    override fun isShowConfirmationRestorePurchases(): Boolean {
        return pluginConfig.filterKeys { key: String ->
            key == UI_KEY_RESTORE_CONFIRMATION_TITLE_TEXT
                    || key == UI_KEY_RESTORE_CONFIRMATION_DESC_TEXT
                    || key == UI_KEY_RESTORE_CONFIRMATION_BUTTON_TEXT
        }.size == confirmationKeysAmount
    }
}

const val KEY_AUTH_FIELDS = "authentication_input_fields"
const val KEY_DEFAULT_AUTH_SCREEN = "default_login_screen"
const val KEY_FACEBOOK_LOGIN_REQ = "facebook_login_required"
const val KEY_EMPTY_INPUT_FIELD_ERROR = "required_field_alert_text"
const val KEY_NOT_VALID_EMAIL_INPUT_FIELD_ERROR = "invalid_email_alert_text"