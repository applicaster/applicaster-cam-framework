package com.applicaster.cam.config.ui

import android.graphics.Color
import android.graphics.Typeface
import androidx.annotation.ColorInt
import android.text.SpannableStringBuilder
import android.text.TextPaint
import android.text.TextUtils
import android.text.method.LinkMovementMethod
import android.text.style.ClickableSpan
import android.view.View
import android.view.ViewGroup
import android.widget.Button
import android.widget.EditText
import android.widget.ImageView
import android.widget.TextView
import com.applicaster.cam.ContentAccessManager
import com.applicaster.cam.ui.base.custom.CustomLinkTextView
import com.applicaster.cam.ui.base.presenter.ICustomLinkActionHandler
import com.applicaster.util.OSUtil
import com.applicaster.util.TextUtil


class UIMapper {
    companion object {
        private val uiProvider: UIProvider = ContentAccessManager.pluginUIProvider

        fun map(view: View, key: UIKey) {
            key.text?.let { if (it.isNotEmpty()) setText(view, it) }
            key.image?.let { if (it.isNotEmpty()) setImage(view, it) }
            key.textStyle?.let { setTextStyle(view, it) }
        }

        fun map(view: View, key: UIKey, linkActionCallback: () -> Unit) {
            if (key.text != null && key.text.isNotEmpty() && key.textLink != null) {
                customizeTextWithLink(key.text, key.textLink, key, linkActionCallback, view)
            }
        }

        fun map(view: View, key: UIKey, listener: ICustomLinkActionHandler) {
            map(view, key)
            if (view is CustomLinkTextView) {
                val linkText = uiProvider.getText(key.text.orEmpty())
                val linkUrl = uiProvider.getText(key.textLink.orEmpty())
                view.customizeWithLinkData(linkText, linkUrl)
                view.setClickListener(listener)
            }
        }

        private fun customizeTextWithLink(text: String, textLink: String, key: UIKey, linkActionCallback: () -> Unit, view: View) {
            val textParamsHolder = TextParamsHolder.build {
                this.text = uiProvider.getText(text)
                this.textLink = uiProvider.getText(textLink)
                this.textStyle = key.textStyle
                this.textLinkStyle = key.textLinkStyle
                this.linkActionCallback = linkActionCallback
            }
            customizeSpannableText(view, textParamsHolder)
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

        private fun customizeSpannableText(view: View, textParamsHolder: TextParamsHolder) {
            if (view is TextView) {
                val spanText = SpannableStringBuilder()
                spanText.append(textParamsHolder.text)
                //space symbol to prevent sticking two text lines together
                //if first part of text doesn't contain last 'space' symbol
                //or second part of text doesn't contain first 'space' symbol
                val textSeparator = ' '
                textParamsHolder.text?.let {
                    if (it.isNotEmpty() && it.last() != textSeparator) {
                        if (!TextUtils.isEmpty(textParamsHolder.textLink) && textParamsHolder.textLink?.first() != textSeparator)
                            spanText.append(textSeparator)
                    }
                }
                //apply text style to view
                textParamsHolder.textStyle?.let { setTextStyle(view, it) }
                spanText.append(textParamsHolder.textLink)
                spanText.setSpan(object : ClickableSpan() {
                    override fun onClick(widget: View) {
                        //call function to perform click action
                        textParamsHolder.linkActionCallback()
                    }

                    override fun updateDrawState(textPaint: TextPaint) {
                        //apply text style only for text link
                        val fontName: String = uiProvider.getFontName(textParamsHolder.textLinkStyle?.getFontName().orEmpty())
                        val typeface: Typeface? = TextUtil.getTypefaceFromFontKey(fontName)
                        typeface?.let { textPaint.typeface = it }
                        textPaint.color = uiProvider.getColor(
                                textParamsHolder.textLinkStyle?.getHexColor()
                                        ?: Color.WHITE.toString()
                        )
                        textPaint.isUnderlineText = true
                    }
                }, spanText.length - (textParamsHolder.textLink?.length ?: 0), spanText.length, 0)
                view.movementMethod = LinkMovementMethod.getInstance()
                view.setText(spanText, TextView.BufferType.SPANNABLE)
                view.highlightColor = Color.TRANSPARENT
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

private class TextParamsHolder(
        val text: String?,
        val textLink: String?,
        val textStyle: StyleKey?,
        val textLinkStyle: StyleKey?,
        val linkActionCallback: () -> Unit
) {

    private constructor(builder: Builder) :
            this(builder.text, builder.textLink, builder.textStyle, builder.textLinkStyle, builder.linkActionCallback)

    companion object {
        inline fun build(block: Builder.() -> Unit) = Builder().apply(block).build()
    }

    class Builder {
        var text: String? = null
        var textLink: String? = null
        var textStyle: StyleKey? = null
        var textLinkStyle: StyleKey? = null
        var linkActionCallback: () -> Unit = {}

        fun build() = TextParamsHolder(this)
    }
}