package com.applicaster.cam.ui.auth.login

import android.view.View
import com.applicaster.cam.ContentAccessManager
import com.applicaster.cam.config.ui.UIKey
import com.applicaster.cam.config.ui.UIMapper
import com.applicaster.cam.ui.CamNavigationRouter
import com.applicaster.cam.ui.auth.AuthFragment
import com.applicaster.cam.ui.auth.IAuthPresenter
import kotlinx.android.synthetic.main.fragment_auth.*
import kotlinx.android.synthetic.main.layout_additional_auth.*
import kotlinx.android.synthetic.main.layout_auth_input.*
import kotlinx.android.synthetic.main.layout_text_with_action.*

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

    override fun customize() {
        super.customize()
        tv_forgot_pwd?.apply {
            visibility =
                if (ContentAccessManager.pluginConfigurator.isPasswordResetRequired()) View.VISIBLE else View.GONE
        }
        UIMapper.apply {
            map(tv_auth_title, UIKey.LOGIN_TITLE)
            map(tv_forgot_pwd, UIKey.LOGIN_RESET_PWD_TEXT)
            map(btn_input_action, UIKey.LOGIN_BUTTON)
            map(tv_add_auth_or, UIKey.AUTH_SEPARATOR_TEXT)
            map(tv_add_auth_desc, UIKey.LOGIN_ALT_AUTH_TEXT)
            map(tv_hint_desc, UIKey.LOGIN_PROMPT_TEXT)
            map(tv_hint_action, UIKey.LOGIN_PROMPT_ACTION_TEXT)
        }
    }
}