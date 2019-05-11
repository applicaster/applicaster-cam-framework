package com.applicaster.cam

import android.content.Context

interface ContentAccessManager {
    fun onProcessStarted(contract: CamContract, configurationProvider: CamConfigurationProvider, context: Context)
}

/**
 *  Dummy action callbacks
 *  TODO: review during implementation
 */
interface LoginCallback : ActionCallback
interface SignUpCallback : ActionCallback
interface PasswordResetCallback : ActionCallback
interface RedeemCodeActivationCallback: ActionCallback
interface FacebookLoginCallback: ActionCallback
interface ActionCallback {
    fun onFailure(msg: String)
    fun onSuccess()
}