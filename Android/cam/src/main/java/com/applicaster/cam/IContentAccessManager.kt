package com.applicaster.cam

import android.content.Context
import com.applicaster.cam.params.billing.BillingOffer

interface IContentAccessManager {
    fun onProcessStarted(contract: ICamContract, context: Context)
}

/**
 * Actions callbacks
 */
interface LoginCallback : ActionCallback
interface SignUpCallback : ActionCallback
interface AccountActivationCallback : ActionCallback
interface PasswordResetCallback : ActionCallback
interface PasswordUpdateCallback : ActionCallback
interface FacebookAuthCallback {
    fun onFacebookAuthFailure(msg: String)
    fun onFacebookAuthSuccess()
}
interface SendActivationCodeCallback {
    fun onCodeSendingFailure(msg: String)
    fun onCodeSendingSuccess()
}
interface ActionCallback {
    fun onFailure(msg: String)
    fun onActionSuccess()
}

interface EntitlementsLoadCallback {
    fun onFailure(msg: String)
    fun onSuccess(billingOffers: List<BillingOffer>)
}

interface RestoreCallback : ActionCallback
interface PurchaseCallback : ActionCallback