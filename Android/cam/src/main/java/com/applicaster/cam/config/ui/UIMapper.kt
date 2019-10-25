package com.applicaster.cam.config.ui

import android.text.SpannableStringBuilder
import android.view.View
import android.view.ViewGroup
import android.widget.Button
import android.widget.EditText
import android.widget.ImageView
import android.widget.TextView
import com.applicaster.cam.ContentAccessManager
import com.applicaster.util.OSUtil
import com.applicaster.util.TextUtil

class UIMapper {
    companion object {
        private val uiProvider: UIProvider = ContentAccessManager.pluginUIProvider

        fun map(view: View, key: UIKey) {
            if (!key.text.isNullOrEmpty()) {
                setText(view, key.text!!)
            }
            if (key.textStyle != null) {
                setTextStyle(view, key.textStyle)
            }
            if (!key.image.isNullOrEmpty()) {
                setImage(view, key.image!!)
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
            if (!OSUtil.isTablet()) {
                view.textSize = uiProvider.getTextSize(styleKey.getTextSizePhone())
            } else {
                view.textSize = uiProvider.getTextSize(styleKey.getTextSizeTablet())
            }

            //customize font
            val fontName = uiProvider.getFontName(styleKey.getFontName())
            if (fontName.isNotEmpty())
                TextUtil.setTextFont(view, fontName)
        }
    }
}