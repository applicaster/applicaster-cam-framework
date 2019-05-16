package com.applicaster.cam.ui.auth.login

import android.view.View
import com.applicaster.cam.config.ui.UIKey
import com.applicaster.cam.config.ui.UIMapper
import com.applicaster.cam.ui.CamNavigationRouter
import com.applicaster.cam.ui.auth.AuthFragment
import com.applicaster.cam.ui.auth.IAuthPresenter
import kotlinx.android.synthetic.main.fragment_auth.*

class LoginFragment : AuthFragment(), ILoginView {

    private var presenter: ILoginPresenter? = null

    override fun initPresenter(navigationManager: CamNavigationRouter): IAuthPresenter {
        presenter = LoginPresenter(this, navigationManager)
        setPresenter(presenter)
        return presenter as LoginPresenter
    }

    override fun applyUICustomizations() {
        tv_forgot_pwd.visibility = View.VISIBLE
        UIMapper.map(tv_logo, UIKey.SIGN_UP_TITLE)
        UIMapper.map(btn_input_action, UIKey.SIGN_UP_BUTTON)
    }

    override fun setListeners() {
        tv_forgot_pwd.setOnClickListener { presenter?.onForgotPasswordClicked() }
        super.setListeners()
    }
}
