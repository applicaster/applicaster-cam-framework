package com.applicaster.cam.ui.auth.password.reset

import android.os.Bundle
import android.view.LayoutInflater
import android.view.View
import android.view.ViewGroup
import android.widget.EditText
import com.applicaster.cam.R
import com.applicaster.cam.config.ui.UIKey
import com.applicaster.cam.config.ui.UIMapper
import com.applicaster.cam.params.auth.AuthField
import com.applicaster.cam.params.auth.AuthFieldConfig
import com.applicaster.cam.ui.CamNavigationRouter
import com.applicaster.cam.ui.auth.InputFieldViewCustomizer
import com.applicaster.cam.ui.base.view.BaseFragment
import kotlinx.android.synthetic.main.fragment_password_reset.*
import kotlinx.android.synthetic.main.layout_toolbar_template.*

class PasswordResetFragment : BaseFragment(), IPasswordResetView {
    private var presenter: IPasswordResetPresenter? = null

    override fun onCreateView(
            inflater: LayoutInflater, container: ViewGroup?,
            savedInstanceState: Bundle?
    ): View? {
        val rootView = inflater.inflate(R.layout.fragment_password_reset, container, false)

        val navigationManager = if (baseActivity.getNavigationRouter() is CamNavigationRouter)
            baseActivity.getNavigationRouter() as CamNavigationRouter
        else
            CamNavigationRouter(baseActivity)
        presenter = PasswordResetPresenter(this, navigationManager)
        setPresenter(presenter)

        return rootView
    }

    override fun onViewCreated(view: View, savedInstanceState: Bundle?) {
        super.onViewCreated(view, savedInstanceState)
        setListeners()
    }

    override fun setListeners() {
        btn_reset.setOnClickListener { presenter?.onResetButtonClicked(getInputFieldsValues()) }
        toolbar_back_button.setOnClickListener { presenter?.onToolbarBackClicked() }
        toolbar_close_button.setOnClickListener { presenter?.onToolbarCloseClicked() }
    }

    override fun customize() {
        super.customize()

        UIMapper.apply {
            map(toolbar_back_button, UIKey.TOOLBAR_BACK_BUTTON)
            map(toolbar_close_button, UIKey.TOOLBAR_CLOSE_BUTTON)
            map(app_logo, UIKey.TOOLBAR_HEADER_LOGO_IMAGE)
            map(container_reset_password, UIKey.BACKGROUND_IMAGE)

            map(tv_reset_title, UIKey.PASSWORD_RESET_TITLE_TEXT)
            map(tv_reset_title_desc, UIKey.PASSWORD_RESET_DESC_TEXT)
            map(btn_reset, UIKey.PASSWORD_RESET_ACTION_BUTTON)
        }
    }

    override fun getParentView() = container_reset_password

    override fun populateAuthFieldsViews(authFieldConfig: AuthFieldConfig) {
        context?.apply {
            InputFieldViewCustomizer.populateAuthFields(
                    this,
                    linearParent = container_linear_reset_input,
                    authFieldConfig = authFieldConfig
            )
        }
    }

    private fun getInputFieldsValues(): HashMap<String, String> {
        val inputValues = HashMap<String, String>()
        for (i in 0 until container_linear_reset_input.childCount) {
            val child = container_linear_reset_input.getChildAt(i) as? EditText
            if (child != null)
                inputValues[(child.tag as AuthField).key!!] = child.text.toString()
        }
        return inputValues
    }
}

