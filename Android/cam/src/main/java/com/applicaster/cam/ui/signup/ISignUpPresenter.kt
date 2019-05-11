package com.applicaster.cam.ui.signup

import com.applicaster.cam.ui.base.presenter.IBasePresenter

interface ISignUpPresenter : IBasePresenter {
    fun onForgotPasswordClicked()
    fun onSignUpButtonClicked()
    fun onLogInHintClicked()
    fun onToolbarBackClicked()
    fun onToolbarCloseClicked()
    fun onRestoreClicked()
}