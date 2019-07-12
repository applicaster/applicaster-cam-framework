package com.applicaster.cam.analytics

import com.applicaster.analytics.AnalyticsAgentUtil
import com.applicaster.cam.ContentAccessManager
import com.applicaster.cam.params.auth.AuthScreenType
import com.applicaster.plugin_manager.Plugin
import com.applicaster.plugin_manager.PluginManager

class AnalyticsUtil {
    companion object {

        private fun getPluginProvider(): String =
            PluginManager.getInstance().getInitiatedPlugin(Plugin.Type.LOGIN)?.plugin?.name.orEmpty()


        private fun getFirstScreen() =
            Properties.TRIGGER.value to when (ContentAccessManager.pluginConfigurator.getDefaultAuthScreen()) {
                AuthScreenType.LOGIN -> "Login"
                AuthScreenType.SIGNUP -> "Sign-Up"
                else -> ""
            }

        fun logTapStandardLoginButton() {
            val params = mapOf(
                Properties.CONTENT_ENTITY_NAME.value to ContentAccessManager.contract.getEntityName(),
                Properties.CONTENT_ENTITY_TYPE.value to ContentAccessManager.contract.getEntityType(),
                Properties.PLUGIN_PROVIDER.value to getPluginProvider()
            )
            AnalyticsAgentUtil.logEvent(AnalyticsEvent.TAP_STANDARD_LOGIN_BUTTON.value, params)
        }

        fun logStandardLoginSuccess() {
            val params = mapOf(
                Properties.CONTENT_ENTITY_NAME.value to ContentAccessManager.contract.getEntityName(),
                Properties.CONTENT_ENTITY_TYPE.value to ContentAccessManager.contract.getEntityType(),
                Properties.PLUGIN_PROVIDER.value to getPluginProvider()
            )
            AnalyticsAgentUtil.logEvent(AnalyticsEvent.STANDARD_LOGIN_SUCCESS.value, params)
        }

        fun logStandardLoginFailure() {
            val params = mapOf(
                Properties.CONTENT_ENTITY_NAME.value to ContentAccessManager.contract.getEntityName(),
                Properties.CONTENT_ENTITY_TYPE.value to ContentAccessManager.contract.getEntityType(),
                Properties.PLUGIN_PROVIDER.value to getPluginProvider()
            )
            AnalyticsAgentUtil.logEvent(AnalyticsEvent.STANDARD_LOGIN_FAILURE.value, params)
        }

        fun logTapAlternativeLogin() {
            val params = mapOf(
                Properties.CONTENT_ENTITY_NAME.value to ContentAccessManager.contract.getEntityName(),
                Properties.CONTENT_ENTITY_TYPE.value to ContentAccessManager.contract.getEntityType(),
                Properties.PLUGIN_PROVIDER.value to getPluginProvider()
            )
            AnalyticsAgentUtil.logEvent(AnalyticsEvent.TAP_ALTERNATIVE_LOGIN.value, params)
        }

        fun logAlternativeLoginSuccess() {
            val params = mapOf(
                Properties.CONTENT_ENTITY_NAME.value to ContentAccessManager.contract.getEntityName(),
                Properties.CONTENT_ENTITY_TYPE.value to ContentAccessManager.contract.getEntityType(),
                Properties.PLUGIN_PROVIDER.value to getPluginProvider()
            )
            AnalyticsAgentUtil.logEvent(AnalyticsEvent.ALTERNATIVE_LOGIN_SUCCESS.value, params)
        }

        fun logAlternativeLoginFailure() {
            val params = mapOf(
                Properties.CONTENT_ENTITY_NAME.value to ContentAccessManager.contract.getEntityName(),
                Properties.CONTENT_ENTITY_TYPE.value to ContentAccessManager.contract.getEntityType(),
                Properties.PLUGIN_PROVIDER.value to getPluginProvider()
            )
            AnalyticsAgentUtil.logEvent(AnalyticsEvent.ALTERNATIVE_LOGIN_FAILURE.value, params)
        }

        fun logTapStandardSignUpButton() {
            val params = mapOf(
                Properties.CONTENT_ENTITY_NAME.value to ContentAccessManager.contract.getEntityName(),
                Properties.CONTENT_ENTITY_TYPE.value to ContentAccessManager.contract.getEntityType(),
                Properties.PLUGIN_PROVIDER.value to getPluginProvider()
            )
            AnalyticsAgentUtil.logEvent(AnalyticsEvent.TAP_STANDARD_SIGNUP_BUTTON.value, params)
        }

        fun logStandardSignUpSuccess() {
            val params = mapOf(
                Properties.CONTENT_ENTITY_NAME.value to ContentAccessManager.contract.getEntityName(),
                Properties.CONTENT_ENTITY_TYPE.value to ContentAccessManager.contract.getEntityType(),
                Properties.PLUGIN_PROVIDER.value to getPluginProvider()
            )
            AnalyticsAgentUtil.logEvent(AnalyticsEvent.STANDARD_SIGNUP_SUCCESS.value, params)
        }

        fun logStandardSignUpFailure() {
            val params = mapOf(
                Properties.CONTENT_ENTITY_NAME.value to ContentAccessManager.contract.getEntityName(),
                Properties.CONTENT_ENTITY_TYPE.value to ContentAccessManager.contract.getEntityType(),
                Properties.PLUGIN_PROVIDER.value to getPluginProvider()
            )
            AnalyticsAgentUtil.logEvent(AnalyticsEvent.STANDARD_SIGNUP_FAILURE.value, params)
        }

        fun logTapAlternativeSignUp() {
            val params = mapOf(
                Properties.CONTENT_ENTITY_NAME.value to ContentAccessManager.contract.getEntityName(),
                Properties.CONTENT_ENTITY_TYPE.value to ContentAccessManager.contract.getEntityType(),
                Properties.PLUGIN_PROVIDER.value to getPluginProvider()
            )
            AnalyticsAgentUtil.logEvent(AnalyticsEvent.TAP_ALTERNATIVE_SIGNUP.value, params)
        }

        fun logAlternativeSignUpSuccess() {
            val params = mapOf(
                Properties.CONTENT_ENTITY_NAME.value to ContentAccessManager.contract.getEntityName(),
                Properties.CONTENT_ENTITY_TYPE.value to ContentAccessManager.contract.getEntityType(),
                Properties.PLUGIN_PROVIDER.value to getPluginProvider()
            )
            AnalyticsAgentUtil.logEvent(AnalyticsEvent.ALTERNATIVE_SIGNUP_SUCCESS.value, params)
        }

        fun logAlternativeSignUpFailure() {
            val params = mapOf(
                Properties.CONTENT_ENTITY_NAME.value to ContentAccessManager.contract.getEntityName(),
                Properties.CONTENT_ENTITY_TYPE.value to ContentAccessManager.contract.getEntityType(),
                Properties.PLUGIN_PROVIDER.value to getPluginProvider()
            )
            AnalyticsAgentUtil.logEvent(AnalyticsEvent.ALTERNATIVE_SIGNUP_FAILURE.value, params)
        }

        fun logLaunchContentGatwayPlugin(trigger: String) {
            val params = mapOf(
                Properties.TRIGGER.value to trigger,
                getFirstScreen(),
                Properties.CONTENT_ENTITY_NAME.value to ContentAccessManager.contract.getEntityName(),
                Properties.CONTENT_ENTITY_TYPE.value to ContentAccessManager.contract.getEntityType(),
                Properties.PLUGIN_PROVIDER.value to getPluginProvider()
            )
            AnalyticsAgentUtil.logEvent(AnalyticsEvent.LAUNCH_CONTENT_GATEWAY_PLUGIN.value, params)
        }

        fun logContentGatewaySession(timedEvent: TimedEvent, trigger: String, action: Action) {
            val params = mapOf(
                Properties.TRIGGER.value to trigger,
                Properties.ACTION.value to action.value,
                Properties.PLUGIN_PROVIDER.value to getPluginProvider()
            )
            if (timedEvent == TimedEvent.START)
                AnalyticsAgentUtil.logTimedEvent(AnalyticsEvent.CONTENT_GATEWAY_SESSION.value, params)
            else
                AnalyticsAgentUtil.endTimedEvent(AnalyticsEvent.CONTENT_GATEWAY_SESSION.value, params)
        }

        fun logSwitchToLoginScreen() {
            AnalyticsAgentUtil.logEvent(
                AnalyticsEvent.SWITCH_TO_LOGIN_SCREEN.value,
                mapOf(Properties.PLUGIN_PROVIDER.value to getPluginProvider())
            )
        }

        fun logSwitchToSignUpScreen() {
            AnalyticsAgentUtil.logEvent(
                AnalyticsEvent.SWITCH_TO_SIGNUP_SCREEN.value,
                mapOf(Properties.PLUGIN_PROVIDER.value to getPluginProvider())
            )
        }

        fun logLaunchPasswordResetScreen() {
            AnalyticsAgentUtil.logEvent(
                AnalyticsEvent.LAUNCH_PASSWORD_RESET_SCREEN.value,
                mapOf(Properties.PLUGIN_PROVIDER.value to getPluginProvider())
            )
        }

        fun logResetPassword() {
            AnalyticsAgentUtil.logEvent(
                AnalyticsEvent.RESET_PASSWORD.value,
                mapOf(Properties.PLUGIN_PROVIDER.value to getPluginProvider())
            )
        }

        fun logViewAlert(confirmationAlertData: ConfirmationAlertData) {
            val confirmationAlert = when (confirmationAlertData.isConfirmationAlert) {
                true -> "true"
                else -> "false"
            }
            val params = mapOf(
                Properties.PLUGIN_PROVIDER.value to getPluginProvider(),
                Properties.CONFIRMATION_ALERT.value to confirmationAlert,
                Properties.CONFIRMATION_CAUSE.value to confirmationAlertData.confirmationCause.value,
                Properties.ALERT_TITLE.value to confirmationAlertData.alertTitle,
                Properties.ALERT_DESCRIPTION.value to confirmationAlertData.alertDescription,
                Properties.API_ERROR_MESSAGE.value to confirmationAlertData.apiErrorMessage
            )
            AnalyticsAgentUtil.logEvent(AnalyticsEvent.VIEW_ALERT.value, params)
        }

        fun logTapPurchaseButton(voucherProperties: VoucherProperties) {}

        fun logStartPurchase(voucherProperties: VoucherProperties) {}

        fun logCompletePurchase(voucherProperties: VoucherProperties) {}

        fun logCancelPurchase(voucherProperties: VoucherProperties) {}

        fun logStorePurchaseError(errorCode: String, errorMessage: String, voucherProperties: VoucherProperties) {}

        fun logTapRestorePurchaseLink() {}

        fun logStartRestorePurchase() {}

        fun logCompleteRestorePurchase() {}

        fun logCancelRestorePurchase() {}

        fun logStoreRestorePurchaseError() {}
     }
}

