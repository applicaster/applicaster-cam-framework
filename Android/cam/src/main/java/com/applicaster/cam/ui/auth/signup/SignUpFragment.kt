package com.applicaster.cam.ui.auth.signup

import com.applicaster.cam.config.ui.UIKey
import com.applicaster.cam.config.ui.UIMapper
import com.applicaster.cam.ui.CamNavigationRouter
import com.applicaster.cam.ui.auth.AuthFragment
import com.applicaster.cam.ui.auth.AuthPresenter
import com.applicaster.cam.ui.auth.IAuthPresenter
import kotlinx.android.synthetic.main.fragment_auth.*
import kotlinx.android.synthetic.main.layout_auth_buttons.*

class SignUpFragment : AuthFragment(), ISignUpView {

    private var presenter: IAuthPresenter? = null

    override fun initPresenter(navigationManager: CamNavigationRouter): IAuthPresenter {
        presenter = AuthPresenter(this, navigationManager)
        setPresenter(presenter)
        return presenter as AuthPresenter
    }

    override fun applyUICustomizations() {
        UIMapper.map(tv_logo, UIKey.SIGN_UP_TITLE)
        UIMapper.map(btn_input_action, UIKey.SIGN_UP_BUTTON)
    }
}
