package com.applicaster.cam.ui.auth.user.activation

import android.util.Log
import com.applicaster.cam.AccountActivationCallback
import com.applicaster.cam.CamFlow
import com.applicaster.cam.SendAuthActivationCodeCallback
import com.applicaster.cam.ContentAccessManager
import com.applicaster.cam.analytics.AnalyticsUtil
import com.applicaster.cam.analytics.CodeResend
import com.applicaster.cam.params.auth.AuthField
import com.applicaster.cam.params.auth.AuthFieldConfig
import com.applicaster.cam.params.auth.AuthScreenType
import com.applicaster.cam.ui.CamNavigationRouter
import com.applicaster.cam.ui.auth.base.BaseInputPresenter

class AccountActivationPresenter(
    private val view: IAccountActivationView?,
    private val authData: HashMap<String, String>,
    private val navigationRouter: CamNavigationRouter
) :
    BaseInputPresenter(view), IAccountActivationPresenter, SendAuthActivationCodeCallback,
    AccountActivationCallback {

    private val TAG = "AccountActivationPresenter"

    override fun onViewCreated() {
        super.onViewCreated()
        view?.showLoadingIndicator()
        view?.customize()
        AnalyticsUtil.logSendAccountActivationCode(CodeResend.NO)
        ContentAccessManager.contract.sendAuthActivationCode(authData, this)
    }

    override fun performAuthAction(input: HashMap<String, String>) {
        input.putAll(authData)
        ContentAccessManager.contract.activateAccount(input, this)
    }

    override fun onAuthActionButtonClicked(inputValues: HashMap<AuthField, String>) {
        AnalyticsUtil.logActivateAccount()
        super.onAuthActionButtonClicked(inputValues)
    }

    override fun onResendCodeClicked() {
        view?.showLoadingIndicator()
        AnalyticsUtil.logSendAccountActivationCode(CodeResend.YES)
        ContentAccessManager.contract.sendAuthActivationCode(authData, this)
    }

    override fun onFailure(msg: String) {
        Log.e(TAG, "onFailure: $msg")
        view?.hideLoadingIndicator()
        view?.showAlert(msg)
    }

    override fun onActionSuccess() {
        view?.hideLoadingIndicator()
        view?.hideKeyboard()

        when (ContentAccessManager.camFlow) {
            CamFlow.AUTH_AND_STOREFRONT, CamFlow.STOREFRONT -> navigationRouter.attachBillingFragment()
            else -> view?.close()
        }
    }

    override fun getAuthFieldConfig(): AuthFieldConfig =
        ContentAccessManager.pluginConfigurator.getAuthFields(AuthScreenType.ACCOUNT_ACTIVATION)

    override fun onCodeSendingFailure(msg: String) {
        onFailure(msg)
    }

    override fun onCodeSendingSuccess() {
        view?.hideLoadingIndicator()
        view?.hideKeyboard()
    }
}