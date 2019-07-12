package com.applicaster.cam.ui.auth.password.reset

import com.applicaster.cam.ContentAccessManager
import com.applicaster.cam.PasswordResetCallback
import com.applicaster.cam.analytics.AnalyticsUtil
import com.applicaster.cam.params.auth.AuthFieldConfig
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
        AnalyticsUtil.logResetPassword()
    }

    override fun onFailure(msg: String) {
        view?.hideLoadingIndicator()
        view?.showAlert(msg)
    }

    override fun onSuccess() {
        view?.hideLoadingIndicator()
        if (ContentAccessManager.pluginConfigurator.isShowConfirmationPasswordReset())
            navigationRouter.showConfirmationDialog(AlertDialogType.RESET_PASSWORD)
        else
            view?.goBack()
    }

    override fun getAuthFieldConfig(): AuthFieldConfig =
        ContentAccessManager.pluginConfigurator.getPasswordResetAuthFields()


}