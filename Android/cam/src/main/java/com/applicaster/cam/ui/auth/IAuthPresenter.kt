package com.applicaster.cam.ui.auth

import android.app.Activity
import com.applicaster.cam.params.auth.AuthField
import com.applicaster.cam.ui.base.custom.InputFieldViewListener
import com.applicaster.cam.ui.base.presenter.IBasePresenter

interface IAuthPresenter : IBasePresenter, InputFieldViewListener {
    fun onAuthActionButtonClicked(inputValues: HashMap<AuthField, String>)
    fun onAuthHintClicked()
    fun onRestoreClicked()
    fun onFacebookButtonClicked(activity: Activity?)
}