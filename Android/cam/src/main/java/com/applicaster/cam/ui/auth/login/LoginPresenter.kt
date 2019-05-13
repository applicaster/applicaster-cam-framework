package com.applicaster.cam.ui.auth.login

import com.applicaster.cam.ui.CamNavigationRouter
import com.applicaster.cam.ui.auth.AuthPresenter

class LoginPresenter(
    private val view: ILoginView?,
    private val navigationRouter: CamNavigationRouter
) :
    AuthPresenter(view, navigationRouter), ILoginPresenter {

}