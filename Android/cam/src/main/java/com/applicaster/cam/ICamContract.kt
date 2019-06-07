package com.applicaster.cam

interface ICamContract {

    fun login(authFieldsInput: HashMap<String, String>, callback: LoginCallback)

    fun signUp(authFieldsInput: HashMap<String, String>, callback: SignUpCallback)

    fun resetPassword(authFieldsInput: HashMap<String, String>, callback: PasswordResetCallback)

    fun activateRedeemCode(redeemCode: String, callback: RedeemCodeActivationCallback)

    fun loginWithFacebook(email: String, id: String, callback: FacebookAuthCallback)

    fun signupWithFacebook(email: String, id: String, callback: FacebookAuthCallback)

    fun onItemPurchased(/*item*/)

    fun onPurchasesRestored(callback: RestoreCallback)

    fun loadEntitlements(callback: EntitlementsLoadCallback) //get purchase id (and corresponding data)

    fun isUserLogged(): Boolean

    fun isPurchaseRequired(entitlements: List<String>): Boolean

    fun getPluginConfig(): Map<String, String>
}