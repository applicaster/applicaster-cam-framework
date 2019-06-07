package com.applicaster.camsample.mock

import android.content.Context
import android.os.Handler
import com.applicaster.cam.*
import com.applicaster.cam.params.billing.Offer
import com.applicaster.cam.params.billing.ProductType

class MockCamContract(private val context: Context) : ICamContract {

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

    override fun onItemPurchased() {
        TODO("not implemented") //To change body of created functions use File | Settings | File Templates.
    }

    override fun onPurchasesRestored(callback: RestoreCallback) {
        Handler().postDelayed({ callback.onSuccess(arrayListOf()) }, 1250)
    }

    override fun loadEntitlements(callback: EntitlementsLoadCallback) {
        val offer = Offer(
            "Test product id",
            ProductType.INAPP
        )
        callback.onSuccess(arrayListOf(offer, offer, offer))
    }

    override fun isUserLogged() = false

    override fun isPurchaseRequired(entitlements: List<String>) = false

    override fun getPluginConfig() = MockPluginConfiguration.getPluginConfiguration(context)
}