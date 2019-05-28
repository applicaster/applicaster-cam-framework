package com.applicaster.cam.ui.auth.login

import com.applicaster.cam.ContentAccessManager
import com.applicaster.cam.LoginCallback
import com.applicaster.cam.params.auth.AuthFieldConfig
import com.applicaster.cam.ui.CamNavigationRouter
import com.applicaster.cam.ui.auth.AuthPresenter

class LoginPresenter(
    private val view: ILoginView?,
    private val navigationRouter: CamNavigationRouter
) :
    AuthPresenter(view, navigationRouter), ILoginPresenter, LoginCallback {

    override fun getAuthFieldConfig(): AuthFieldConfig =
        ContentAccessManager.pluginConfigurator.getLoginAuthFields()

    override fun onForgotPasswordClicked() {
        navigationRouter.attachPasswordResetFragment()
    }

    override fun onAuthActionButtonClicked(inputValues: HashMap<String, String>) {
        if (isAuthInputFieldsValid(inputValues)) return
        view?.showLoadingIndicator()
        ContentAccessManager.contract.login(inputValues, this)
    }

    override fun onFailure(msg: String) {
        view?.showToastMessage(msg)
    }

    override fun onSuccess() {
        view?.hideLoadingIndicator()
        navigationRouter.attachBillingFragment()
    }

    override fun onAuthHintClicked() {
        navigationRouter.attachSignUpFragment()
    }
}