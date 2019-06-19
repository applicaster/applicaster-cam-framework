package com.applicaster.cam.ui.auth.password.reset

import com.applicaster.cam.ContentAccessManager
import com.applicaster.cam.PasswordResetCallback
import com.applicaster.cam.params.auth.AuthFieldConfig
import com.applicaster.cam.ui.CamNavigationRouter
import com.applicaster.cam.ui.base.presenter.BasePresenter
import com.applicaster.cam.ui.confirmation.AlertDialogType

class PasswordResetPresenter(
    private val view: IPasswordResetView?,
    private val navigationRouter: CamNavigationRouter
) :
    BasePresenter(view), IPasswordResetPresenter, PasswordResetCallback {

    override fun onViewCreated() {
        super.onViewCreated()

        view?.populateAuthFieldsViews(getAuthFieldConfig())
        view?.customize()
    }


    override fun onResetButtonClicked(inputValues: HashMap<String, String>) {
        if (!isAuthInputFieldsValid(inputValues)) return
        view?.showLoadingIndicator()
        ContentAccessManager.contract.resetPassword(inputValues, this)
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

    private fun isAuthInputFieldsValid(inputValues: HashMap<String, String>): Boolean {
        for (inputValue in inputValues) {
            if (inputValue.value.isEmpty()) {
                view?.showAlert(ContentAccessManager.pluginConfigurator.getEmptyInputFieldError())
                return false
            }
        }
        return true
    }

    fun getAuthFieldConfig(): AuthFieldConfig =
        ContentAccessManager.pluginConfigurator.getPasswordResetAuthFields()
}