enum class AnalyticsEvent(val value: String) {
    TAP_STANDARD_LOGIN_BUTTON    ("Tap Standard Login Button"),
    STANDARD_LOGIN_SUCCESS       ("Standard Login Success"),
    STANDARD_LOGIN_FAILURE       ("Standard Login Failure"),
    TAP_ALTERNATIVE_LOGIN        ("Tap Alternative Login"),
    ALTERNATIVE_LOGIN_SUCCESS    ("Alternative Login Success"),
    ALTERNATIVE_LOGIN_FAILURE    ("Alternative Login Failure"),
    TAP_STANDARD_SIGNUP_BUTTON   ("Tap Standard Sign-Up Button"),
    STANDARD_SIGNUP_SUCCESS      ("Standard Sign-Up Success"),
    STANDARD_SIGNUP_FAILURE      ("Standard Sign-Up Failure"),
    TAP_ALTERNATIVE_SIGNUP       ("Tap Alternative Sign-Up"),
    ALTERNATIVE_SIGNUP_SUCCESS   ("Alternative Sign-Up Success"),
    ALTERNATIVE_SIGNUP_FAILURE   ("Alternative Sign-Up Failure"),
    LAUNCH_CONTENT_GATEWAY_PLUGIN("Launch Content Gateway Plugin"),
    CONTENT_GATEWAY_SESSION      ("Content Gateway Session"),
    SWITCH_TO_LOGIN_SCREEN       ("Switch to Login Screen"),
    SWITCH_TO_SIGNUP_SCREEN      ("Switch to Sign-Up Screen"),
    LAUNCH_PASSWORD_RESET_SCREEN ("Launch Password Reset Screen"),
    RESET_PASSWORD               ("Reset Password"),
    VIEW_ALERT                   ("View Alert"),
    TAP_PURCHASE_BUTTON          ("Tap Purchase Button"),
    START_PURCHASE               ("Start Purchase"),
    COMPLETE_PURCHASE            ("Complete Purchase"),
    CANCEL_PURCHASE              ("Cancel Purchase"),
    STORE_PURCHASE_ERROR         ("Store Purchase Error"),
    TAP_RESTORE_PURCHASE_LINK    ("Tap Restore Purchase Link"),
    START_RESTORE_PURCHASE       ("Start Restore Purchase"),
    COMPLETE_RESTORE_PURCHASE    ("Complete Restore Purchase"),
    CANCEL_RESTORE_PURCHASE      ("Cancel Restore Purchase"),
    STORE_RESTORE_PURCHASE_ERROR ("Store Restore Purchase Error")
}

