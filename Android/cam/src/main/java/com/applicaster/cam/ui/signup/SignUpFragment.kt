package com.applicaster.cam.ui.signup

import android.os.Bundle
import android.text.InputType
import android.view.LayoutInflater
import android.view.View
import android.view.ViewGroup
import android.widget.EditText
import android.widget.LinearLayout
import com.applicaster.cam.R
import com.applicaster.cam.config.ui.UIKey
import com.applicaster.cam.config.ui.UIMapper
import com.applicaster.cam.params.auth.AuthField
import com.applicaster.cam.params.auth.AuthFieldConfig
import com.applicaster.cam.ui.CamNavigationRouter
import com.applicaster.cam.ui.base.view.BaseFragment
import kotlinx.android.synthetic.main.fragment_sign_up.*
import kotlinx.android.synthetic.main.layout_auth_buttons.*
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
        super.onViewCreated(view, savedInstanceState)
        setListeners()
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

    override fun populateAuthFieldsViews(authFieldConfig: AuthFieldConfig) {
        val etWidth = resources.getDimensionPixelSize(R.dimen.auth_et_width)
        val etHeight = resources.getDimensionPixelSize(R.dimen.auth_et_height)
        val etMarginTop = resources.getDimensionPixelSize(R.dimen.auth_et_top_margin)

        for (field in authFieldConfig.authFields) {
            val editText = EditText(context)
            editText.layoutParams = LinearLayout.LayoutParams(
                    etWidth,
                    etHeight
            ).apply {
                topMargin = etMarginTop
            }
            when (field.type) {
                AuthField.Type.TEXT -> editText.inputType = InputType.TYPE_CLASS_TEXT
                AuthField.Type.PASSWORD -> editText.inputType = (InputType.TYPE_CLASS_TEXT or InputType.TYPE_TEXT_VARIATION_PASSWORD)
                AuthField.Type.NUMBER -> editText.inputType = InputType.TYPE_CLASS_NUMBER
                else -> editText.inputType = InputType.TYPE_CLASS_TEXT
            }
            editText.hint = field.hint
            container_linear_input.addView(editText)
        }
        val visibleViewsCount = if (authFieldConfig.authFields.size < MAX_NON_SCROLLABLE_AUTH_FIELDS)
            authFieldConfig.authFields.size else MAX_NON_SCROLLABLE_AUTH_FIELDS
        val parentMaxHeight = (etHeight + etMarginTop) * visibleViewsCount

        //recalculating scroll view height to match design spec
        container_scrollable_input.layoutParams = container_scrollable_input.layoutParams.apply {
            height = parentMaxHeight
        }
    }

    override fun customize() {
        UIMapper.map(tv_logo, UIKey.SIGN_UP_TITLE)
        UIMapper.map(btn_input_action, UIKey.SIGN_UP_BUTTON)
    }

    override fun goBack() {
        activity?.onBackPressed()
    }

    override fun close() {
        activity?.finish()
    }

    companion object {
        const val MAX_NON_SCROLLABLE_AUTH_FIELDS = 4
    }
}
