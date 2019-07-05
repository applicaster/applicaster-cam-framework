package com.applicaster.cam.ui.auth.user.login

import com.applicaster.cam.CamFlow
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
        view?.hideLoadingIndicator()
        view?.showAlert(msg)
    }

    override fun onSuccess() {
        view?.hideLoadingIndicator()
        if (ContentAccessManager.contract.isPurchaseRequired()) {
            when (ContentAccessManager.contract.getCamFlow()) {
                CamFlow.AUTH_AND_STOREFRONT -> navigationRouter.attachBillingFragment()
                CamFlow.STOREFRONT -> navigationRouter.attachBillingFragment()
                else -> view?.close()
            }
        } else {
            view?.close()
        }
    }

    override fun onAuthHintClicked() {
        navigationRouter.attachSignUpFragment()
    }

    override fun onFacebookAuthActionCompleted(email: String, id: String) {
        view?.showLoadingIndicator()
        ContentAccessManager.contract.loginWithFacebook(email, id, this)
    }
}