package com.applicaster.cam.ui.auth.password

import android.widget.LinearLayout
import com.applicaster.cam.R
import com.applicaster.cam.config.ui.UIKey
import com.applicaster.cam.config.ui.UIMapper
import com.applicaster.cam.params.auth.AuthFieldConfig
import com.applicaster.cam.ui.auth.base.BaseInputFragment
import com.applicaster.cam.ui.auth.base.IBaseInputView
import kotlinx.android.synthetic.main.fragment_password_reset.*
import kotlinx.android.synthetic.main.layout_toolbar_template.*

abstract class BasePasswordFragment : BaseInputFragment(), IBaseInputView {

    override fun getLayoutId() = R.layout.fragment_password_reset

    override fun setListeners() {
        btn_reset.setOnClickListener { presenter?.onAuthActionButtonClicked(getInputFieldsValues()) }
        toolbar_back_button.setOnClickListener { presenter?.onToolbarBackClicked() }
    }

    override fun customize() {
        super.customize()

        UIMapper.apply {
            map(toolbar_back_button, UIKey.TOOLBAR_BACK_BUTTON)
            map(app_logo, UIKey.TOOLBAR_HEADER_LOGO_IMAGE)
            map(container_reset_password, UIKey.BACKGROUND_IMAGE)
        }
    }

    override fun populateAuthFieldsViews(authFieldConfig: AuthFieldConfig) {
        super.populateAuthFieldsViews(authFieldConfig)
        val scrollableParent = getAuthInputScrollableParent()
        scrollableParent.layoutParams =
            LinearLayout.LayoutParams(LinearLayout.LayoutParams.WRAP_CONTENT, LinearLayout.LayoutParams.MATCH_PARENT)
    }

    override fun getParentView() = container_reset_password

    override fun getAuthInputLinearParent() = container_linear_reset_input

    override fun getAuthInputScrollableParent() = container_scrollable_reset_input

    override fun onLastFragmentClosed() = Unit
}

