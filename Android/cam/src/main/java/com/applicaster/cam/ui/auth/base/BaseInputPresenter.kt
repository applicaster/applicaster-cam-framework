package com.applicaster.cam.ui.auth.base

import android.view.View
import com.applicaster.cam.ContentAccessManager
import com.applicaster.cam.params.auth.AuthField
import com.applicaster.cam.params.auth.AuthFieldConfig
import com.applicaster.cam.ui.base.presenter.BasePresenter

abstract class BaseInputPresenter(
    private val view: IBaseInputView?
) :
    BasePresenter(view), IBaseInputPresenter {

    override fun onViewCreated() {
        super.onViewCreated()

        view?.populateAuthFieldsViews(getAuthFieldConfig())
        view?.customize()
    }

    override fun onErrorIconClicked(rootView: View, errorMsg: String) {
        view?.showErrorPopup(rootView, errorMsg)
    }

    override fun onActionDoneTriggered() {
        val inputFields = view?.getInputFieldsValues() ?: hashMapOf()
        onAuthActionButtonClicked(inputFields)
    }

    override fun onAuthActionButtonClicked(inputValues: HashMap<AuthField, String>) {
        val inputFieldValidationErrors = validateAuthInputFields(inputValues)
        if (inputFieldValidationErrors.isNotEmpty()) {
            view?.showAuthInputFieldErrorIcons(inputFieldValidationErrors)
            return
        }
        view?.showLoadingIndicator()
        val input = inputValues.entries.associate { entry
            ->
            val key = entry.key.key ?: ""
            key to entry.value
        }
        performAuthAction(input.toMutableMap() as HashMap<String, String>)
    }

    private fun validateAuthInputFields(inputValues: HashMap<AuthField, String>): HashMap<AuthField, String> {
        val inputErrors = HashMap<AuthField, String>()
        for (inputValue in inputValues) {
            if (inputValue.key.mandatory == true) {
                if (inputValue.value.isEmpty()) {
                    inputErrors[inputValue.key] =
                        ContentAccessManager.pluginConfigurator.getEmptyInputFieldError()
                } else if (inputValue.key.type == AuthField.Type.EMAIL && !(isEmailValid(inputValue.value))) {
                    inputErrors[inputValue.key] =
                        ContentAccessManager.pluginConfigurator.getNotValidEmailInputFieldError()
                }
            }
        }
        return inputErrors
    }

    private fun isEmailValid(email: String): Boolean {
        return android.util.Patterns.EMAIL_ADDRESS.matcher(email).matches()
    }

    abstract fun performAuthAction(input: HashMap<String, String>)
    abstract fun getAuthFieldConfig(): AuthFieldConfig
}