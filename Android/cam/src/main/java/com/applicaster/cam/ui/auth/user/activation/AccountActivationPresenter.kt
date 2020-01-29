package com.applicaster.cam.ui.auth.user.activation

import com.applicaster.cam.AccountActivationCallback
import com.applicaster.cam.CamFlow
import com.applicaster.cam.SendAuthActivationCodeCallback
import com.applicaster.cam.ContentAccessManager
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

    override fun onViewCreated() {
        super.onViewCreated()
        view?.showLoadingIndicator()
        view?.customize()
        ContentAccessManager.contract.sendAuthActivationCode(authData, this)
    }

    override fun performAuthAction(input: HashMap<String, String>) {
        input.putAll(authData)
        ContentAccessManager.contract.activateAccount(input, this)
    }

    override fun onResendCodeClicked() {
        view?.showLoadingIndicator()
        ContentAccessManager.contract.sendAuthActivationCode(authData, this)
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