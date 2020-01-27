package com.applicaster.cam.ui.auth.user.activation

import com.applicaster.cam.AccountActivationCallback
import com.applicaster.cam.CamFlow
import com.applicaster.cam.SendActivationCodeCallback
import com.applicaster.cam.ContentAccessManager
import com.applicaster.cam.analytics.Action
import com.applicaster.cam.analytics.AnalyticsGatewaySession
import com.applicaster.cam.analytics.AnalyticsUtil
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
    BaseInputPresenter(view), IAccountActivationPresenter, SendActivationCodeCallback,
    AccountActivationCallback {

    override fun onViewCreated() {
        super.onViewCreated()
        view?.showLoadingIndicator()
        view?.customize()
        ContentAccessManager.contract.sendActivationCode(authData, this)
    }

    override fun performAuthAction(input: HashMap<String, String>) {
        input.putAll(authData)
        ContentAccessManager.contract.activateAccount(input, this)
    }

    override fun onResendCodeClicked() {
        view?.showLoadingIndicator()
        ContentAccessManager.contract.sendActivationCode(authData, this)
    }

    override fun onFailure(msg: String) {
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