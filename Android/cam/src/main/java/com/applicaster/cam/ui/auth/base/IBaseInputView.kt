package com.applicaster.cam.ui.auth.base

import android.view.View
import com.applicaster.cam.params.auth.AuthField
import com.applicaster.cam.params.auth.AuthFieldConfig
import com.applicaster.cam.ui.base.view.IBaseView

interface IBaseInputView : IBaseView {
    fun getInputFieldsValues(): HashMap<AuthField, String>
    fun populateAuthFieldsViews(authFieldConfig: AuthFieldConfig)
    fun showAuthInputFieldErrorIcons(inputFieldValidationErrors: HashMap<AuthField, String>)
    fun showErrorPopup(rootView: View, errorMsg: String)
}