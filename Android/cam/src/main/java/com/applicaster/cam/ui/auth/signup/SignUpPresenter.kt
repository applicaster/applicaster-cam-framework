package com.applicaster.cam.ui.auth.signup

import com.applicaster.cam.ui.CamNavigationRouter
import com.applicaster.cam.ui.auth.AuthPresenter

class SignUpPresenter(
    private val view: ISignUpView?,
    private val navigationRouter: CamNavigationRouter
) :
    AuthPresenter(view, navigationRouter), ISignUpPresenter {

}