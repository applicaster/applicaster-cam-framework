package com.applicaster.cam.ui.resetpassword

import com.applicaster.cam.ui.base.presenter.IBasePresenter

interface IPasswordResetPresenter : IBasePresenter {
    fun onResetButtonClicked(inputValues: HashMap<String, String>)
}