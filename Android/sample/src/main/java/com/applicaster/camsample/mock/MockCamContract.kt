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
        Handler().postDelayed({ callback.onActionSuccess() }, 1250)
    }

    override fun onPurchasesRestored(purchases: List<Purchase>, callback: RestoreCallback) {
        Handler().postDelayed({ callback.onActionSuccess() }, 1250)
    }

    override fun isPurchaseRequired() = true

    override fun login(authFieldsInput: HashMap<String, String>, callback: LoginCallback) {
        Handler().postDelayed({ callback.onActionSuccess() }, 1250)
    }

    override fun logout(isConfirmedByUser: Boolean) {
    }

    override fun signUp(authFieldsInput: HashMap<String, String>, callback: SignUpCallback) {
        Handler().postDelayed({ callback.onActionSuccess() }, 1250)
    }

    override fun sendAuthActivationCode(authFieldsInput: HashMap<String, String>, callback: SendAuthActivationCodeCallback) {
        Handler().postDelayed({ callback.onCodeSendingFailure("Test fail") }, 1250)
    }

    override fun sendPasswordActivationCode(authFieldsInput: HashMap<String, String>, callback: SendPasswordActivationCodeCallback) {
        Handler().postDelayed({ callback.onCodeSendingSuccess() }, 1250)
    }

    override fun updatePassword(authFieldsInput: HashMap<String, String>, callback: PasswordUpdateCallback) {
        Handler().postDelayed({ callback.onActionSuccess() }, 1250)
    }

    override fun activateAccount(authFieldsInput: HashMap<String, String>, callback: AccountActivationCallback) {
        Handler().postDelayed({ callback.onActionSuccess() }, 1250)
    }

    override fun resetPassword(authFieldsInput: HashMap<String, String>, callback: PasswordResetCallback) {
        Handler().postDelayed({ callback.onActionSuccess() }, 1250)
    }

    override fun loginWithFacebook(email: String, id: String, callback: FacebookAuthCallback) {
        Handler().postDelayed({ callback.onFacebookAuthSuccess() }, 1250)
    }

    override fun signupWithFacebook(email: String, id: String, callback: FacebookAuthCallback) {
        Handler().postDelayed({ callback.onFacebookAuthSuccess() }, 1250)
    }

    override fun isUserActivated() = false

    override fun isUserLogged() = false

    override fun getPluginConfig() = MockPluginConfiguration.getPluginConfiguration(context)

    override fun getCamFlow(): CamFlow = CamFlow.AUTH_AND_STOREFRONT

    override fun onCamFinished() {}

    override fun getAnalyticsDataProvider(): IAnalyticsDataProvider {
        return AnalyticsDataProviderMock()
    }
}