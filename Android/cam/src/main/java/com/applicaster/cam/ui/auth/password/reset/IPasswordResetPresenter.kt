package com.applicaster.cam.ui.auth.password.reset

import com.applicaster.cam.ui.base.presenter.IBasePresenter

interface IPasswordResetPresenter : IBasePresenter {
    fun onResetButtonClicked(inputValues: HashMap<String, String>)
}