package com.applicaster.cam.ui.auth

import android.app.Activity
import com.applicaster.cam.ContentAccessManager
import com.applicaster.cam.params.auth.AuthFieldConfig
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

    protected fun isAuthInputFieldsValid(inputValues: HashMap<String, String>): Boolean {
        for (inputValue in inputValues) {
            if (inputValue.value.isEmpty()) {
                view?.showAlert(ContentAccessManager.pluginConfigurator.getDefaultInputFieldError())
                return false
            }
        }
        return true
    }

    abstract override fun onAuthActionButtonClicked(inputValues: HashMap<String, String>)
    abstract override fun onAuthHintClicked()
    abstract fun onFacebookAuthActionCompleted(email: String, id: String)
    abstract fun getAuthFieldConfig(): AuthFieldConfig
}