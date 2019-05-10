package com.applicaster.cam.ui.signup

import android.util.Log
import com.applicaster.cam.ContentAccessManagerImpl
import com.applicaster.cam.ui.CamNavigationRouter
import com.applicaster.cam.ui.base.presenter.BasePresenter

class SignUpPresenter(private val view: ISignUpView?, private val navigationRouter: CamNavigationRouter) :
    BasePresenter(view), ISignUpPresenter {

    override fun onViewCreated() {
        super.onViewCreated()

       val authFieldConfig = ContentAccessManagerImpl.getSignInAuthFields()
        Log.d("test", "test ${authFieldConfig.authFields}")
    }

    override fun onForgotPasswordClicked() {
        TODO("not implemented") //To change body of created functions use File | Settings | File Templates.
    }

    override fun onSignUpButtonClicked() {
        TODO("not implemented") //To change body of created functions use File | Settings | File Templates.
    }

    override fun onLogInHintClicked() {
        TODO("not implemented") //To change body of created functions use File | Settings | File Templates.
    }

    override fun onToolbarBackClicked() {
        view?.goBack()
    }

    override fun onToolbarCloseClicked() {
        view?.close()
    }

    override fun onRestoreClicked() {
        TODO("not implemented") //To change body of created functions use File | Settings | File Templates.
    }
}