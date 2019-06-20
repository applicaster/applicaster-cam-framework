package com.applicaster.cam.ui.auth.user.login

import com.applicaster.cam.ui.auth.user.IUserAuthPresenter

interface ILoginPresenter : IUserAuthPresenter {
    fun onForgotPasswordClicked()
}