enum class Properties(val value: String) {
    CONTENT_ENTITY_NAME("Content Entity Name"),
    CONTENT_ENTITY_TYPE("Content Entity Type"),
    PLUGIN_PROVIDER    ("Plugin Provider"),
    TRIGGER            ("Trigger"),
    ACTION             ("Action"),
    FIRST_SCREEN       ("First Screen"),
    CONFIRMATION_ALERT ("Confirmation Alert"),
    CONFIRMATION_CAUSE ("Confirmation Cause" ),
    ALERT_TITLE        ("Alert Title"),
    ALERT_DESCRIPTION  ("Alert Description"),
    API_ERROR_MESSAGE  ("API Error Message"),
    VOUCHER_PROPERTIES ("Voucher Properties"),
    ERROR_CODE_ID      ("Error Code ID"),
    ERROR_MESSAGE      ("Error message"),
}

enum class Action(val value: String) {
    PURCHASE              ("Purchase"),
    LOGIN                 ("Login"),
    SIGNUP                ("Sign Up"),
    SIGNUP_AND_PURCHASE   ("Sign Up & Purchase"),
    RESTORE_PURCHASE      ("Restore Purchase"),
    CANCEL                ("Cancel"),
    FAILED_ATTEMPT        ("Failed Attempt"),
    SEND_APP_TO_BACKGROUND("Send App To Background")
}

enum class ConfirmationCause(val value: String) {
    PURCHASE        ("Purchase"),
    RESTORE_PURCHASE("Restore Purchase"),
    PASSWORD_RESET  ("Password Reset")
}

enum class PurchaseType(val value: String) {
    SUBSCRIPTION("Subscription"),
    CONSUMABLE  ("Consumable"),
    UNSPECIFIED ("Unspecified")
}

enum class TimedEvent {
    START, END
}

data class ConfirmationAlertData(
    val isConfirmationAlert: Boolean,
    val confirmationCause: ConfirmationCause,
    val alertTitle: String,
    val alertDescription: String,
    val apiErrorMessage: String
)

data class VoucherProperties(
    val isUserSubscribed: Boolean,
    val voucherName: String,
    val price: String,
    val transactionId: String,
    val productId: String,
    val purchaseType: PurchaseType,
    val subscriptionDuration: String,
    val trialPeriod: String,
    val purchaseEntityType: String,
    val gracePeriod: String
)

