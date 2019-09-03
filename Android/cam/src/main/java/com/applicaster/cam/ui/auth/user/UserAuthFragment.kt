package com.applicaster.cam.ui.auth.user

import android.view.View
import com.applicaster.cam.ContentAccessManager
import com.applicaster.cam.R
import com.applicaster.cam.config.ui.UIKey
import com.applicaster.cam.config.ui.UIMapper
import com.applicaster.cam.ui.auth.base.BaseInputFragment
import kotlinx.android.synthetic.main.fragment_auth.*
import kotlinx.android.synthetic.main.layout_additional_auth.*
import kotlinx.android.synthetic.main.layout_auth_input.*
import kotlinx.android.synthetic.main.layout_bottom_bar.*
import kotlinx.android.synthetic.main.layout_text_with_action.*
import kotlinx.android.synthetic.main.layout_toolbar_template.*

abstract class UserAuthFragment : BaseInputFragment() {

    override fun setListeners() {
        val presenter = presenter as? IUserAuthPresenter
        btn_input_action.setOnClickListener { presenter?.onAuthActionButtonClicked(getInputFieldsValues()) }
        tv_hint_desc.setOnClickListener { presenter?.onAuthHintClicked() }
        tv_hint_action.setOnClickListener { presenter?.onAuthHintClicked() }
        tv_bottom_bar_desc.setOnClickListener { presenter?.onRestoreClicked() }
        tv_bottom_bar_action.setOnClickListener { presenter?.onRestoreClicked() }
        iv_facebook_auth.setOnClickListener { presenter?.onFacebookButtonClicked(activity) }
    }

    override fun customize() {
        super.customize()

        container_additional_auth?.apply {
            visibility =
                if (ContentAccessManager.pluginConfigurator.isFacebookLoginRequired()) View.VISIBLE else View.GONE
        }
        container_bottom_bar?.apply {
            visibility =
                if (ContentAccessManager.pluginConfigurator.isAuthRestoreRequired()) View.VISIBLE else View.GONE
        }

        UIMapper.apply {
            map(toolbar_back_button, UIKey.TOOLBAR_BACK_BUTTON)
            map(app_logo, UIKey.TOOLBAR_HEADER_LOGO_IMAGE)
            map(container_parent_auth, UIKey.BACKGROUND_IMAGE)
            map(iv_facebook_auth, UIKey.AUTH_FACEBOOK_IMAGE)
            map(iv_left_divider, UIKey.AUTH_LEFT_DIVIDER_IMAGE)
            map(iv_right_divider, UIKey.AUTH_RIGHT_DIVIDER_IMAGE)
        }
    }

    override fun getLayoutId() = R.layout.fragment_auth
    override fun getAuthInputLinearParent() = container_linear_input
    override fun getAuthInputScrollableParent() = container_scrollable_input
    override fun getParentView() = container_parent_auth
}