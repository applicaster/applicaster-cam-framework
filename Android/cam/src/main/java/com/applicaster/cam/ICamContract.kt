package com.applicaster.cam

import com.android.billingclient.api.Purchase

interface ICamContract {

    fun login(authFieldsInput: HashMap<String, String>, callback: LoginCallback)

    fun logout(isConfirmedByUser: Boolean)

    fun signUp(authFieldsInput: HashMap<String, String>, callback: SignUpCallback)

    fun resetPassword(authFieldsInput: HashMap<String, String>, callback: PasswordResetCallback)

    fun loginWithFacebook(email: String, id: String, callback: FacebookAuthCallback)

    fun signupWithFacebook(email: String, id: String, callback: FacebookAuthCallback)

    fun onItemPurchased(purchase: List<Purchase>, callback: PurchaseCallback)

    fun onPurchasesRestored(purchases: List<Purchase>, callback: RestoreCallback)

    fun loadEntitlements(callback: EntitlementsLoadCallback) //get purchase id (and corresponding data)

    fun isUserLogged(): Boolean

    fun isPurchaseRequired(): Boolean

    fun getPluginConfig(): Map<String, String>

    fun getCamFlow(): CamFlow

    fun onCamFinished()

    //========= Analytics ============//

    fun getAnalyticsDataProvider(): IAnalyticsDataProvider
}