package com.applicaster.cam.analytics

import com.applicaster.analytics.AnalyticsAgentUtil
import com.applicaster.cam.ContentAccessManager
import com.applicaster.cam.params.auth.AuthScreenType
import com.applicaster.plugin_manager.Plugin
import com.applicaster.plugin_manager.PluginManager
import org.json.JSONObject

class AnalyticsUtil {
    companion object {

        const val KEY_YES = "Yes"
        const val KEY_NO = "No"
        const val KEY_NON_PROVIDED = "Non provided"

        private fun getPluginProvider(): String =
            PluginManager.getInstance().getInitiatedPlugin(Plugin.Type.LOGIN)?.plugin?.name.orEmpty()


        private fun getFirstScreen() =
            Properties.TRIGGER.value to when (ContentAccessManager.pluginConfigurator.getDefaultAuthScreen()) {
                AuthScreenType.LOGIN -> AuthScreenType.LOGIN.getKey()
                AuthScreenType.SIGNUP -> AuthScreenType.SIGNUP.getKey()
                else -> KEY_NON_PROVIDED
            }

        private fun matchIsUserSubscribed(isUserSubscribed: Boolean): String =
            when (isUserSubscribed) {
                true -> KEY_YES
                else -> KEY_NO
            }

        private fun getContentEntityName() =
            ContentAccessManager.contract.getAnalyticsDataProvider().entityName

        private fun getContentEntityType() =
            ContentAccessManager.contract.getAnalyticsDataProvider().entityName

        private fun generateProductPropertiesMap(productPropertiesData: PurchaseProductPropertiesData) =
            mapOf(
                Properties.SUBSCRIBER.value to matchIsUserSubscribed(productPropertiesData.isUserSubscribed),
                Properties.PRODUCT_NAME.value to productPropertiesData.productName,
                Properties.PRICE.value to productPropertiesData.price,
                Properties.TRANSACTION_ID.value to productPropertiesData.transactionId,
                Properties.PRODUCT_ID.value to productPropertiesData.productId,
                Properties.SUBSCRIPTION_DURATION.value to productPropertiesData.subscriptionDuration,
                Properties.PURCHASE_TYPE.value to productPropertiesData.purchaseType.value,
                Properties.TRIAL_PERIOD.value to productPropertiesData.trialPeriod,
                Properties.PURCHASE_ENTITY_TYPE.value to productPropertiesData.purchaseEntityType
            )

        // Analytics logger functions
        fun logTapStandardLoginButton() {
            val params = mapOf(
                Properties.CONTENT_ENTITY_NAME.value to getContentEntityName(),
                Properties.CONTENT_ENTITY_TYPE.value to getContentEntityType(),
                Properties.PLUGIN_PROVIDER.value to getPluginProvider()
            )
            AnalyticsAgentUtil.logEvent(AnalyticsEvent.TAP_STANDARD_LOGIN_BUTTON.value, params)
        }

        fun logStandardLoginSuccess() {
            val params = mapOf(
                Properties.CONTENT_ENTITY_NAME.value to getContentEntityName(),
                Properties.CONTENT_ENTITY_TYPE.value to getContentEntityType(),
                Properties.PLUGIN_PROVIDER.value to getPluginProvider()
            )
            AnalyticsAgentUtil.logEvent(AnalyticsEvent.STANDARD_LOGIN_SUCCESS.value, params)
        }

        fun logStandardLoginFailure() {
            val params = mapOf(
                Properties.CONTENT_ENTITY_NAME.value to getContentEntityName(),
                Properties.CONTENT_ENTITY_TYPE.value to getContentEntityType(),
                Properties.PLUGIN_PROVIDER.value to getPluginProvider()
            )
            AnalyticsAgentUtil.logEvent(AnalyticsEvent.STANDARD_LOGIN_FAILURE.value, params)
        }

        fun logTapAlternativeLogin() {
            val params = mapOf(
                Properties.CONTENT_ENTITY_NAME.value to getContentEntityName(),
                Properties.CONTENT_ENTITY_TYPE.value to getContentEntityType(),
                Properties.PLUGIN_PROVIDER.value to getPluginProvider()
            )
            AnalyticsAgentUtil.logEvent(AnalyticsEvent.TAP_ALTERNATIVE_LOGIN.value, params)
        }

        fun logAlternativeLoginSuccess() {
            val params = mapOf(
                Properties.CONTENT_ENTITY_NAME.value to getContentEntityName(),
                Properties.CONTENT_ENTITY_TYPE.value to getContentEntityType(),
                Properties.PLUGIN_PROVIDER.value to getPluginProvider()
            )
            AnalyticsAgentUtil.logEvent(AnalyticsEvent.ALTERNATIVE_LOGIN_SUCCESS.value, params)
        }

        fun logAlternativeLoginFailure() {
            val params = mapOf(
                Properties.CONTENT_ENTITY_NAME.value to getContentEntityName(),
                Properties.CONTENT_ENTITY_TYPE.value to getContentEntityType(),
                Properties.PLUGIN_PROVIDER.value to getPluginProvider()
            )
            AnalyticsAgentUtil.logEvent(AnalyticsEvent.ALTERNATIVE_LOGIN_FAILURE.value, params)
        }

        fun logTapStandardSignUpButton() {
            val params = mapOf(
                Properties.CONTENT_ENTITY_NAME.value to getContentEntityName(),
                Properties.CONTENT_ENTITY_TYPE.value to getContentEntityType(),
                Properties.PLUGIN_PROVIDER.value to getPluginProvider()
            )
            AnalyticsAgentUtil.logEvent(AnalyticsEvent.TAP_STANDARD_SIGNUP_BUTTON.value, params)
        }

        fun logStandardSignUpSuccess() {
            val params = mapOf(
                Properties.CONTENT_ENTITY_NAME.value to getContentEntityName(),
                Properties.CONTENT_ENTITY_TYPE.value to getContentEntityType(),
                Properties.PLUGIN_PROVIDER.value to getPluginProvider()
            )
            AnalyticsAgentUtil.logEvent(AnalyticsEvent.STANDARD_SIGNUP_SUCCESS.value, params)
        }

        fun logStandardSignUpFailure() {
            val params = mapOf(
                Properties.CONTENT_ENTITY_NAME.value to getContentEntityName(),
                Properties.CONTENT_ENTITY_TYPE.value to getContentEntityType(),
                Properties.PLUGIN_PROVIDER.value to getPluginProvider()
            )
            AnalyticsAgentUtil.logEvent(AnalyticsEvent.STANDARD_SIGNUP_FAILURE.value, params)
        }

        fun logTapAlternativeSignUp() {
            val params = mapOf(
                Properties.CONTENT_ENTITY_NAME.value to getContentEntityName(),
                Properties.CONTENT_ENTITY_TYPE.value to getContentEntityType(),
                Properties.PLUGIN_PROVIDER.value to getPluginProvider()
            )
            AnalyticsAgentUtil.logEvent(AnalyticsEvent.TAP_ALTERNATIVE_SIGNUP.value, params)
        }

        fun logAlternativeSignUpSuccess() {
            val params = mapOf(
                Properties.CONTENT_ENTITY_NAME.value to getContentEntityName(),
                Properties.CONTENT_ENTITY_TYPE.value to getContentEntityType(),
                Properties.PLUGIN_PROVIDER.value to getPluginProvider()
            )
            AnalyticsAgentUtil.logEvent(AnalyticsEvent.ALTERNATIVE_SIGNUP_SUCCESS.value, params)
        }

        fun logAlternativeSignUpFailure() {
            val params = mapOf(
                Properties.CONTENT_ENTITY_NAME.value to getContentEntityName(),
                Properties.CONTENT_ENTITY_TYPE.value to getContentEntityType(),
                Properties.PLUGIN_PROVIDER.value to getPluginProvider()
            )
            AnalyticsAgentUtil.logEvent(AnalyticsEvent.ALTERNATIVE_SIGNUP_FAILURE.value, params)
        }

        fun logLaunchContentGatwayPlugin(trigger: String) {
            val params = mapOf(
                Properties.TRIGGER.value to trigger,
                getFirstScreen(),
                Properties.CONTENT_ENTITY_NAME.value to getContentEntityName(),
                Properties.CONTENT_ENTITY_TYPE.value to getContentEntityType(),
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
                AnalyticsAgentUtil.logTimedEvent(
                    AnalyticsEvent.CONTENT_GATEWAY_SESSION.value,
                    params
                )
            else
                AnalyticsAgentUtil.endTimedEvent(
                    AnalyticsEvent.CONTENT_GATEWAY_SESSION.value,
                    params
                )
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
                true -> KEY_YES
                else -> KEY_NO
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

        fun logTapPurchaseButton(purchaseProductPropertiesData: PurchaseProductPropertiesData?) {
            purchaseProductPropertiesData?.let {
                val params = mapOf(
                    Properties.PLUGIN_PROVIDER.value to getPluginProvider(),
                    Properties.CONTENT_ENTITY_NAME.value to getContentEntityName(),
                    Properties.CONTENT_ENTITY_TYPE.value to getContentEntityType()
                ) + generateProductPropertiesMap(it)
                AnalyticsAgentUtil.logEvent(AnalyticsEvent.TAP_PURCHASE_BUTTON.value, params)
            }
        }

        fun logCompletePurchase(purchaseProductPropertiesData: PurchaseProductPropertiesData) {
            val params = mapOf(
                Properties.PLUGIN_PROVIDER.value to getPluginProvider(),
                Properties.CONTENT_ENTITY_NAME.value to getContentEntityName(),
                Properties.CONTENT_ENTITY_TYPE.value to getContentEntityType()
            ) + generateProductPropertiesMap(purchaseProductPropertiesData)
            AnalyticsAgentUtil.logEvent(AnalyticsEvent.COMPLETE_PURCHASE.value, params)
        }

        fun logCancelPurchase(purchaseProductPropertiesData: PurchaseProductPropertiesData) {
            val params = mapOf(
                Properties.PLUGIN_PROVIDER.value to getPluginProvider(),
                Properties.CONTENT_ENTITY_NAME.value to getContentEntityName(),
                Properties.CONTENT_ENTITY_TYPE.value to getContentEntityType()
            ) + generateProductPropertiesMap(purchaseProductPropertiesData)
            AnalyticsAgentUtil.logEvent(AnalyticsEvent.CANCEL_PURCHASE.value, params)
        }

        fun logStorePurchaseError(
            errorCode: String,
            errorMessage: String,
            purchaseProductPropertiesData: PurchaseProductPropertiesData
        ) {
            val params = mapOf(
                Properties.ERROR_CODE_ID.value to errorCode,
                Properties.ERROR_MESSAGE.value to errorMessage,
                Properties.PLUGIN_PROVIDER.value to getPluginProvider(),
                Properties.CONTENT_ENTITY_NAME.value to getContentEntityName(),
                Properties.CONTENT_ENTITY_TYPE.value to getContentEntityType()
            ) + generateProductPropertiesMap(purchaseProductPropertiesData)
            AnalyticsAgentUtil.logEvent(AnalyticsEvent.STORE_PURCHASE_ERROR.value, params)
        }

        fun logTapRestorePurchaseLink() {
            val params = mapOf(
                Properties.CONTENT_ENTITY_NAME.value to getContentEntityName(),
                Properties.CONTENT_ENTITY_TYPE.value to getContentEntityType(),
                Properties.PLUGIN_PROVIDER.value to getPluginProvider()
            )
            AnalyticsAgentUtil.logEvent(AnalyticsEvent.TAP_RESTORE_PURCHASE_LINK.value, params)
        }

        fun logCompleteRestorePurchase(purchaseProductPropertiesData: PurchaseProductPropertiesData) {
            val params = mapOf(
                Properties.PLUGIN_PROVIDER.value to getPluginProvider(),
                Properties.CONTENT_ENTITY_NAME.value to getContentEntityName(),
                Properties.CONTENT_ENTITY_TYPE.value to getContentEntityType()
            ) + generateProductPropertiesMap(purchaseProductPropertiesData)
            AnalyticsAgentUtil.logEvent(AnalyticsEvent.COMPLETE_RESTORE_PURCHASE.value, params)
        }

        fun logStoreRestorePurchaseError(
            errorMessage: String,
            purchaseProductPropertiesData: PurchaseProductPropertiesData
        ) {
            val params = mapOf(
                Properties.ERROR_MESSAGE.value to errorMessage,
                Properties.PLUGIN_PROVIDER.value to getPluginProvider(),
                Properties.CONTENT_ENTITY_NAME.value to getContentEntityName(),
                Properties.CONTENT_ENTITY_TYPE.value to getContentEntityType()
            ) + generateProductPropertiesMap(purchaseProductPropertiesData)
            AnalyticsAgentUtil.logEvent(AnalyticsEvent.STORE_RESTORE_PURCHASE_ERROR.value, params)
        }


        // user analytics
        fun logUserProperties(purchaseProductPropertiesData: List<PurchaseProductPropertiesData>) {
            val pluginProvider: String = PluginManager.getInstance().getInitiatedPlugin(Plugin.Type.LOGIN)?.plugin?.name.orEmpty()
            val isUserLoggedIn = ContentAccessManager.contract.isUserLogged()
            val productNames = arrayListOf<String>()
            var isUserSubscribed: Boolean = false
            purchaseProductPropertiesData.forEach {
                isUserSubscribed = it.isUserSubscribed
                productNames.add(it.productName)
            }
            val productName: String = productNames.joinToString(separator = "; ")
            val userProps = JSONObject()
            userProps.put(UserProperties.LOGGED_IN.value, isUserLoggedIn)
            userProps.put(UserProperties.AUTH_PROVIDER.value, pluginProvider)
            userProps.put(UserProperties.PURCHASE_PRODUCT_NAME.value, productName)
            userProps.put(UserProperties.SUBSCRIBER.value, isUserSubscribed)
            AnalyticsAgentUtil.sendUserProperties(userProps)
        }
    }
}

enum class AnalyticsEvent(val value: String) {
    // @formatter:off
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
    COMPLETE_PURCHASE            ("Complete Purchase"),
    CANCEL_PURCHASE              ("Cancel Purchase"),
    STORE_PURCHASE_ERROR         ("Store Purchase Error"),
    TAP_RESTORE_PURCHASE_LINK    ("Tap Restore Purchase Link"),
    COMPLETE_RESTORE_PURCHASE    ("Complete Restore Purchase"),
    STORE_RESTORE_PURCHASE_ERROR ("Store Restore Purchase Error")
    // @formatter:on
}

enum class Properties(val value: String) {
    // @formatter:off
    //General properties
    CONTENT_ENTITY_NAME  ("Content Entity Name"),
    CONTENT_ENTITY_TYPE  ("Content Entity Type"),
    PLUGIN_PROVIDER      ("Plugin Provider"),
    TRIGGER              ("Trigger"),
    ACTION               ("Action"),
    FIRST_SCREEN         ("First Screen"),
    CONFIRMATION_ALERT   ("Confirmation Alert"),
    CONFIRMATION_CAUSE   ("Confirmation Cause" ),
    ALERT_TITLE          ("Alert Title"),
    ALERT_DESCRIPTION    ("Alert Description"),
    API_ERROR_MESSAGE    ("API Error Message"),
    ERROR_CODE_ID        ("Error Code ID"),
    ERROR_MESSAGE        ("Error message"),
    //Purchase product properties
    SUBSCRIBER           ("Subscriber"),
    PRODUCT_NAME         ("Product Name"),
    PRICE                ("Price"),
    TRANSACTION_ID       ("Transaction ID"),
    PRODUCT_ID           ("Product ID"),
    SUBSCRIPTION_DURATION("Subscription Duration"),
    PURCHASE_TYPE        ("Purchase Type"),
    TRIAL_PERIOD         ("Trial Period"),
    PURCHASE_ENTITY_TYPE ("Purchase Entity Type")
    // @formatter:on
}

enum class Action(val value: String) {
    // @formatter:off
    PURCHASE              ("Purchase"),
    LOGIN                 ("Login"),
    SIGNUP                ("Sign Up"),
    SIGNUP_AND_PURCHASE   ("Sign Up & Purchase"),
    RESTORE_PURCHASE      ("Restore Purchase"),
    CANCEL                ("Cancel"),
    FAILED_ATTEMPT        ("Failed Attempt"),
    SEND_APP_TO_BACKGROUND("Send App To Background")
    // @formatter:on
}

enum class ConfirmationCause(val value: String) {
    // @formatter:off
    PURCHASE        ("Purchase"),
    RESTORE_PURCHASE("Restore Purchase"),
    PASSWORD_RESET  ("Password Reset"),
    NONE            ("None Provided")
    // @formatter:on
}

enum class PurchaseType(val value: String) {
    // @formatter:off
    SUBSCRIPTION("Subscription"),
    CONSUMABLE  ("Consumable"),
    UNSPECIFIED ("Unspecified")
    // @formatter:on
}

enum class TimedEvent {
    START, END
}

enum class UserProperties(val value: String) {
    LOGGED_IN("Logged In"),
    AUTH_PROVIDER("Authentication Provider"),
    SUBSCRIBER("Subscriber"),
    PURCHASE_PRODUCT_NAME("Purchase Product Name")
}

data class ConfirmationAlertData(
    val isConfirmationAlert: Boolean,
    val confirmationCause: ConfirmationCause,
    val alertTitle: String,
    val alertDescription: String,
    val apiErrorMessage: String
)

data class PurchaseProductPropertiesData(
    val isUserSubscribed: Boolean,
    val productName: String,
    val price: String,
    val transactionId: String,
    val productId: String,
    val purchaseType: PurchaseType,
    val subscriptionDuration: String,
    val trialPeriod: String,
    val purchaseEntityType: String
)

