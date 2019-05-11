package com.applicaster.cam.ui.signup

import com.applicaster.cam.params.AuthFieldConfig
import com.applicaster.cam.ui.base.view.IBaseView

interface ISignUpView : IBaseView {
    fun goBack()
    fun close()
    fun populateAuthFieldsViews(authFieldConfig: AuthFieldConfig)
}