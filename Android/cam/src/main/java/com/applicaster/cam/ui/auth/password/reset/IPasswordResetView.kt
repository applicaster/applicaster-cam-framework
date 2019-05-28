package com.applicaster.cam.ui.auth.password.reset

import com.applicaster.cam.params.auth.AuthFieldConfig
import com.applicaster.cam.ui.base.view.IBaseView

interface IPasswordResetView : IBaseView {
    fun populateAuthFieldsViews(authFieldConfig: AuthFieldConfig)
}