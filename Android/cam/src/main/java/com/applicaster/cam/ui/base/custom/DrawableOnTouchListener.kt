package com.applicaster.cam.ui.base.custom

import android.graphics.drawable.Drawable
import android.view.MotionEvent
import android.view.View
import android.view.View.OnTouchListener
import android.widget.EditText

abstract class DrawableOnTouchListener : OnTouchListener {
    private val extendedClickableArea = 30

    override fun onTouch(v: View, event: MotionEvent): Boolean {
        val drawable = getDrawable(v as EditText)
        if (event.action == MotionEvent.ACTION_DOWN && drawable != null) {
            val x = event.x.toInt()
            val y = event.y.toInt()
            val bounds = drawable!!.bounds
            if (x >= v.getRight() - bounds.width() - extendedClickableArea && x <= v.getRight() - v.getPaddingRight() + extendedClickableArea
                && y >= v.getPaddingTop() - extendedClickableArea && y <= v.getHeight() - v.getPaddingBottom() + extendedClickableArea
            ) {
                return onDrawableTouch(event)
            }
        }
        return false
    }

    private fun getDrawable(view: EditText): Drawable? {
        for (drawable in view.compoundDrawables) {
            if (drawable != null)
                return drawable
        }
        return null
    }

    abstract fun onDrawableTouch(event: MotionEvent): Boolean
}