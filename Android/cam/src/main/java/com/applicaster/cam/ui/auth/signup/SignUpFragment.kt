package com.applicaster.cam.ui.auth.signup

import android.view.View
import com.applicaster.cam.config.ui.UIKey
import com.applicaster.cam.config.ui.UIMapper
import com.applicaster.cam.ui.CamNavigationRouter
import com.applicaster.cam.ui.auth.AuthFragment
import com.applicaster.cam.ui.auth.AuthPresenter
import com.applicaster.cam.ui.auth.IAuthPresenter
import kotlinx.android.synthetic.main.fragment_auth.*

class SignUpFragment : AuthFragment(), ISignUpView {

    private var presenter: ISignUpPresenter? = null

    override fun initPresenter(navigationManager: CamNavigationRouter): IAuthPresenter {
        presenter = SignUpPresenter(this, navigationManager)
        setPresenter(presenter)
        return presenter as AuthPresenter
    }

    override fun applyUICustomizations() {
        tv_forgot_pwd.visibility = View.GONE
        UIMapper.map(tv_logo, UIKey.SIGN_UP_TITLE)
        UIMapper.map(btn_input_action, UIKey.SIGN_UP_BUTTON)
    }
}