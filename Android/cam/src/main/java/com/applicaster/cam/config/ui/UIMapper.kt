package com.applicaster.cam.config.ui

import android.text.SpannableStringBuilder
import android.view.View
import android.view.ViewGroup
import android.widget.Button
import android.widget.EditText
import android.widget.ImageView
import android.widget.TextView
import com.applicaster.cam.ContentAccessManager

object UIMapper {

    fun map(view: View, key: UIKey) {
        if (!key.text.isNullOrEmpty()) {
            setText(view, key.text)
        }
        if (!key.hint.isNullOrEmpty()) {
            setHint(view, key.hint)
        }
        if (!key.textSize.isNullOrEmpty()) {
            setTextSize(view, key.textSize)
        }
        if (!key.textColor.isNullOrEmpty()) {
            setTextColor(view, key.textColor)
        }
        if (!key.font.isNullOrEmpty()) {
            setFont(view, key.font)
        }
        if (!key.image.isNullOrEmpty()) {
            setImage(view, key.image)
        }
    }

    private fun setImage(view: View, key: String) {
        when (view) {
            is ImageView -> view.background = uiProvider().getDrawable(key)
            is Button -> view.background = uiProvider().getDrawable(key)
            is ViewGroup -> view.background = uiProvider().getDrawable(key)
        }
    }

    private fun setText(view: View, key: String) {
        when (view) {
            is TextView -> view.text = uiProvider().getText(key)
            is EditText -> view.text = SpannableStringBuilder(uiProvider().getText(key))
        }
    }

    private fun setHint(view: View, key: String) {
        when (view) {
            is EditText -> view.hint = uiProvider().getText(key)
        }
    }

    private fun setTextSize(view: View, key: String) {
        when (view) {
            is TextView -> view.textSize = uiProvider().getTextSize(key)
            is EditText -> view.textSize = uiProvider().getTextSize(key)
        }
    }

    private fun setTextColor(view: View, key: String) {
        when (view) {
            is TextView -> view.setTextColor(uiProvider().getColor(key))
            is EditText -> view.setTextColor(uiProvider().getColor(key))
        }
    }

    private fun setFont(view: View, key: String) {
        when (view) {
            is TextView -> view.typeface = uiProvider().getFont(key)
            is EditText -> view.typeface = uiProvider().getFont(key)
        }
    }

    private fun uiProvider() = ContentAccessManager.pluginUIProvider
}