package com.applicaster.cam.ui.auth

import com.applicaster.cam.ui.base.presenter.IBasePresenter

interface IAuthPresenter : IBasePresenter {
    fun onAuthActionButtonClicked(inputValues: HashMap<String, String>)
    fun onAuthHintClicked()
    fun onRestoreClicked()
}