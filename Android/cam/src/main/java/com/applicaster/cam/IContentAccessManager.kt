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
interface SendPasswordActivationCodeCallback : ActivationCodeCallback
interface SendAuthActivationCodeCallback : ActivationCodeCallback
interface FacebookAuthCallback {
    fun onFacebookAuthFailure(msg: String)
    fun onFacebookAuthSuccess()
}

interface ActionCallback {
    fun onFailure(msg: String)
    fun onActionSuccess()
}
interface ActivationCodeCallback {
    fun onCodeSendingFailure(msg: String)
    fun onCodeSendingSuccess()
}

interface EntitlementsLoadCallback {
    fun onFailure(msg: String)
    fun onSuccess(billingOffers: List<BillingOffer>)
}

interface RestoreCallback : ActionCallback
interface PurchaseCallback : ActionCallback