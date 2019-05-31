package com.applicaster.cam

import android.content.Context
import com.applicaster.cam.params.billing.Offer

interface IContentAccessManager {
    fun onProcessStarted(contract: ICamContract, context: Context)
}

/**
 *  Dummy action callbacks
 *  TODO: review during implementation
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
    fun onSuccess(offers: List<Offer>)
}

interface RestoreCallback : EntitlementsLoadCallback
interface PurchaseCallback : ActionCallback