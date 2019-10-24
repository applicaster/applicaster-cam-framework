package com.applicaster.cam.ui.auth.user.login

import android.app.Activity
import com.applicaster.cam.CamFlow
import com.applicaster.cam.ContentAccessManager
import com.applicaster.cam.FacebookAuthCallback
import com.applicaster.cam.LoginCallback
import com.applicaster.cam.analytics.*
import com.applicaster.cam.params.auth.AuthField
import com.applicaster.cam.params.auth.AuthFieldConfig
import com.applicaster.cam.params.auth.AuthScreenType
import com.applicaster.cam.ui.CamNavigationRouter
import com.applicaster.cam.ui.auth.user.UserAuthPresenter

class LoginPresenter(
    private val view: ILoginView?,
    private val navigationRouter: CamNavigationRouter
) :
    UserAuthPresenter(view), ILoginPresenter, LoginCallback, FacebookAuthCallback {

    override fun onViewCreated() {
        super.onViewCreated()
        when (ContentAccessManager.pluginConfigurator.getDefaultAuthScreen()) {
            AuthScreenType.LOGIN -> view?.initBackButton(!ContentAccessManager.pluginConfigurator.isTriggerOnAppLaunch())
            else -> view?.initBackButton(enable = true)
        }

        AnalyticsGatewaySession.sessionData.add(Action.LOGIN)
    }

    override fun getAuthFieldConfig(): AuthFieldConfig =
        ContentAccessManager.pluginConfigurator.getLoginAuthFields()

    override fun onForgotPasswordClicked() {
        navigationRouter.attachPasswordResetFragment()
        AnalyticsUtil.logLaunchPasswordResetScreen()
    }

    override fun performAuthAction(input: HashMap<String, String>) {
        ContentAccessManager.contract.login(input, this)
    }

    override fun onAuthActionButtonClicked(inputValues: HashMap<AuthField, String>) {
        AnalyticsUtil.logTapStandardLoginButton()
        super.onAuthActionButtonClicked(inputValues)
    }

    override fun onFailure(msg: String) {
        view?.hideLoadingIndicator()
        view?.showAlert(msg)
        //Analytics
        AnalyticsUtil.logStandardLoginFailure()
        AnalyticsUtil.logViewAlert(
            ConfirmationAlertData(
                false,
                ConfirmationCause.NONE,
                AnalyticsUtil.KEY_NON_PROVIDED,
                AnalyticsUtil.KEY_NON_PROVIDED,
                msg
            )
        )
        //
    }

    override fun onActionSuccess() {
        view?.hideLoadingIndicator()
        view?.hideKeyboard()
        //Analytics
        AnalyticsUtil.logStandardLoginSuccess()
        AnalyticsUtil.logUserProperties(
            AnalyticsUtil.collectPurchaseData(
                ContentAccessManager.contract.getAnalyticsDataProvider().purchaseData
            )
        )
        //
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
        //Analytics
        AnalyticsUtil.logAlternativeLoginFailure()
        AnalyticsUtil.logViewAlert(
            ConfirmationAlertData(
                false,
                ConfirmationCause.NONE,
                AnalyticsUtil.KEY_NON_PROVIDED,
                AnalyticsUtil.KEY_NON_PROVIDED,
                error?.message ?: AnalyticsUtil.KEY_NON_PROVIDED
            )
        )
        //
    }

    override fun onFacebookButtonClicked(activity: Activity?) {
        super.onFacebookButtonClicked(activity)
        AnalyticsUtil.logTapAlternativeLogin()
    }

    override fun onLastFragmentClosed() {
        AnalyticsGatewaySession.sessionData.add(Action.CANCEL)
    }
}