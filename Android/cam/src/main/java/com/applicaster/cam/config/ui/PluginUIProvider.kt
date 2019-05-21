package com.applicaster.cam.config.ui

import android.content.Context
import android.graphics.Color
import android.graphics.Typeface
import android.graphics.drawable.Drawable
import android.os.Build
import android.util.Log
import com.applicaster.app.CustomApplication
import com.applicaster.cam.R
import com.applicaster.util.OSUtil
import com.applicaster.util.StringUtil

class PluginUIProvider(
    private val pluginConfig: Map<String, String>,
    private val context: Context
) : UIProvider {

    override fun getText(key: String): String {
        return let {
            if (pluginConfig.containsKey(key)) {
                pluginConfig[key] ?: context.getString(R.string.default_text)
            } else {
                context.getString(R.string.default_text)
            }
        }
    }

    override fun getColor(key: String): Int {
        /**
         *  TODO: get values from [OSUtil] or pluginConfig
         */
        return Color.BLACK
    }

    override fun getTextSize(key: String): Float {
        return let {
            if (pluginConfig.containsKey(key)) {
                pluginConfig[key]?.toFloat() ?: context.resources.getDimension(R.dimen.default_text_size)
            } else {
                context.resources.getDimension(R.dimen.default_text_size)
            }
        }
    }

    override fun getDrawable(key: String): Drawable {
        val drawableId = OSUtil.getDrawableResourceIdentifier(key)
        return if (drawableId != 0) {
            if (Build.VERSION.SDK_INT >= Build.VERSION_CODES.M)
                context.resources.getDrawable(drawableId, context.theme)
             else
                context.resources.getDrawable(drawableId)
        } else {
            if (Build.VERSION.SDK_INT >= Build.VERSION_CODES.M)
                context.resources.getDrawable(R.drawable.btn_dummy, context.theme)
            else
                context.resources.getDrawable(R.drawable.btn_dummy)
        }
    }

    override fun getFont(key: String): Typeface {
        if (StringUtil.isNotEmpty(key)) {
            try {
                val firstSuffix = ".otf"
                val secondSuffix = ".ttf"
                var customFontTypeface = Typeface.createFromAsset(
                    CustomApplication.getAppContext().assets,
                    "fonts/$key$firstSuffix"
                )

                if (customFontTypeface == null) {
                    customFontTypeface = Typeface.createFromAsset(
                        CustomApplication.getAppContext().assets,
                        "fonts/$key$secondSuffix"
                    )
                }
                return customFontTypeface
            } catch (e: Exception) {
                Log.d("", "")
            }
        }
        return Typeface.DEFAULT
    }
}