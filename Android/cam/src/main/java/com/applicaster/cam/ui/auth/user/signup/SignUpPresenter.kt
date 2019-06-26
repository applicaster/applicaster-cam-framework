package com.applicaster.cam.ui.auth.user.signup

import com.applicaster.cam.CamFlow
import com.applicaster.cam.ContentAccessManager
import com.applicaster.cam.FacebookAuthCallback
import com.applicaster.cam.SignUpCallback
import com.applicaster.cam.params.auth.AuthFieldConfig
import com.applicaster.cam.ui.CamNavigationRouter
import com.applicaster.cam.ui.auth.user.UserAuthPresenter

class SignUpPresenter(
    private val view: ISignUpView?,
    private val navigationRouter: CamNavigationRouter
) :
    UserAuthPresenter(view), ISignUpPresenter, SignUpCallback, FacebookAuthCallback {
    override fun onFailure(msg: String) {
        view?.showAlert(msg)
    }

    override fun onSuccess() {
        view?.hideLoadingIndicator()
        when (ContentAccessManager.contract.getCamFlow()) {
            CamFlow.AUTH_AND_STOREFRONT -> navigationRouter.attachBillingFragment()
            else -> view?.close()
        }
    }

    override fun getAuthFieldConfig(): AuthFieldConfig =
        ContentAccessManager.pluginConfigurator.getSignInAuthFields()

    override fun performAuthAction(input: HashMap<String, String>) {
        ContentAccessManager.contract.signUp(input, this)
    }

    override fun onAuthHintClicked() {
        navigationRouter.attachLoginFragment()
    }

    override fun onFacebookAuthActionCompleted(email: String, id: String) {
        view?.showLoadingIndicator()
        ContentAccessManager.contract.signupWithFacebook(email, id, this)
    }
}