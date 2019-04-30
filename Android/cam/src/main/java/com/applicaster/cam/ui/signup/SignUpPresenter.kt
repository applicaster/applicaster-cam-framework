package com.applicaster.cam.ui.signup

import com.applicaster.cam.ui.CamNavigationRouter
import com.applicaster.cam.ui.base.presenter.BasePresenter

class SignUpPresenter(private val view: ISignUpView, private val navigationRouter: CamNavigationRouter) :
    BasePresenter(view), ISignUpPresenter {
}