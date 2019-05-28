package com.applicaster.cam.ui.resetpassword

import com.applicaster.cam.ContentAccessManager
import com.applicaster.cam.params.auth.AuthFieldConfig
import com.applicaster.cam.ui.CamNavigationRouter
import com.applicaster.cam.ui.base.presenter.BasePresenter

class PasswordResetPresenter(
    private val view: IPasswordResetView?,
    private val navigationRouter: CamNavigationRouter
) :
    BasePresenter(view), IPasswordResetPresenter {

    override fun onViewCreated() {
        super.onViewCreated()

        view?.populateAuthFieldsViews(getAuthFieldConfig())
        view?.customize()
    }


    override fun onResetButtonClicked(inputValues: HashMap<String, String>) {
        TODO("not implemented") //To change body of created functions use File | Settings | File Templates.
    }


    private fun isAuthInputFieldsValid(inputValues: HashMap<String, String>): Boolean {
        for (inputValue in inputValues) {
            if (inputValue.value.isEmpty()) {
                view?.showToastMessage("You must fill all fields")
                return true
            }
        }
        return false
    }

    fun getAuthFieldConfig(): AuthFieldConfig =
            ContentAccessManager.pluginConfigurator.getPasswordResetAuthFields()
}