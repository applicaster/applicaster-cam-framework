package com.applicaster.cam.ui.auth.user.activation

import com.applicaster.cam.ui.auth.base.IBaseInputPresenter

interface IAccountActivationPresenter : IBaseInputPresenter {
    fun onResendCodeClicked()
}