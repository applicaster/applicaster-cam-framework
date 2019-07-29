package com.applicaster.cam.ui.auth.user.login

import android.app.Activity
import com.applicaster.cam.CamFlow
import com.applicaster.cam.ContentAccessManager
import com.applicaster.cam.FacebookAuthCallback
import com.applicaster.cam.LoginCallback
import com.applicaster.cam.analytics.*
import com.applicaster.cam.params.auth.AuthFieldConfig
import com.applicaster.cam.ui.CamNavigationRouter
import com.applicaster.cam.ui.auth.user.UserAuthPresenter

class LoginPresenter(
    private val view: ILoginView?,
    private val navigationRouter: CamNavigationRouter
) :
    UserAuthPresenter(view), ILoginPresenter, LoginCallback, FacebookAuthCallback {

    override fun onViewCreated() {
        super.onViewCreated()
        //Analytics event
        AnalyticsUtil.logContentGatewaySession(
            TimedEvent.START,
            ContentAccessManager.contract.getAnalyticsDataProvider().getTrigger().value,
            Action.LOGIN
        )
    }

    override fun getAuthFieldConfig(): AuthFieldConfig =
        ContentAccessManager.pluginConfigurator.getLoginAuthFields()

    override fun onForgotPasswordClicked() {
        navigationRouter.attachPasswordResetFragment()
        AnalyticsUtil.logLaunchPasswordResetScreen()
    }

    override fun performAuthAction(input: HashMap<String, String>) {
        ContentAccessManager.contract.login(input, this)
        AnalyticsUtil.logTapStandardLoginButton()
    }

    override fun onFailure(msg: String) {
        view?.hideLoadingIndicator()
        view?.showAlert(msg)

        AnalyticsUtil.logStandardLoginFailure()
        AnalyticsUtil.logViewAlert(
            ConfirmationAlertData(
                false,
                ConfirmationCause.NONE,
                "",
                msg,
                msg
            )
        )
    }

    override fun onSuccess() {
        view?.hideLoadingIndicator()
        AnalyticsUtil.logStandardLoginSuccess()
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
        AnalyticsUtil.logSwitchToSignUpScreen()
    }

    override fun onFacebookAuthActionCompleted(email: String, id: String) {
        view?.showLoadingIndicator()
        ContentAccessManager.contract.loginWithFacebook(email, id, this)
        AnalyticsUtil.logAlternativeLoginSuccess()
    }

    override fun onError(error: Exception?) {
        super.onError(error)
        AnalyticsUtil.logAlternativeSignUpFailure()
        AnalyticsUtil.logViewAlert(
            ConfirmationAlertData(
                false,
                ConfirmationCause.NONE,
                "",
                error?.message.orEmpty(),
                error?.message.orEmpty()
            )
        )
    }

    override fun onFacebookButtonClicked(activity: Activity?) {
        super.onFacebookButtonClicked(activity)
        AnalyticsUtil.logTapAlternativeLogin()
    }
}