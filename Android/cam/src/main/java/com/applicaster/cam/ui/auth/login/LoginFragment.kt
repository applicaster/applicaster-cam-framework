package com.applicaster.cam.ui.auth.login

import android.view.View
import com.applicaster.cam.config.ui.UIKey
import com.applicaster.cam.config.ui.UIMapper
import com.applicaster.cam.ui.CamNavigationRouter
import com.applicaster.cam.ui.auth.AuthFragment
import com.applicaster.cam.ui.auth.IAuthPresenter
import kotlinx.android.synthetic.main.fragment_auth.*
import kotlinx.android.synthetic.main.layout_additional_auth.*
import kotlinx.android.synthetic.main.layout_auth_input.*

class LoginFragment : AuthFragment(), ILoginView {

    private var presenter: ILoginPresenter? = null

    override fun initPresenter(navigationManager: CamNavigationRouter): IAuthPresenter {
        presenter = LoginPresenter(this, navigationManager)
        setPresenter(presenter)
        return presenter as LoginPresenter
    }

    override fun setListeners() {
        tv_forgot_pwd.setOnClickListener { presenter?.onForgotPasswordClicked() }
        super.setListeners()
    }

    override fun applyUICustomizations() {
        super.applyUICustomizations()
        tv_forgot_pwd.visibility = View.VISIBLE
        UIMapper.map(tv_logo, UIKey.LOGIN_TITLE)
        UIMapper.map(tv_forgot_pwd, UIKey.LOGIN_RESET_PWD)
        UIMapper.map(btn_input_action, UIKey.LOGIN_BTN_TEXT)
        UIMapper.map(tv_add_auth_or, UIKey.SEPARATOR_TEXT)
        UIMapper.map(tv_add_auth_desc, UIKey.LOGIN_ALT_AUTH_TEXT)
    }
}