package com.applicaster.cam.ui.resetpassword

import com.applicaster.cam.params.auth.AuthFieldConfig
import com.applicaster.cam.ui.base.view.IBaseView

interface IPasswordResetView : IBaseView {
    fun populateAuthFieldsViews(authFieldConfig: AuthFieldConfig)
}