package com.applicaster.cam.ui.base.custom

import android.view.Gravity
import android.view.View
import android.widget.TextView

class CustomLinkViewCustomizationHelper {
    fun customize(leftLinkView: CustomLinkTextView, rightLinkView: CustomLinkTextView, parentView: View) {
        parentView.visibility = View.VISIBLE
        if (!leftLinkView.isCustomLinkDataNotEmpty() && rightLinkView.isCustomLinkDataNotEmpty()) {
            rightLinkView.gravity = Gravity.CENTER
            leftLinkView.visibility = View.GONE
        } else if (leftLinkView.isCustomLinkDataNotEmpty() && !rightLinkView.isCustomLinkDataNotEmpty()) {
            leftLinkView.gravity = Gravity.CENTER
            rightLinkView.visibility = View.GONE
        } else if (!leftLinkView.isCustomLinkDataNotEmpty() && !rightLinkView.isCustomLinkDataNotEmpty()) {
            parentView.visibility = View.GONE
        } else {
            leftLinkView.gravity = Gravity.END
            rightLinkView.gravity = Gravity.START
            rightLinkView.visibility = View.VISIBLE
            rightLinkView.visibility = View.VISIBLE
        }
    }
}