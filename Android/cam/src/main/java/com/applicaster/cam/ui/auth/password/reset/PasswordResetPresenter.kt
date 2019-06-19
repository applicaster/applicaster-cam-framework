package com.applicaster.cam.ui.auth.password.reset

import android.view.View
import com.applicaster.cam.ContentAccessManager
import com.applicaster.cam.PasswordResetCallback
import com.applicaster.cam.params.auth.AuthField
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

    override fun onResetButtonClicked(inputValues: HashMap<AuthField, String>) {
        val inputFieldValidationErrors = validateAuthInputFields(inputValues)
        if (inputFieldValidationErrors.isNotEmpty()) {
            view?.showAuthInputFieldErrorIcons(inputFieldValidationErrors)
            return
        }
        view?.showLoadingIndicator()
        val input = HashMap<String, String>()
        for (inputEntry in inputValues) {
            inputEntry.key.key?.let { input[it] = inputEntry.value }
        }
        ContentAccessManager.contract.resetPassword(input, this)
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

    private fun getAuthFieldConfig(): AuthFieldConfig =
        ContentAccessManager.pluginConfigurator.getPasswordResetAuthFields()

    private fun validateAuthInputFields(inputValues: HashMap<AuthField, String>): HashMap<AuthField, String> {
        val inputErrors = HashMap<AuthField, String>()
        for (inputValue in inputValues) {
            if (inputValue.value.isEmpty()) {
                inputErrors[inputValue.key] = ContentAccessManager.pluginConfigurator.getEmptyInputFieldError()
            } else if (inputValue.key.type == AuthField.Type.EMAIL && !(isEmailValid(inputValue.value))) {
                inputErrors[inputValue.key] = ContentAccessManager.pluginConfigurator.getNotValidEmailInputFieldError()
            }
        }
        return inputErrors
    }

    private fun isEmailValid(email: String): Boolean {
        return android.util.Patterns.EMAIL_ADDRESS.matcher(email).matches()
    }

    override fun onErrorIconClicked(rootView: View, errorMsg: String) {
        view?.showErrorPopup(rootView, errorMsg)
    }
}