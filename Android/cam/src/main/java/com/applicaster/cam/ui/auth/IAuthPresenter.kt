package com.applicaster.cam.ui.auth

import com.applicaster.cam.ui.base.presenter.IBasePresenter

interface IAuthPresenter : IBasePresenter {
    fun onForgotPasswordClicked()
    fun onSignUpButtonClicked()
    fun onLogInHintClicked()
    fun onRestoreClicked()
}