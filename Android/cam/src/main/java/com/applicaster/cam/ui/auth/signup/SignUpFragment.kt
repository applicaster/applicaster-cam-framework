package com.applicaster.cam.ui.auth.signup

import android.view.View
import com.applicaster.cam.config.ui.UIKey
import com.applicaster.cam.config.ui.UIMapper
import com.applicaster.cam.ui.CamNavigationRouter
import com.applicaster.cam.ui.auth.AuthFragment
import com.applicaster.cam.ui.auth.AuthPresenter
import com.applicaster.cam.ui.auth.IAuthPresenter
import kotlinx.android.synthetic.main.fragment_auth.*
import kotlinx.android.synthetic.main.layout_additional_auth.*
import kotlinx.android.synthetic.main.layout_auth_input.*
import kotlinx.android.synthetic.main.layout_text_with_action.*

class SignUpFragment : AuthFragment(), ISignUpView {

    private var presenter: ISignUpPresenter? = null

    override fun initPresenter(navigationManager: CamNavigationRouter): IAuthPresenter {
        presenter = SignUpPresenter(this, navigationManager)
        setPresenter(presenter)
        return presenter as AuthPresenter
    }

    override fun applyUICustomizations() {
        super.applyUICustomizations()
        tv_forgot_pwd.visibility = View.GONE
        UIMapper.map(tv_logo, UIKey.SIGN_UP_TITLE)
        UIMapper.map(btn_input_action, UIKey.SIGN_UP_BUTTON)
        UIMapper.map(tv_add_auth_or, UIKey.SEPARATOR_TEXT)
        UIMapper.map(tv_add_auth_desc, UIKey.SIGN_UP_ALT_AUTH_TEXT)
        UIMapper.map(tv_hint_desc, UIKey.SIGN_UP_PROMPT_TEXT)
        UIMapper.map(tv_hint_action, UIKey.SIGN_UP_PROMPT_ACTION_TEXT)
    }
}