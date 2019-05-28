package com.applicaster.cam.ui.auth

import android.content.Context
import android.text.InputType
import android.widget.EditText
import android.widget.LinearLayout
import android.widget.ScrollView
import com.applicaster.cam.R
import com.applicaster.cam.config.ui.UIKey
import com.applicaster.cam.config.ui.UIMapper
import com.applicaster.cam.params.auth.AuthField
import com.applicaster.cam.params.auth.AuthFieldConfig

object InputFieldViewCustomizer {

    private const val MAX_NON_SCROLLABLE_AUTH_FIELDS = 4

    fun populateAuthFields(context: Context, linearParent: LinearLayout, scrollableParent: ScrollView? = null, authFieldConfig: AuthFieldConfig) {
        val etWidth = context.resources.getDimensionPixelSize(R.dimen.auth_et_width)
        val etHeight = context.resources.getDimensionPixelSize(R.dimen.auth_et_height)
        val etMarginTop = context.resources.getDimensionPixelSize(R.dimen.auth_et_margin_top)

        for (field in authFieldConfig.authFields) {
            val editText = EditText(context)
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

    private fun EditText.applyCustomizations(
            etWidth: Int,
            etHeight: Int,
            etMarginTop: Int,
            field: AuthField
    ) {
        layoutParams = LinearLayout.LayoutParams(
                etWidth,
                etHeight
        ).apply {
            topMargin = etMarginTop

        }
        tag = field
        val paddingHorizontal = resources.getDimensionPixelSize(R.dimen.auth_et_padding_horizontal)
        setPadding(paddingHorizontal, 0, paddingHorizontal, 0)
        UIMapper.map(this, UIKey.AUTH_INPUT_FIELD)
        inputType = when (field.type) {
            AuthField.Type.TEXT -> InputType.TYPE_CLASS_TEXT
            AuthField.Type.PASSWORD -> (InputType.TYPE_CLASS_TEXT or InputType.TYPE_TEXT_VARIATION_PASSWORD)
            AuthField.Type.NUMBER -> InputType.TYPE_CLASS_NUMBER
            else -> InputType.TYPE_CLASS_TEXT
        }
        hint = field.hint
    }
}