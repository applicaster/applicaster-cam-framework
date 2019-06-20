package com.applicaster.cam.ui.auth.user.login

import com.applicaster.cam.ContentAccessManager
import com.applicaster.cam.FacebookAuthCallback
import com.applicaster.cam.LoginCallback
import com.applicaster.cam.params.auth.AuthFieldConfig
import com.applicaster.cam.ui.CamNavigationRouter
import com.applicaster.cam.ui.auth.user.UserAuthPresenter

class LoginPresenter(
    private val view: ILoginView?,
    private val navigationRouter: CamNavigationRouter
) :
    UserAuthPresenter(view), ILoginPresenter, LoginCallback, FacebookAuthCallback {

    override fun getAuthFieldConfig(): AuthFieldConfig =
        ContentAccessManager.pluginConfigurator.getLoginAuthFields()

    override fun onForgotPasswordClicked() {
        navigationRouter.attachPasswordResetFragment()
    }

    override fun performAuthAction(input: HashMap<String, String>) {
        ContentAccessManager.contract.login(input, this)
    }

    override fun onFailure(msg: String) {
        view?.showAlert(msg)
    }

    override fun onSuccess() {
        view?.hideLoadingIndicator()
        if (ContentAccessManager.contract.isPurchaseRequired(emptyList()))
            navigationRouter.attachBillingFragment()
        else
            view?.close()
    }

    override fun onAuthHintClicked() {
        navigationRouter.attachSignUpFragment()
    }

    override fun onFacebookAuthActionCompleted(email: String, id: String) {
        view?.showLoadingIndicator()
        ContentAccessManager.contract.loginWithFacebook(email, id, this)
    }
}