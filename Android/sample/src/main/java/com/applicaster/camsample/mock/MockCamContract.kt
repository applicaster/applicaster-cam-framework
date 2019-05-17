package com.applicaster.camsample.mock

import android.content.Context
import android.os.Handler
import com.applicaster.cam.*
import com.applicaster.cam.params.auth.AuthField

class MockCamContract(val context: Context) : ICamContract {

    override fun login(authFields: List<AuthField>, callback: LoginCallback) {
        Handler().postDelayed({ callback.onSuccess() }, 1000)
    }

    override fun signUp(authFields: List<AuthField>, callback: SignUpCallback) {
        Handler().postDelayed({ callback.onSuccess() }, 1000)
    }

    override fun resetPassword(callback: PasswordResetCallback) {
        Handler().postDelayed({ callback.onSuccess() }, 1000)
    }

    override fun activateRedeemCode(redeemCode: String, callback: RedeemCodeActivationCallback) {
        Handler().postDelayed({ callback.onSuccess() }, 1000)
    }

    override fun loginWithFacebook(callback: FacebookLoginCallback) {
        Handler().postDelayed({ callback.onSuccess() }, 1000)
    }

    override fun onItemPurchased() {
        TODO("not implemented") //To change body of created functions use File | Settings | File Templates.
    }

    override fun onPurchasesRestored() {
        TODO("not implemented") //To change body of created functions use File | Settings | File Templates.
    }

    override fun loadEntitlements(callback: EntitlementsLoadCallback) {
        TODO("not implemented") //To change body of created functions use File | Settings | File Templates.
    }

    override fun isUserLogged() = false

    override fun getPluginConfig() = MockPluginConfiguration.getPluginConfiguration(context)
}