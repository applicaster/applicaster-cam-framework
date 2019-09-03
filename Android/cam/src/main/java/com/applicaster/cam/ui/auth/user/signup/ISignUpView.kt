package com.applicaster.cam.ui.auth.user.signup

import com.applicaster.cam.ui.auth.base.IBaseInputView

interface ISignUpView : IBaseInputView {
    fun initBackButton(enable: Boolean)
}