package com.applicaster.cam.ui.auth.user.login

import com.applicaster.cam.ui.auth.base.IBaseInputView

interface ILoginView : IBaseInputView {
    fun initBackButton(enable: Boolean)
}