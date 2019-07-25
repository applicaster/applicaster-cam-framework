package com.applicaster.camsample.mock

import android.content.Context
import android.os.Handler
import com.android.billingclient.api.Purchase
import com.applicaster.cam.*

class MockCamContract(private val context: Context) : ICamContract {
    override fun loadEntitlements(callback: EntitlementsLoadCallback) {
        Handler().postDelayed({ callback.onSuccess(arrayListOf()) }, 1250)
    }

    override fun onItemPurchased(purchase: List<Purchase>, callback: PurchaseCallback) {
        Handler().postDelayed({ callback.onSuccess() }, 1250)
    }

    override fun onPurchasesRestored(purchases: List<Purchase>, callback: RestoreCallback) {
        Handler().postDelayed({ callback.onSuccess() }, 1250)
    }

    override fun isPurchaseRequired() = true

    override fun login(authFieldsInput: HashMap<String, String>, callback: LoginCallback) {
        Handler().postDelayed({ callback.onSuccess() }, 1250)
    }

    override fun signUp(authFieldsInput: HashMap<String, String>, callback: SignUpCallback) {
        Handler().postDelayed({ callback.onSuccess() }, 1250)
    }

    override fun resetPassword(authFieldsInput: HashMap<String, String>, callback: PasswordResetCallback) {
        Handler().postDelayed({ callback.onSuccess() }, 1250)
    }

    override fun activateRedeemCode(redeemCode: String, callback: RedeemCodeActivationCallback) {
        Handler().postDelayed({ callback.onSuccess() }, 1250)
    }

    override fun loginWithFacebook(email: String, id: String, callback: FacebookAuthCallback) {
        Handler().postDelayed({ callback.onSuccess() }, 1250)
    }

    override fun signupWithFacebook(email: String, id: String, callback: FacebookAuthCallback) {
        Handler().postDelayed({ callback.onSuccess() }, 1250)
    }

    override fun isUserLogged() = false

    override fun getPluginConfig() = MockPluginConfiguration.getPluginConfiguration(context)

    override fun isRedeemActivated(): Boolean = false

    override fun getCamFlow(): CamFlow = CamFlow.AUTH_AND_STOREFRONT

    override fun onCamFinished() {}
}