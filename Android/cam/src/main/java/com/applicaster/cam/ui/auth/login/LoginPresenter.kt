package com.applicaster.cam.ui.auth.login

import com.applicaster.cam.ContentAccessManager
import com.applicaster.cam.params.auth.AuthFieldConfig
import com.applicaster.cam.ui.CamNavigationRouter
import com.applicaster.cam.ui.auth.AuthPresenter

class LoginPresenter(
    private val view: ILoginView?,
    private val navigationRouter: CamNavigationRouter
) :
    AuthPresenter(view, navigationRouter), ILoginPresenter {

    override fun getAuthFieldConfig(): AuthFieldConfig =
        ContentAccessManager.pluginConfigurator.getLoginAuthFields()

    override fun onForgotPasswordClicked() {
        view?.showToastMessage("forgot pwd action")
    }

    override fun onAuthActionButtonClicked() {
        view?.showToastMessage("login action")
        //TODO: added for test implementation and should be removed after
        navigationRouter.attachBillingFragment()
    }

    override fun onAuthHintClicked() {
        navigationRouter.attachSignUpFragment()
    }
}