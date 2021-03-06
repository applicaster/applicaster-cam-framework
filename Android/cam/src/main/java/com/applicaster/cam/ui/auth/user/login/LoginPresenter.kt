package com.applicaster.cam.ui.auth.user.login

import android.app.Activity
import android.content.ActivityNotFoundException
import android.util.Log
import com.applicaster.cam.ContentAccessManager
import com.applicaster.cam.FacebookAuthCallback
import com.applicaster.cam.LoginCallback
import com.applicaster.cam.analytics.*
import com.applicaster.cam.params.auth.AuthField
import com.applicaster.cam.params.auth.AuthFieldConfig
import com.applicaster.cam.params.auth.AuthScreenType
import com.applicaster.cam.ui.CamNavigationRouter
import com.applicaster.cam.ui.auth.user.UserAuthPresenter
import com.applicaster.cam.ui.base.presenter.ICustomLinkActionHandler

class LoginPresenter(
    private val view: ILoginView?,
    private val navigationRouter: CamNavigationRouter
) :
    UserAuthPresenter(view), ILoginPresenter, LoginCallback, FacebookAuthCallback, ICustomLinkActionHandler {

    private val TAG = "LoginPresenter"

    private val userInput: HashMap<String, String> = hashMapOf()

    override fun onViewCreated() {
        super.onViewCreated()
        when (ContentAccessManager.pluginConfigurator.getDefaultAuthScreen()) {
            AuthScreenType.LOGIN -> view?.initBackButton(!ContentAccessManager.pluginConfigurator.isTriggerOnAppLaunch())
            else -> view?.initBackButton(enable = true)
        }
    }

    override fun getAuthFieldConfig(): AuthFieldConfig =
        ContentAccessManager.pluginConfigurator.getAuthFields(AuthScreenType.LOGIN)

    override fun onForgotPasswordClicked() {
        navigationRouter.attachPasswordResetFragment()
        AnalyticsUtil.logLaunchPasswordResetScreen()
    }

    override fun performAuthAction(input: HashMap<String, String>) {
        userInput.clear()
        userInput.putAll(input)
        ContentAccessManager.contract.login(input, this)
    }

    override fun onAuthActionButtonClicked(inputValues: HashMap<AuthField, String>) {
        //Analytics
        AnalyticsGatewaySession.sessionData.add(Action.LOGIN)
        AnalyticsUtil.logTapStandardLoginButton()
        super.onAuthActionButtonClicked(inputValues)
    }

    override fun onFacebookAuthFailure(msg: String) {
        Log.e(TAG, "onFacebookAuthFailure: $msg")
        view?.hideLoadingIndicator()
        view?.showAlert(msg)
        AnalyticsUtil.logAlternativeLoginFailure()
        AnalyticsUtil.logViewAlert(
            ConfirmationAlertData(
                false,
                AlertType.ERROR_ALERT,
                AnalyticsUtil.KEY_NONE_PROVIDED,
                msg,
                AnalyticsUtil.KEY_NONE_PROVIDED
            )
        )
    }

    override fun onFacebookAuthSuccess() {
        view?.hideLoadingIndicator()
        view?.hideKeyboard()
        AnalyticsUtil.logAlternativeLoginSuccess()
        navigateOnAuthSuccess(navigationRouter)
    }

    override fun onFailure(msg: String) {
        Log.e(TAG, "onFailure: $msg")
        view?.hideLoadingIndicator()
        view?.showAlert(msg)
        //Analytics
        AnalyticsUtil.logStandardLoginFailure()
        AnalyticsUtil.logViewAlert(
            ConfirmationAlertData(
                false,
                AlertType.ERROR_ALERT,
                AnalyticsUtil.KEY_NONE_PROVIDED,
                msg,
                AnalyticsUtil.KEY_NONE_PROVIDED
            )
        )
        AnalyticsGatewaySession.sessionData.add(Action.FAILED_ATTEMPT)
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

        if (ContentAccessManager.pluginConfigurator.isAccountActivationRequired() &&
            !ContentAccessManager.contract.isUserActivated()
        ) {
            navigationRouter.attachAccountActivation(userInput)
        } else {
            navigateOnAuthSuccess(navigationRouter)
        }
    }

    override fun onAuthHintClicked() {
        navigationRouter.attachSignUpFragment()
        AnalyticsUtil.logSwitchToSignUpScreen()
    }

    override fun onFacebookAuthActionCompleted(email: String, id: String) {
        view?.showLoadingIndicator()
        ContentAccessManager.contract.loginWithFacebook(email, id, this)
    }

    override fun onError(error: Exception?) {
        super.onError(error)
        //Analytics
        AnalyticsUtil.logViewAlert(
            ConfirmationAlertData(
                false,
                AlertType.ERROR_ALERT,
                AnalyticsUtil.KEY_NONE_PROVIDED,
                AnalyticsUtil.KEY_NONE_PROVIDED,
                error?.message ?: AnalyticsUtil.KEY_NONE_PROVIDED
            )
        )
        //
    }

    override fun onCancel() {
        super.onCancel()
        AnalyticsUtil.logAlternativeLoginCancel()
    }

    override fun onFacebookButtonClicked(activity: Activity?) {
        super.onFacebookButtonClicked(activity)
        AnalyticsUtil.logTapAlternativeLogin()
    }

    override fun onLastFragmentClosed() {
        AnalyticsGatewaySession.sessionData.add(Action.CANCEL)
    }

    override fun onCustomLinkClicked(linkText: String, linkUrl: String) {
        AnalyticsUtil.logTapCustomLink(CustomLinkData(linkUrl, linkText, ScreenName.LOGIN))
        try {
            navigationRouter.openBrowserWithUrl(linkUrl)
        } catch (exception: ActivityNotFoundException) {
            view?.showAlert(ContentAccessManager.pluginConfigurator.getDefaultAlertText())
        } catch (exception: NullPointerException) {
            view?.showAlert(ContentAccessManager.pluginConfigurator.getDefaultAlertText())
        }
    }
}