package com.applicaster.cam.ui.auth

import android.app.Activity
import android.view.View
import com.applicaster.cam.ContentAccessManager
import com.applicaster.cam.params.auth.AuthField
import com.applicaster.cam.params.auth.AuthFieldConfig
import com.applicaster.cam.ui.base.custom.InputFieldViewListener
import com.applicaster.cam.ui.base.presenter.BasePresenter
import com.applicaster.model.APUser
import com.applicaster.util.FacebookUtil
import com.applicaster.util.asynctask.AsyncTaskListener
import com.applicaster.util.facebook.listeners.FBAuthoriziationListener
import com.applicaster.util.facebook.permissions.APPermissionsType

abstract class AuthPresenter(
    private val view: IAuthView?
) :
    BasePresenter(view), IAuthPresenter, FBAuthoriziationListener {

    override fun onViewCreated() {
        super.onViewCreated()

        view?.populateAuthFieldsViews(getAuthFieldConfig())
        view?.customize()
    }

    override fun onRestoreClicked() {
        view?.showToastMessage("restore action")
    }

    /**
     * [FBAuthoriziationListener] auth success
     */
    override fun onSuccess() {
        FacebookUtil.loadUserInfo(object : AsyncTaskListener<APUser> {

            override fun handleException(error: Exception) {
                view?.hideLoadingIndicator()
                view?.showAlert(error.message ?: "Facebook auth failed")
            }

            override fun onTaskComplete(result: APUser) {
                onFacebookAuthActionCompleted(result.email, result.id)
            }

            override fun onTaskStart() {
                view?.showLoadingIndicator()
            }
        })
    }

    /**
     * [FBAuthoriziationListener] auth cancelled
     */
    override fun onCancel() {
        view?.showToastMessage("Cancelled by user")
    }

    /**
     * [FBAuthoriziationListener] auth error
     */
    override fun onError(error: Exception?) {
        view?.showAlert(error?.message ?: "Facebook auth failed")
    }

    override fun onFacebookButtonClicked(activity: Activity?) {
        if (activity != null && !activity.isFinishing)
            FacebookUtil.updateTokenIfNeeded(activity, APPermissionsType.Custom, this)
    }

    override fun onErrorIconClicked(rootView: View, errorMsg: String) {
        view?.showErrorPopup(rootView, errorMsg)
    }

    override fun onAuthActionButtonClicked(inputValues: HashMap<AuthField, String>) {
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
        performAuthAction(input)
    }

    protected fun validateAuthInputFields(inputValues: HashMap<AuthField, String>): HashMap<AuthField, String> {
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

    abstract override fun onAuthHintClicked()
    abstract fun performAuthAction(input: HashMap<String, String>)
    abstract fun onFacebookAuthActionCompleted(email: String, id: String)
    abstract fun getAuthFieldConfig(): AuthFieldConfig
}