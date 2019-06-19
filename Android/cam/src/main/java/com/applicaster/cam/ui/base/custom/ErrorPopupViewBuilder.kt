package com.applicaster.cam.ui.base.custom

import android.content.Context
import android.view.Gravity
import android.view.LayoutInflater
import android.view.View
import android.widget.PopupWindow
import android.widget.TextView
import com.applicaster.cam.R

class ErrorPopupViewBuilder(var context: Context?, var layoutInflater: LayoutInflater?) {

    fun build(anchorView: View, msg: String) {
        if (context != null && layoutInflater != null) {
            val errorPopupWidth = context!!.resources.getDimensionPixelSize(R.dimen.auth_error_popup_width)
            val errorPopupHeight = context!!.resources.getDimensionPixelSize(R.dimen.auth_error_popup_height)
            val errorTextWidth = context!!.resources.getDimensionPixelSize(R.dimen.auth_error_text_width)
            val popupView = layoutInflater!!.inflate(R.layout.layout_input_validation_popup, null)

            val tvValidationMessage = popupView.findViewById<TextView>(R.id.tv_validation_msg)
            tvValidationMessage.text = msg
            val popupWindow = PopupWindow(
                popupView,
                errorPopupWidth,
                errorPopupHeight
            )
            popupWindow.isFocusable = true
            val location = IntArray(2)
            anchorView.getLocationOnScreen(location)

            popupWindow.showAtLocation(
                anchorView, Gravity.NO_GRAVITY, location[0] -
                        (errorPopupWidth
                                - errorTextWidth) / 2,
                location[1] + anchorView.height
            )
        }
    }
}