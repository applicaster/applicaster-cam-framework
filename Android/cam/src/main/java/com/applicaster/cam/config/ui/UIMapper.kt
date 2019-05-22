package com.applicaster.cam.config.ui

import android.os.Build
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
        if (!key.textStyle.isNullOrEmpty()) {
            setTextStyle(view, key.textStyle)
        }
        if (!key.image.isNullOrEmpty()) {
            setImage(view, key.image)
        }
    }

    private fun setImage(view: View, key: String) {
        when (view) {
            is ImageView -> view.background = uiProvider.getDrawable(key)
            is Button -> view.background = uiProvider.getDrawable(key)
            is EditText -> view.background = uiProvider.getDrawable(key)
            is ViewGroup -> view.background = uiProvider.getDrawable(key)
        }
    }

    private fun setText(view: View, key: String) {
        when (view) {
            is TextView -> view.text = uiProvider.getText(key)
            is EditText -> view.text = SpannableStringBuilder(uiProvider.getText(key))
        }
    }

    private fun setHint(view: View, key: String) {
        when (view) {
            is EditText -> view.hint = uiProvider.getText(key)
        }
    }

    private fun setTextStyle(view: View, key: String) {
        when (view) {
            is TextView -> {
                if (Build.VERSION.SDK_INT >= Build.VERSION_CODES.M)
                    view.setTextAppearance(uiProvider.getStyleResId(key))
                else
                    view.setTextAppearance(view.context, uiProvider.getStyleResId(key))
            }
            is EditText -> {
                if (Build.VERSION.SDK_INT >= Build.VERSION_CODES.M)
                    view.setTextAppearance(uiProvider.getStyleResId(key))
                else
                    view.setTextAppearance(view.context, uiProvider.getStyleResId(key))
            }
        }
    }

    private val uiProvider: UIProvider by lazy { ContentAccessManager.pluginUIProvider }
}