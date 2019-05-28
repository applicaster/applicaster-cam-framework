package com.applicaster.cam.ui.auth

import android.app.Activity
import com.applicaster.cam.ui.base.presenter.IBasePresenter

interface IAuthPresenter : IBasePresenter {
    fun onAuthActionButtonClicked(inputValues: HashMap<String, String>)
    fun onAuthHintClicked()
    fun onRestoreClicked()
    fun onFacebookButtonClicked(activity: Activity?)
}