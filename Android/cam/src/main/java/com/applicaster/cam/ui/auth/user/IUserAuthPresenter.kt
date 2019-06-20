package com.applicaster.cam.ui.auth.user

import android.app.Activity
import com.applicaster.cam.ui.auth.base.IBaseInputPresenter
import com.applicaster.util.facebook.listeners.FBAuthoriziationListener

interface IUserAuthPresenter : IBaseInputPresenter, FBAuthoriziationListener {
    fun onAuthHintClicked()
    fun onRestoreClicked()
    fun onFacebookButtonClicked(activity: Activity?)
}