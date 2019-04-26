package com.applicaster.cam

interface ContentAccessManager {
    fun onProcessStarted(contract: CamContract, configurationProvider: CamConfigurationProvider)
}

/**
 *  Dummy action callbacks
 *  TODO: review during implementation
 */
interface LoginCallback : ActionCallback
interface SignUpCallback : ActionCallback
interface PasswordResetCallback : ActionCallback
interface ReedemCodeActivationCallback: ActionCallback
interface FacebookLoginCallback: ActionCallback
interface ActionCallback {
    fun onFailure(msg: String)
    fun onSuccess()
}