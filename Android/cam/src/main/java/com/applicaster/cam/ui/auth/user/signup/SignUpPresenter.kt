package com.applicaster.cam.ui.auth.user.signup

import android.app.Activity
import com.applicaster.cam.CamFlow
import com.applicaster.cam.ContentAccessManager
import com.applicaster.cam.FacebookAuthCallback
import com.applicaster.cam.SignUpCallback
import com.applicaster.cam.analytics.*
import com.applicaster.cam.params.auth.AuthField
import com.applicaster.cam.params.auth.AuthFieldConfig
import com.applicaster.cam.params.auth.AuthScreenType
import com.applicaster.cam.ui.CamNavigationRouter
import com.applicaster.cam.ui.auth.user.UserAuthPresenter

class SignUpPresenter(
    private val view: ISignUpView?,
    private val navigationRouter: CamNavigationRouter
) :
    UserAuthPresenter(view), ISignUpPresenter, SignUpCallback, FacebookAuthCallback {

    override fun onViewCreated() {
        super.onViewCreated()
        when (ContentAccessManager.pluginConfigurator.getDefaultAuthScreen()) {
            AuthScreenType.SIGNUP -> view?.initBackButton(!ContentAccessManager.pluginConfigurator.isTriggerOnAppLaunch())
            else -> view?.initBackButton(enable = true)
        }
    }

    override fun onFacebookAuthFailure(msg: String) {
        view?.hideLoadingIndicator()
        view?.showAlert(msg)
        AnalyticsUtil.logAlternativeSignUpFailure()
    }

    override fun onFacebookAuthSuccess() {
        view?.hideLoadingIndicator()
        view?.hideKeyboard()
        AnalyticsUtil.logAlternativeSignUpSuccess()
    }

    override fun onFailure(msg: String) {
        view?.hideLoadingIndicator()
        view?.showAlert(msg)
        //Analytics
        AnalyticsUtil.logStandardSignUpFailure()
        AnalyticsUtil.logViewAlert(
            ConfirmationAlertData(
                false,
                ConfirmationCause.NONE,
                AnalyticsUtil.KEY_NONE_PROVIDED,
                AnalyticsUtil.KEY_NONE_PROVIDED,
                msg
            )
        )
        AnalyticsGatewaySession.sessionData.add(Action.FAILED_ATTEMPT)
        //
    }

    override fun onActionSuccess() {
        view?.hideLoadingIndicator()
        view?.hideKeyboard()
        //Analytics
        AnalyticsUtil.logStandardSignUpSuccess()
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

    override fun getAuthFieldConfig(): AuthFieldConfig =
        ContentAccessManager.pluginConfigurator.getSignInAuthFields()

    override fun performAuthAction(input: HashMap<String, String>) {
        ContentAccessManager.contract.signUp(input, this)
    }

    override fun onAuthHintClicked() {
        navigationRouter.attachLoginFragment()
        AnalyticsUtil.logSwitchToLoginScreen()
    }

    override fun onAuthActionButtonClicked(inputValues: HashMap<AuthField, String>) {
        //Analytics
        AnalyticsGatewaySession.sessionData.add(Action.SIGNUP)
        AnalyticsUtil.logTapStandardSignUpButton()
        super.onAuthActionButtonClicked(inputValues)
    }

    override fun onFacebookAuthActionCompleted(email: String, id: String) {
        view?.showLoadingIndicator()
        ContentAccessManager.contract.signupWithFacebook(email, id, this)
    }

    override fun onError(error: Exception?) {
        super.onError(error)
        //Analytics
        AnalyticsUtil.logViewAlert(
            ConfirmationAlertData(
                false,
                ConfirmationCause.NONE,
                AnalyticsUtil.KEY_NONE_PROVIDED,
                AnalyticsUtil.KEY_NONE_PROVIDED,
                error?.message ?: AnalyticsUtil.KEY_NONE_PROVIDED
            )
        )
        //
    }

    override fun onCancel() {
        super.onCancel()
        AnalyticsUtil.logAlternativeSignUpCancel()
    }

    override fun onFacebookButtonClicked(activity: Activity?) {
        super.onFacebookButtonClicked(activity)
        AnalyticsUtil.logTapAlternativeSignUp()
    }

    override fun onLastFragmentClosed() {
        AnalyticsGatewaySession.sessionData.add(Action.CANCEL)
    }
}