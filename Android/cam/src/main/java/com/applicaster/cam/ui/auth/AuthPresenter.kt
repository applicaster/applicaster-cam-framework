package com.applicaster.cam.ui.auth

import com.applicaster.cam.ContentAccessManager
import com.applicaster.cam.ui.CamNavigationRouter
import com.applicaster.cam.ui.base.presenter.BasePresenter

open class AuthPresenter(
    private val view: IAuthView?,
    private val navigationRouter: CamNavigationRouter
) :
    BasePresenter(view), IAuthPresenter {

    override fun onViewCreated() {
        super.onViewCreated()

        val authFieldConfig = ContentAccessManager.pluginConfigurator.getSignInAuthFields()
        view?.populateAuthFieldsViews(authFieldConfig)
        view?.applyUICustomizations()
    }

    override fun onForgotPasswordClicked() {
//        TODO("not implemented") //To change body of created functions use File | Settings | File Templates.
    }

    override fun onSignUpButtonClicked() {
//        TODO("not implemented") //To change body of created functions use File | Settings | File Templates.
    }

    override fun onLogInHintClicked() {
//        TODO("not implemented") //To change body of created functions use File | Settings | File Templates.
    }


    override fun onRestoreClicked() {
//        TODO("not implemented") //To change body of created functions use File | Settings | File Templates.
    }
}