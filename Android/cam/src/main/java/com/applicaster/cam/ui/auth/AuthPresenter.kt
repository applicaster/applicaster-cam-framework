package com.applicaster.cam.ui.auth

import com.applicaster.cam.params.auth.AuthFieldConfig
import com.applicaster.cam.ui.CamNavigationRouter
import com.applicaster.cam.ui.base.presenter.BasePresenter

abstract class AuthPresenter(
        private val view: IAuthView?,
        private val navigationRouter: CamNavigationRouter
) :
        BasePresenter(view), IAuthPresenter {

    override fun onViewCreated() {
        super.onViewCreated()

        view?.populateAuthFieldsViews(getAuthFieldConfig())
        view?.customize()
    }

    override fun onRestoreClicked() {
        view?.showToastMessage("restore action")
    }

    protected fun isAuthInputFieldsValid(inputValues: HashMap<String, String>): Boolean {
        for (inputValue in inputValues) {
            if (inputValue.value.isEmpty()) {
                view?.showToastMessage("You must fill all fields")
                return true
            }
        }
        return false
    }

    abstract override fun onAuthActionButtonClicked(inputValues: HashMap<String, String>)
    abstract override fun onAuthHintClicked()
    abstract fun getAuthFieldConfig(): AuthFieldConfig
}