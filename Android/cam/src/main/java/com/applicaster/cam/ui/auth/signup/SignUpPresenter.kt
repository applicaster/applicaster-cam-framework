package com.applicaster.cam.ui.auth.signup

import com.applicaster.cam.ContentAccessManager
import com.applicaster.cam.params.auth.AuthFieldConfig
import com.applicaster.cam.ui.CamNavigationRouter
import com.applicaster.cam.ui.auth.AuthPresenter

class SignUpPresenter(
    private val view: ISignUpView?,
    private val navigationRouter: CamNavigationRouter
) :
    AuthPresenter(view, navigationRouter), ISignUpPresenter {

    override fun getAuthFieldConfig(): AuthFieldConfig =
        ContentAccessManager.pluginConfigurator.getSignInAuthFields()

    override fun onAuthActionButtonClicked() {
        view?.showToastMessage("sign up action")
    }

    override fun onAuthHintClicked() {
        navigationRouter.attachLoginFragment()
    }
}