package com.applicaster.cam.ui.base.custom

import android.view.Gravity
import android.view.View
import android.widget.TextView

class CustomLinkViewCustomizationHelper {
    fun customize(leftLinkView: TextView, rightLinkView: TextView) {
        if (leftLinkView.text.isEmpty() && rightLinkView.text.isNotEmpty()) {
            rightLinkView.gravity = Gravity.CENTER
            leftLinkView.visibility = View.GONE
        } else if (leftLinkView.text.isNotEmpty() && rightLinkView.text.isEmpty()) {
            leftLinkView.gravity = Gravity.CENTER
            rightLinkView.visibility = View.GONE
        } else {
            leftLinkView.gravity = Gravity.END
            rightLinkView.gravity = Gravity.START
            rightLinkView.visibility = View.VISIBLE
            rightLinkView.visibility = View.VISIBLE
        }
    }
}