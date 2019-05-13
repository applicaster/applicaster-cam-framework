package com.applicaster.cam.ui.auth.login

import com.applicaster.cam.ui.auth.IAuthPresenter

interface ILoginPresenter : IAuthPresenter {
    fun onForgotPasswordClicked()
}