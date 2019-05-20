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
        view?.applyUICustomizations()
    }

    override fun onRestoreClicked() {
        view?.showToastMessage("restore action")
    }

    abstract override fun onAuthActionButtonClicked()
    abstract override fun onAuthHintClicked()
    abstract fun getAuthFieldConfig(): AuthFieldConfig
}