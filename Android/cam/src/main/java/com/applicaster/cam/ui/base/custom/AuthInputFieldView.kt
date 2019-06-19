package com.applicaster.cam.ui.base.custom

import android.content.Context
import android.text.Editable
import android.text.InputType
import android.text.TextWatcher
import android.view.MotionEvent
import android.view.View
import android.widget.EditText
import android.widget.LinearLayout
import com.applicaster.cam.ContentAccessManager
import com.applicaster.cam.R
import com.applicaster.cam.config.ui.PluginUIProvider
import com.applicaster.cam.config.ui.UIKey
import com.applicaster.cam.config.ui.UIMapper
import com.applicaster.cam.config.ui.UI_KEY_INPUT_ERROR_IMAGE
import com.applicaster.cam.params.auth.AuthField

class AuthInputFieldView(context: Context, var authField: AuthField, listener: InputFieldViewListener) :
    EditText(context) {

    private var errorMsg: String? = null

    init {
        setOnTouchListener(object : DrawableOnTouchListener() {
            override fun onDrawableTouch(event: MotionEvent): Boolean {
                listener.onErrorIconClicked(this@AuthInputFieldView, errorMsg ?: "Error")
                return true
            }
        })
        addTextChangedListener(object : TextWatcher {
            override fun afterTextChanged(s: Editable?) {
            }

            override fun beforeTextChanged(s: CharSequence?, start: Int, count: Int, after: Int) {
            }

            override fun onTextChanged(s: CharSequence?, start: Int, before: Int, count: Int) {
                clearErrorState()
            }
        })
    }

    fun showError(errorMsg: String) {
        this.errorMsg = errorMsg

        setCompoundDrawablesRelativeWithIntrinsicBounds(
            null,
            null,
            ContentAccessManager.pluginUIProvider.getDrawable(UI_KEY_INPUT_ERROR_IMAGE),
            null
        )
    }

    fun clearErrorState() {
        if (errorMsg != null) {
            errorMsg = null
            setCompoundDrawablesRelativeWithIntrinsicBounds(
                null,
                null,
                null,
                null
            )
        }
    }

    fun applyCustomizations(
        etWidth: Int,
        etHeight: Int,
        etMarginTop: Int,
        field: AuthField
    ) {
        layoutParams = LinearLayout.LayoutParams(
            etWidth,
            etHeight
        ).apply {
            topMargin = etMarginTop

        }
        tag = field
        val paddingHorizontal = resources.getDimensionPixelSize(R.dimen.auth_et_padding_horizontal)
        setPadding(paddingHorizontal, 0, paddingHorizontal, 0)
        inputType = when (field.type) {
            AuthField.Type.TEXT -> InputType.TYPE_CLASS_TEXT
            AuthField.Type.PASSWORD -> (InputType.TYPE_CLASS_TEXT or InputType.TYPE_TEXT_VARIATION_PASSWORD)
            AuthField.Type.NUMBER -> InputType.TYPE_CLASS_NUMBER
            else -> InputType.TYPE_CLASS_TEXT
        }
        UIMapper.map(this, UIKey.AUTH_INPUT_FIELD)
        hint = field.hint
    }

}

interface InputFieldViewListener {
    fun onErrorIconClicked(rootView: View, errorMsg: String)
}