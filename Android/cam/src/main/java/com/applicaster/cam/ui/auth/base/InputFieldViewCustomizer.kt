package com.applicaster.cam.ui.auth.base

import android.content.Context
import android.widget.LinearLayout
import android.widget.ScrollView
import com.applicaster.cam.R
import com.applicaster.cam.params.auth.AuthFieldConfig
import com.applicaster.cam.ui.base.custom.AuthInputFieldView
import com.applicaster.cam.ui.base.custom.InputFieldViewListener

class InputFieldViewCustomizer {
    companion object {

        private const val MAX_NON_SCROLLABLE_AUTH_FIELDS = 4

        fun populateAuthFields(
            context: Context,
            linearParent: LinearLayout,
            scrollableParent: ScrollView? = null,
            authFieldConfig: AuthFieldConfig,
            listener: InputFieldViewListener
        ) {
            val etWidth = context.resources.getDimensionPixelSize(R.dimen.auth_et_width)
            val etHeight = context.resources.getDimensionPixelSize(R.dimen.auth_et_height)
            val etMarginTop = context.resources.getDimensionPixelSize(R.dimen.auth_et_margin_top)

            for (field in authFieldConfig.authFields) {
                val editText = AuthInputFieldView(context, field, listener)
                editText.applyCustomizations(etWidth, etHeight, etMarginTop, field)
                linearParent.addView(editText)
            }

            if (scrollableParent != null) {
                val visibleViewsCount =
                    if (authFieldConfig.authFields.size < MAX_NON_SCROLLABLE_AUTH_FIELDS)
                        authFieldConfig.authFields.size else MAX_NON_SCROLLABLE_AUTH_FIELDS
                val parentMaxHeight = (etHeight + etMarginTop) * visibleViewsCount

                //recalculating scroll view height to match design spec
                scrollableParent.layoutParams = scrollableParent.layoutParams.apply {
                    height = parentMaxHeight
                }
            }
        }
    }
}

