package com.applicaster.cam.ui.signup

import android.os.Bundle
import android.view.LayoutInflater
import android.view.View
import android.view.ViewGroup
import com.applicaster.cam.R
import com.applicaster.cam.ui.CamNavigationRouter
import com.applicaster.cam.ui.base.view.BaseFragment
import kotlinx.android.synthetic.main.layout_auth_input.*
import kotlinx.android.synthetic.main.layout_bottom_bar.*
import kotlinx.android.synthetic.main.layout_text_with_action.*
import kotlinx.android.synthetic.main.layout_toolbar_template.*

class SignUpFragment : BaseFragment(), ISignUpView {

    private var presenter: ISignUpPresenter? = null

    override fun onCreateView(
        inflater: LayoutInflater, container: ViewGroup?,
        savedInstanceState: Bundle?
    ): View? {
        val navigationManager = if (baseActivity.getNavigationRouter() is CamNavigationRouter)
            baseActivity.getNavigationRouter() as CamNavigationRouter
        else
            CamNavigationRouter(baseActivity)

        presenter = SignUpPresenter(this, navigationManager)
        setPresenter(presenter)
        return inflater.inflate(R.layout.fragment_sign_up, container, false)
    }

    override fun onViewCreated(view: View, savedInstanceState: Bundle?) {
        setListeners()
        super.onViewCreated(view, savedInstanceState)
    }

    override fun setListeners() {
        tv_forgot_pwd.setOnClickListener { presenter?.onForgotPasswordClicked() }
        btn_input_action.setOnClickListener { presenter?.onSignUpButtonClicked() }
        tv_hint_desc.setOnClickListener { presenter?.onLogInHintClicked() }
        tv_hint_action.setOnClickListener { presenter?.onLogInHintClicked() }
        tv_bottom_bar_desc.setOnClickListener { presenter?.onRestoreClicked() }
        tv_bottom_bar_action.setOnClickListener { presenter?.onRestoreClicked() }
        toolbar_back_button.setOnClickListener { presenter?.onToolbarBackClicked() }
        toolbar_close_button.setOnClickListener { presenter?.onToolbarCloseClicked() }
    }

    override fun goBack() {
        activity?.onBackPressed()
    }

    override fun close() {
        activity?.finish()
    }
}
