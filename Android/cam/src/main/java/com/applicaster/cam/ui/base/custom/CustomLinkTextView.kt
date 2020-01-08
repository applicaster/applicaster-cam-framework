package com.applicaster.cam.ui.base.custom

import android.content.Context
import android.text.TextUtils
import android.util.AttributeSet
import com.applicaster.cam.ui.base.presenter.ICustomLinkActionHandler
import com.applicaster.util.ui.CustomTextView

class CustomLinkTextView : CustomTextView {

    private var customLinkText: String? = null
    private var customLinkUrl: String? = null

    constructor(context: Context) : super(context)

    constructor(context: Context?, attrs: AttributeSet?) : super(context, attrs)

    fun customizeWithLinkData(customLinkText: String, customLinkUrl: String) {
        this.customLinkText = customLinkText
        this.customLinkUrl = customLinkUrl
    }

    fun setClickListener(actionHandler: ICustomLinkActionHandler) {
        setOnClickListener { actionHandler.onCustomLinkClicked(customLinkText.orEmpty(), customLinkUrl.orEmpty()) }
    }

    fun isCustomLinkDataNotEmpty(): Boolean = !TextUtils.isEmpty(customLinkText) && !TextUtils.isEmpty(customLinkUrl)
}