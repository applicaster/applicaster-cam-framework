package com.applicaster.cam.config.ui

import android.graphics.Typeface
import android.graphics.drawable.Drawable
import android.support.annotation.ColorInt

interface UIProvider {
    fun getText(key: String): String
    @ColorInt
    fun getColor(key: String): Int

    fun getDrawable(key: String): Drawable

    fun getFont(key: String) : Typeface

    fun getStyleResId(key: String): Int
}