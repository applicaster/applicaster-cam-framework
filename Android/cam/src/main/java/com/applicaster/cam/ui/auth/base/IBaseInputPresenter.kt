package com.applicaster.cam.ui.auth.base

import com.applicaster.cam.params.auth.AuthField
import com.applicaster.cam.ui.base.custom.InputFieldViewListener
import com.applicaster.cam.ui.base.presenter.IBasePresenter

interface IBaseInputPresenter : IBasePresenter, InputFieldViewListener {
    fun onAuthActionButtonClicked(inputValues: HashMap<AuthField, String>)
}