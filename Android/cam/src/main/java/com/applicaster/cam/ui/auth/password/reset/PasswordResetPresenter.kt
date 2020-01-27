package com.applicaster.cam.ui.auth.password.reset

import com.applicaster.cam.ContentAccessManager
import com.applicaster.cam.PasswordResetCallback
import com.applicaster.cam.analytics.*
import com.applicaster.cam.params.auth.AuthField
import com.applicaster.cam.params.auth.AuthFieldConfig
import com.applicaster.cam.params.auth.AuthScreenType
import com.applicaster.cam.ui.CamNavigationRouter
import com.applicaster.cam.ui.auth.base.BaseInputPresenter
import com.applicaster.cam.ui.confirmation.AlertDialogType

class PasswordResetPresenter(
    private val view: IPasswordResetView?,
    private val navigationRouter: CamNavigationRouter
) :
    BaseInputPresenter(view), IPasswordResetPresenter, PasswordResetCallback {

    override fun onViewCreated() {
        super.onViewCreated()

        view?.customize()
    }

    override fun performAuthAction(input: HashMap<String, String>) {
        ContentAccessManager.contract.resetPassword(input, this)
    }

    override fun onAuthActionButtonClicked(inputValues: HashMap<AuthField, String>) {
        //Analytics
        AnalyticsGatewaySession.sessionData.add(Action.RESET_PASSWORD)
        AnalyticsUtil.logResetPassword()
        super.onAuthActionButtonClicked(inputValues)
    }

    override fun onFailure(msg: String) {
        view?.hideLoadingIndicator()
        view?.showAlert(msg)
        //Analytics
        AnalyticsUtil.logViewAlert(
            ConfirmationAlertData(
                false,
                AlertType.ERROR_ALERT,
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
        if (ContentAccessManager.pluginConfigurator.isShowConfirmationPasswordReset()) {
            navigationRouter.showConfirmationDialog(AlertDialogType.RESET_PASSWORD)
        } else {
            view?.goBack()
        }
    }

    override fun getAuthFieldConfig(): AuthFieldConfig =
        ContentAccessManager.pluginConfigurator.getAuthFields(AuthScreenType.PASSWORD_RESET)
}