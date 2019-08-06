package com.applicaster.cam.config.ui

import android.content.Context
import android.graphics.Color
import android.graphics.drawable.Drawable
import android.os.Build
import com.applicaster.app.CustomApplication
import com.applicaster.cam.R
import com.applicaster.util.OSUtil

class PluginUIProvider(
    private val pluginConfig: Map<String, String>,
    private val context: Context
) : UIProvider {

    override fun getText(key: String): String {
        return let {
            if (pluginConfig.containsKey(key)) {
                pluginConfig[key].orEmpty()
            } else {
                ""
            }
        }
    }

    override fun getColor(key: String): Int {
        return let {
            if (pluginConfig.containsKey(key)) {
                Color.parseColor(pluginConfig[key])
            } else {
                Color.BLACK
            }
        }
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

    override fun getFontName(key: String): String {
        return let {
            if (pluginConfig.containsKey(key)) {
               pluginConfig[key].orEmpty()
            } else {
                ""
            }
        }
    }

    @Suppress("DEPRECATION")
    override fun getDrawable(key: String): Drawable {
        val drawableId = OSUtil.getDrawableResourceIdentifier(key)
        return if (drawableId != 0) {
            if (Build.VERSION.SDK_INT >= Build.VERSION_CODES.M)
                context.resources.getDrawable(drawableId, context.theme)
            else
                context.resources.getDrawable(drawableId)
        } else {
            if (Build.VERSION.SDK_INT >= Build.VERSION_CODES.M)
                context.resources.getDrawable(R.drawable.dummy_drawable, context.theme)
            else
                context.resources.getDrawable(R.drawable.dummy_drawable)
        }
    }

    override fun getStyleResId(key: String): Int {
        val styleResId = OSUtil.getStyleResourceIdentifier(key)
        return if (styleResId != 0) {
            styleResId
        } else {
            OSUtil.getStyleResourceIdentifier("DefaultTextStyle")
        }
    }
}