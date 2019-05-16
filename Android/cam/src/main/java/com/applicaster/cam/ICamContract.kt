package com.applicaster.cam

import com.applicaster.cam.params.auth.AuthField

interface ICamContract {

    fun login(authFields: List<AuthField>, callback: LoginCallback)

    fun signUp(authFields: List<AuthField>, callback: SignUpCallback)

    fun resetPassword(callback: PasswordResetCallback)

    fun activateRedeemCode(redeemCode: String, callback: RedeemCodeActivationCallback)

    fun loginWithFacebook(callback: FacebookLoginCallback)

    fun onItemPurchased(/*item*/)

    fun onPurchasesRestored(/*items*/)

    fun loadEntitlements(callback: EntitlementsLoadCallback) //get purchase id (and corresponding data)

    fun isUserLogged(): Boolean

    fun getPluginConfig(): Map<String, String>
}