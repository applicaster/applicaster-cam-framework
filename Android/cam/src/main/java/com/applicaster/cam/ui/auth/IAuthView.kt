package com.applicaster.cam.ui.auth

import com.applicaster.cam.params.auth.AuthFieldConfig
import com.applicaster.cam.ui.base.view.IBaseView

interface IAuthView : IBaseView {
    fun populateAuthFieldsViews(authFieldConfig: AuthFieldConfig)
    fun applyUICustomizations()
}