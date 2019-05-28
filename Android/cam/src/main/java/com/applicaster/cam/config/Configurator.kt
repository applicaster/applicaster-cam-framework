package com.applicaster.cam.config

import com.applicaster.cam.params.auth.AuthFieldConfig
import com.applicaster.cam.params.auth.AuthScreenType

interface Configurator {

    fun getSignInAuthFields(): AuthFieldConfig

    fun getLoginAuthFields(): AuthFieldConfig

    fun getPasswordResetAuthFields(): AuthFieldConfig

    fun getDefaultAuthScreen(): AuthScreenType

    fun isAuthRestoreRequired(): Boolean

    fun isPasswordResetRequired(): Boolean

    fun isFacebookLoginRequired(): Boolean

    fun isShowConfirmationPasswordReset(): Boolean

    fun isShowConfirmationPayment(): Boolean

    fun isShowConfiramtionRestorePurchases(): Boolean
}