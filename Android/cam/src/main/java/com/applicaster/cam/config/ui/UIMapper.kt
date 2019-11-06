package com.applicaster.cam.config.ui

import android.support.annotation.ColorInt
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
            val hintColor = obtainHintColor(uiProvider.getColor(styleKey.getHexColor()))
            view.setHintTextColor(hintColor)

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

        //customize hint color(it makes alpha channel 60% from current value)
        @ColorInt
        private fun obtainHintColor(@ColorInt color: Int): Int {
            val alphaMultiplier = 0.6f
            val alpha = ((color shr 24 and 0xff) / 255.0f) * alphaMultiplier
            val red = (color shr 16 and 0xff) / 255.0f
            val green = (color shr 8 and 0xff) / 255.0f
            val blue = (color and 0xff) / 255.0f
            return argb(alpha, red, green, blue)
        }

        //convert float values to int color
        @ColorInt
        private fun argb(alpha: Float, red: Float, green: Float, blue: Float): Int {
            return (alpha * 255.0f + 0.5f).toInt() shl 24 or
                    ((red * 255.0f + 0.5f).toInt() shl 16) or
                    ((green * 255.0f + 0.5f).toInt() shl 8) or
                    (blue * 255.0f + 0.5f).toInt()
        }
    }
}