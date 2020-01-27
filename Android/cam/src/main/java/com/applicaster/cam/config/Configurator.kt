package com.applicaster.cam.config

import com.applicaster.cam.config.flow.AuthenticationRequirement
import com.applicaster.cam.params.auth.AuthFieldConfig
import com.applicaster.cam.params.auth.AuthScreenType

interface Configurator {

    fun getAuthFields(type: AuthScreenType): AuthFieldConfig

    fun getDefaultAuthScreen(): AuthScreenType

    fun isAccountActivationRequired(): Boolean

    fun getEmptyInputFieldError(): String

    fun getNotValidEmailInputFieldError(): String

    fun getDefaultAlertText(): String

    fun getLogoutErrorAlertText(): String

    fun getNoPurchasesToRestoreText(): String

    fun getNonMatchingRestoredPurchasesText(): String

    fun isAuthRestoreRequired(): Boolean

    fun isPasswordResetRequired(): Boolean

    fun isPasswordUpdateRequired(): Boolean

    fun isFacebookLoginRequired(): Boolean

    fun isShowConfirmationPasswordReset(): Boolean

    fun isShowConfirmationPayment(): Boolean

    fun isShowConfirmationRestorePurchases(): Boolean

    fun getAuthRequirement(): AuthenticationRequirement

    fun isPaymentRequired(): Boolean

    fun getPaymentConfirmationTitle(): String

    fun getPaymentConfirmationDescription(): String

    fun isTriggerOnAppLaunch(): Boolean

    fun getAlertDialogFields(): AlertFieldsText
}