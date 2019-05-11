package com.applicaster.cam.config.ui

import android.content.Context
import android.graphics.Typeface
import android.graphics.drawable.Drawable
import android.util.Log
import com.applicaster.app.CustomApplication
import com.applicaster.util.StringUtil

class PluginUIProvider(
    private val pluginConfig: Map<String, String>,
    private val context: Context
) : UIProvider {

    override fun getText(key: String): String {
        /**
         *  TODO: get values from [OSUtil] or pluginConfig
         */
        return ""
    }

    override fun getColor(key: String): Int {
        TODO("not implemented") //To change body of created functions use File | Settings | File Templates.
    }

    override fun getTextSize(key: String): Float {
        TODO("not implemented") //To change body of created functions use File | Settings | File Templates.
    }

    override fun getDrawable(key: String): Drawable {
        TODO("not implemented") //To change body of created functions use File | Settings | File Templates.
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