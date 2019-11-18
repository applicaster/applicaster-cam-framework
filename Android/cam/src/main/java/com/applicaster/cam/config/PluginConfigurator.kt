package com.applicaster.cam.config

import com.applicaster.cam.config.flow.AuthenticationRequirement
import com.applicaster.cam.config.ui.*
import com.applicaster.cam.params.auth.AuthFieldConfig
import com.applicaster.cam.params.auth.AuthFieldsConverter
import com.applicaster.cam.params.auth.AuthScreenType

class PluginConfigurator(private val pluginConfig: Map<String, String>) : Configurator {

    override fun getDefaultAuthScreen() =
        AuthScreenType.fromKey(pluginConfig.getValue(KEY_DEFAULT_AUTH_SCREEN))

    /**
     * Check if need to show auth restore UI element on login screen depending on screen configs
     * If there is no "password reset" config then hide corresponding UI, otherwise show it
     */
    override fun isPasswordResetRequired() =
        getPasswordResetAuthFields().authFields.isNotEmpty()

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

    override fun getNotValidEmailInputFieldError() =
        pluginConfig.getValue(KEY_NOT_VALID_EMAIL_INPUT_FIELD_ERROR)

    override fun getDefaultAlertText(): String = pluginConfig.getValue(KEY_DEFAULT_ALERT_TEXT)

    override fun getNoPurchasesToRestoreText(): String = pluginConfig.getValue(
        KEY_NO_PURCHASES_TO_RESTORE_TEXT
    )

    override fun getNonMatchingRestoredPurchasesText(): String =
        pluginConfig.getValue(KEY_NON_MATCHING_RESTORED_PURCHASES_TEXT)

    override fun isAuthRestoreRequired() =
        false

    override fun isShowConfirmationPasswordReset(): Boolean {
        return UI_KEY_PWD_CONFIRMATION_TITLE_TEXT in pluginConfig
                && UI_KEY_PWD_CONFIRMATION_DESC_TEXT in pluginConfig
                && UI_KEY_PWD_CONFIRMATION_BUTTON_TEXT in pluginConfig
    }

    override fun isShowConfirmationPayment(): Boolean {
        return UI_KEY_PAYMENT_CONFIRMATION_TITLE_TEXT in pluginConfig
                && UI_KEY_PAYMENT_CONFIRMATION_DESC_TEXT in pluginConfig
                && UI_KEY_PAYMENT_CONFIRMATION_BUTTON_TEXT in pluginConfig
    }


    override fun isShowConfirmationRestorePurchases(): Boolean {
        return UI_KEY_RESTORE_CONFIRMATION_TITLE_TEXT in pluginConfig
                && UI_KEY_RESTORE_CONFIRMATION_DESC_TEXT in pluginConfig
                && UI_KEY_RESTORE_CONFIRMATION_BUTTON_TEXT in pluginConfig
    }

    override fun getAuthRequirement(): AuthenticationRequirement =
        AuthenticationRequirement.fromKey(getOrDefault(KEY_AUTH_REQUIREMENT))


    override fun isFacebookLoginRequired() : Boolean {
        return getOrEmpty(KEY_OFFER_ALT_AUTH)?.toBoolean() ?: false
    }

    override fun isPaymentRequired(): Boolean {
        return getOrEmpty(KEY_REQUIRE_PAYMENT)?.toBoolean() ?: false
    }

    private fun getOrDefault(key: String) = getOrEmpty(key).orEmpty()

    private fun getOrEmpty(key: String): String? {
        return if (key in pluginConfig)
            pluginConfig[key]
        else
            null
    }

    override fun getPaymentConfirmationTitle(): String =
        pluginConfig.getValue(KEY_PAYMENT_CONFIRMATION_TITLE_TEXT)

    override fun getPaymentConfirmationDescription(): String =
        pluginConfig.getValue(KEY_PAYMENT_CONFIRMATION_DESC_TEXT)

    override fun isTriggerOnAppLaunch(): Boolean =
        pluginConfig.getValue(KEY_TRIGGER_NO_APP_LAUNCH).toBoolean()

    override fun getAlertDialogFields(): AlertFieldsText =
        AlertFieldsText(
            billingConfirmationTitle = pluginConfig.getValue(KEY_BILLING_CONFIRMATION_TITLE),
            billingConfirmationDescription = pluginConfig.getValue(KEY_BILLING_CONFIRMATION_DESC),
            pwdResetTitle = pluginConfig.getValue(KEY_PWD_RESET_TITLE),
            pwdResetDescription = pluginConfig.getValue(KEY_PWD_RESET_DESC),
            restoreConfirmationTitle = pluginConfig.getValue(KEY_RESTORE_CONFIRMATION_TITLE),
            restoreConfirmationDescription = pluginConfig.getValue(KEY_RESTORE_CONFIRMATION_DESC),
            logoutConfirmationTitle = pluginConfig.getValue(KEY_LOGOUT_CONFIRMATION_TITLE),
            logoutConfirmationDescription = pluginConfig.getValue(KEY_LOGOUT_CONFIRMATION_DESC)
        )
}

// Analytics related data class
data class AlertFieldsText(
    var billingConfirmationTitle: String,
    var billingConfirmationDescription: String,
    var pwdResetTitle: String,
    var pwdResetDescription: String,
    var restoreConfirmationTitle: String,
    var restoreConfirmationDescription: String,
    var logoutConfirmationTitle: String,
    var logoutConfirmationDescription: String
)

const val KEY_AUTH_FIELDS = "authentication_input_fields"
const val KEY_DEFAULT_AUTH_SCREEN = "default_authentication_screen"
const val KEY_OFFER_ALT_AUTH = "offer_alternative_authentication"
const val KEY_EMPTY_INPUT_FIELD_ERROR = "required_field_alert_text"
const val KEY_NOT_VALID_EMAIL_INPUT_FIELD_ERROR = "invalid_email_alert_text"
const val KEY_DEFAULT_ALERT_TEXT = "default_alert_text"
const val KEY_NO_PURCHASES_TO_RESTORE_TEXT = "no_purchases_to_restore_alert_text"
const val KEY_NON_MATCHING_RESTORED_PURCHASES_TEXT = "non_matching_restored_purchases_alert_text"
const val KEY_AUTH_REQUIREMENT = "authentication_requirement"
const val KEY_REQUIRE_PAYMENT = "require_payment"
const val KEY_PAYMENT_CONFIRMATION_TITLE_TEXT = "payment_confirmation_title_text"
const val KEY_PAYMENT_CONFIRMATION_DESC_TEXT = "payment_confirmation_description_text"
const val KEY_TRIGGER_NO_APP_LAUNCH = "trigger_on_app_launch"

//Analytics related keys
const val KEY_BILLING_CONFIRMATION_TITLE = "payment_confirmation_title_text"
const val KEY_BILLING_CONFIRMATION_DESC = "payment_confirmation_description_text"
const val KEY_PWD_RESET_TITLE = "password_reset_confirmation_title_text"
const val KEY_PWD_RESET_DESC = "password_reset_confirmation_description_text"
const val KEY_RESTORE_CONFIRMATION_TITLE = "restore_purchase_confirmation_title_text"
const val KEY_RESTORE_CONFIRMATION_DESC = "restore_purchase_confirmation_description_text"
const val KEY_LOGOUT_CONFIRMATION_TITLE = "logout_title_text"
const val KEY_LOGOUT_CONFIRMATION_DESC = "logout_description_text"
