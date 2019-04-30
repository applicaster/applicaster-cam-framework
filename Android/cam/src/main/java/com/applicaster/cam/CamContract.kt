package com.applicaster.cam

import com.applicaster.cam.params.AuthField

interface CamContract {

    fun login(authFields: List<AuthField>, callback: LoginCallback)

    fun signUp(authFields: List<AuthField>, callback: SignUpCallback)

    fun resetPassword(callback: PasswordResetCallback)

    fun activateRedeemCode(redeemCode: String, callback: RedeemCodeActivationCallback)

    fun loginWithFacebook(callback: FacebookLoginCallback)

    fun onItemPurchased(/*item*/)

    fun onPurchasesRestored(/*items*/)
}