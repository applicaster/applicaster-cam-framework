package com.applicaster.cam.ui.auth.signup

import com.applicaster.cam.ContentAccessManager
import com.applicaster.cam.SignUpCallback
import com.applicaster.cam.params.auth.AuthFieldConfig
import com.applicaster.cam.ui.CamNavigationRouter
import com.applicaster.cam.ui.auth.AuthPresenter

class SignUpPresenter(
    private val view: ISignUpView?,
    private val navigationRouter: CamNavigationRouter
) :
    AuthPresenter(view, navigationRouter), ISignUpPresenter, SignUpCallback {
    override fun onFailure(msg: String) {
        view?.showToastMessage(msg)
    }

    override fun onSuccess() {
        view?.hideLoadingIndicator()
        navigationRouter.attachBillingFragment()
    }

    override fun getAuthFieldConfig(): AuthFieldConfig =
        ContentAccessManager.pluginConfigurator.getSignInAuthFields()

    override fun onAuthActionButtonClicked(inputValues: HashMap<String, String>) {
        if (isAuthInputFieldsValid(inputValues)) return
        view?.showLoadingIndicator()
        ContentAccessManager.contract.signUp(inputValues, this)
    }

    override fun onAuthHintClicked() {
        navigationRouter.attachLoginFragment()
    }
}