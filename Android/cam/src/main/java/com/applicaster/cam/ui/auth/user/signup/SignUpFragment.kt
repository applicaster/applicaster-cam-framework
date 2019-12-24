package com.applicaster.cam.ui.auth.user.signup

import android.view.View
import com.applicaster.cam.config.ui.UIKey
import com.applicaster.cam.config.ui.UIMapper
import com.applicaster.cam.ui.CamNavigationRouter
import com.applicaster.cam.ui.auth.base.IBaseInputPresenter
import com.applicaster.cam.ui.auth.user.UserAuthFragment
import com.applicaster.cam.ui.base.custom.CustomLinkViewCustomizationHelper
import com.applicaster.cam.ui.base.presenter.ICustomLinkActionHandler
import kotlinx.android.synthetic.main.fragment_auth.*
import kotlinx.android.synthetic.main.layout_additional_auth.*
import kotlinx.android.synthetic.main.layout_auth_input.*
import kotlinx.android.synthetic.main.layout_bottom_links.*
import kotlinx.android.synthetic.main.layout_toolbar_template.*

class SignUpFragment : UserAuthFragment(), ISignUpView {

    override fun initPresenter(navigationManager: CamNavigationRouter): IBaseInputPresenter {
        presenter = SignUpPresenter(this, navigationManager)
        setPresenter(presenter)
        return presenter as SignUpPresenter
    }

    override fun customize() {
        super.customize()
        tv_forgot_pwd.visibility = View.GONE
        UIMapper.apply {
            map(tv_auth_title, UIKey.SIGN_UP_TITLE)
            map(btn_input_action, UIKey.SIGN_UP_BUTTON)
            map(tv_add_auth_or, UIKey.AUTH_SEPARATOR_TEXT)
            map(tv_add_auth_desc, UIKey.SIGN_UP_ALT_AUTH_TEXT)
            map(container_auth_hint, UIKey.SIGN_UP_PROMPT_TEXT) { (presenter as? SignUpPresenter)?.onAuthHintClicked() }
            map(tv_bottom_link_1, UIKey.LOGIN_LINK_1_TEXT, presenter as ICustomLinkActionHandler)
            map(tv_bottom_link_2, UIKey.LOGIN_LINK_2_TEXT, presenter as ICustomLinkActionHandler)
        }
        CustomLinkViewCustomizationHelper().customize(tv_bottom_link_1, tv_bottom_link_2)
    }

    override fun initBackButton(enable: Boolean) {
        if (enable) {
            toolbar_back_button.setOnClickListener { presenter?.onToolbarBackClicked() }
        } else {
            toolbar_back_button.visibility = View.GONE
        }
    }

    override fun onLastFragmentClosed() {
        presenter?.onLastFragmentClosed()
    }
}