package com.applicaster.cam.ui.auth.password.update

import android.util.Log
import com.applicaster.cam.ContentAccessManager
import com.applicaster.cam.PasswordUpdateCallback
import com.applicaster.cam.analytics.AnalyticsUtil
import com.applicaster.cam.params.auth.AuthField
import com.applicaster.cam.params.auth.AuthFieldConfig
import com.applicaster.cam.params.auth.AuthScreenType
import com.applicaster.cam.ui.CamNavigationRouter
import com.applicaster.cam.ui.auth.base.BaseInputPresenter
import com.applicaster.cam.ui.auth.base.IBaseInputPresenter
import com.applicaster.cam.ui.auth.base.IBaseInputView
import com.applicaster.cam.ui.confirmation.AlertDialogType

class PasswordUpdatePresenter(
    private val view: IBaseInputView?,
    private val navigationRouter: CamNavigationRouter
) :
    BaseInputPresenter(view), IBaseInputPresenter, PasswordUpdateCallback {

    private val TAG = "PasswordUpdatePresenter"

    override fun onViewCreated() {
        super.onViewCreated()

        view?.customize()
    }

    override fun performAuthAction(input: HashMap<String, String>) {
        ContentAccessManager.contract.updatePassword(input, this)
    }

    override fun onFailure(msg: String) {
        Log.e(TAG, "onFailure: $msg")
        view?.hideLoadingIndicator()
        view?.showAlert(msg)
    }

    override fun onAuthActionButtonClicked(inputValues: HashMap<AuthField, String>) {
        //Analytics
        AnalyticsUtil.logUpdatePassword()
        super.onAuthActionButtonClicked(inputValues)
    }

    override fun onActionSuccess() {
        view?.hideLoadingIndicator()
        view?.hideKeyboard()
        if (ContentAccessManager.pluginConfigurator.isShowConfirmationPasswordReset()) {
            navigationRouter.showConfirmationDialog(AlertDialogType.UPDATE_PASSWORD)
        } else {
            navigationRouter.navigateFragmentBackTwice()
        }
    }

    override fun getAuthFieldConfig(): AuthFieldConfig =
        ContentAccessManager.pluginConfigurator.getAuthFields(AuthScreenType.PASSWORD_UPDATE)
}