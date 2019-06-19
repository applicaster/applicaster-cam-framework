package com.applicaster.cam.ui.auth.password.reset

import com.applicaster.cam.params.auth.AuthField
import com.applicaster.cam.ui.base.custom.InputFieldViewListener
import com.applicaster.cam.ui.base.presenter.IBasePresenter

interface IPasswordResetPresenter : IBasePresenter, InputFieldViewListener {
    fun onResetButtonClicked(inputValues: HashMap<AuthField, String>)
}