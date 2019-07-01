package com.applicaster.cam.config.ui

import android.text.SpannableStringBuilder
import android.view.View
import android.view.ViewGroup
import android.widget.Button
import android.widget.EditText
import android.widget.ImageView
import android.widget.TextView
import com.applicaster.cam.ContentAccessManager
import com.applicaster.util.TextUtil
import com.applicaster.util.ui.APUIUtils

object UIMapper {
    private val uiProvider: UIProvider by lazy { ContentAccessManager.pluginUIProvider }

    fun map(view: View, key: UIKey) {
        if (!key.text.isNullOrEmpty()) {
            setText(view, key.text)
        }
        if (!key.hint.isNullOrEmpty()) {
            setHint(view, key.hint)
        }
        if (key.textStyle != null) {
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
            is TextView -> view.background = uiProvider.getDrawable(key)
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

    private fun setTextStyle(view: View, key: StyleKey) {
        when (view) {
            is TextView -> applyTextStyle(view, key)
            is EditText -> applyTextStyle(view, key)
        }
    }

    private fun applyTextStyle(view: TextView, styleKey: StyleKey) {
        // customize text color
        view.setTextColor(uiProvider.getColor(styleKey.getHexColor()))

        //customize text size
        if (APUIUtils.isPhoneLandscape()) {
            view.textSize = uiProvider.getTextSize(styleKey.getTextSizePhone())
        } else if (APUIUtils.isTabletPortrait()) {
            view.textSize = uiProvider.getTextSize(styleKey.getTextSizeTablet())
        }

        //customize font
        val fontName = uiProvider.getFontName(styleKey.getFontName())
        if (fontName.isNotEmpty())
            TextUtil.setTextFont(view, fontName)
    }
}