package com.applicaster.cam

interface ICamContract {

    fun login(authFieldsInput: HashMap<String, String>, callback: LoginCallback)

    fun signUp(authFieldsInput: HashMap<String, String>, callback: SignUpCallback)

    fun resetPassword(callback: PasswordResetCallback)

    fun activateRedeemCode(redeemCode: String, callback: RedeemCodeActivationCallback)

    fun loginWithFacebook(callback: FacebookLoginCallback)

    fun onItemPurchased(/*item*/)

    fun onPurchasesRestored(/*items*/)

    fun loadEntitlements(callback: EntitlementsLoadCallback) //get purchase id (and corresponding data)

    fun isUserLogged(): Boolean

    fun getPluginConfig(): Map<String, String>
}