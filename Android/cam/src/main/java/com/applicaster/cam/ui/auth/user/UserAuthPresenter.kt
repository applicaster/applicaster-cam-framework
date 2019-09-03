package com.applicaster.cam.ui.auth.user

import android.app.Activity
import com.applicaster.cam.ContentAccessManager
import com.applicaster.cam.analytics.AnalyticsUtil
import com.applicaster.cam.analytics.ConfirmationAlertData
import com.applicaster.cam.analytics.ConfirmationCause
import com.applicaster.cam.ui.auth.base.BaseInputPresenter
import com.applicaster.cam.ui.auth.base.IBaseInputView
import com.applicaster.model.APUser
import com.applicaster.util.FacebookUtil
import com.applicaster.util.asynctask.AsyncTaskListener
import com.applicaster.util.facebook.listeners.FBAuthoriziationListener
import com.applicaster.util.facebook.permissions.APPermissionsType
import com.applicaster.util.facebook.permissions.CustomFBPermissions

abstract class UserAuthPresenter(private val view: IBaseInputView?) : BaseInputPresenter(view),
    IUserAuthPresenter {

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
                val errorMessage: String =
                        if (error.message.isNullOrEmpty()) "Facebook auth failed" else error.message.orEmpty()
                view?.showAlert(errorMessage)
                AnalyticsUtil.logViewAlert(
                    ConfirmationAlertData(
                        false,
                        ConfirmationCause.NONE,
                        "",
                            errorMessage,
                            errorMessage
                    )
                )
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
        view?.hideLoadingIndicator()
        error?.printStackTrace()
        val errorMessage: String = 
                if (error?.message.isNullOrEmpty()) "Facebook auth failed" else error?.message.orEmpty()
        view?.showAlert(errorMessage)

        AnalyticsUtil.logAlternativeLoginFailure()
        AnalyticsUtil.logViewAlert(
            ConfirmationAlertData(
                false,
                ConfirmationCause.NONE,
                "",
                    errorMessage,
                    errorMessage
            )
        )
    }

    override fun onFacebookButtonClicked(activity: Activity?) {
        if (activity != null && !activity.isFinishing) {
            CustomFBPermissions.getInstance().basicPermissions = listOf("public_profile", "email")
            FacebookUtil.updateTokenIfNeeded(activity, APPermissionsType.Custom, this)
        }
    }

    abstract fun onFacebookAuthActionCompleted(email: String, id: String)
}