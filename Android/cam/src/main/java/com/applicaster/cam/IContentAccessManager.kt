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
interface PasswordResetCallback : ActionCallback
interface RedeemCodeActivationCallback: ActionCallback
interface FacebookAuthCallback: ActionCallback
interface ActionCallback {
    fun onFailure(msg: String)
    fun onSuccess()
}

interface EntitlementsLoadCallback {
    fun onFailure(msg: String)
    fun onSuccess(billingOffers: List<BillingOffer>)
}

interface RestoreCallback : ActionCallback {
    fun onNoPurchasesRestored()
    fun onNonMatchingPurchasesRestored()
    override fun onFailure(msg: String) = Unit
}
interface PurchaseCallback : ActionCallback