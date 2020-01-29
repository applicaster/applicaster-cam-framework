package com.applicaster.cam.ui.auth.user.activation

import android.os.Bundle
import android.view.ViewGroup
import android.widget.LinearLayout
import android.widget.ScrollView
import com.applicaster.cam.R
import com.applicaster.cam.config.ui.UIKey
import com.applicaster.cam.config.ui.UIMapper
import com.applicaster.cam.params.auth.AuthFieldConfig
import com.applicaster.cam.ui.CamNavigationRouter
import com.applicaster.cam.ui.auth.base.BaseInputFragment
import com.applicaster.cam.ui.auth.base.IBaseInputPresenter
import kotlinx.android.synthetic.main.fragment_account_activation.*
import kotlinx.android.synthetic.main.layout_toolbar_template.*

class AccountActivationFragment : BaseInputFragment(), IAccountActivationView {

    override fun initPresenter(navigationManager: CamNavigationRouter): IBaseInputPresenter {
        val authData: HashMap<String, String> =
            getUserAuthData() ?: hashMapOf()
        presenter = AccountActivationPresenter(this, authData, navigationManager)
        setPresenter(presenter)
        return presenter as AccountActivationPresenter
    }

    override fun getLayoutId() = R.layout.fragment_account_activation

    override fun setListeners() {
        btn_activate.setOnClickListener { presenter?.onAuthActionButtonClicked(getInputFieldsValues()) }
        tv_resend_code.setOnClickListener { (presenter as? AccountActivationPresenter)?.onResendCodeClicked() }
        toolbar_back_button.setOnClickListener { presenter?.onToolbarBackClicked() }
    }

    override fun customize() {
        super.customize()

        UIMapper.apply {
            map(toolbar_back_button, UIKey.TOOLBAR_BACK_BUTTON)
            map(app_logo, UIKey.TOOLBAR_HEADER_LOGO_IMAGE)
            map(container_account_activation, UIKey.BACKGROUND_IMAGE)

            map(tv_activation_title, UIKey.ACCOUNT_ACTIVATION_TITLE_TEXT)
            map(tv_activation_title_desc, UIKey.ACCOUNT_ACTIVATION_DESC_TEXT)
            map(btn_activate, UIKey.ACCOUNT_ACTIVATION_ACTION_BUTTON)
            map(tv_resend_code, UIKey.ACCOUNT_ACTIVATION_RESEND_CODE_BUTTON)
        }
    }

    override fun populateAuthFieldsViews(authFieldConfig: AuthFieldConfig) {
        super.populateAuthFieldsViews(authFieldConfig)
        val scrollableParent = getAuthInputScrollableParent()
        scrollableParent?.layoutParams =
            LinearLayout.LayoutParams(
                LinearLayout.LayoutParams.WRAP_CONTENT,
                LinearLayout.LayoutParams.MATCH_PARENT
            )
    }

    private fun getUserAuthData(): HashMap<String, String>? =
        arguments?.getSerializable(KEY_USER_AUTH_DATA) as? HashMap<String, String>

    override fun getParentView(): ViewGroup? = container_account_activation

    override fun getAuthInputLinearParent(): LinearLayout? = container_linear_activation_input

    override fun getAuthInputScrollableParent(): ScrollView? = container_scrollable_activation_input

    override fun onLastFragmentClosed() = Unit

    companion object {
        private const val KEY_USER_AUTH_DATA = "user_auth_data"

        fun newInstance(authData: HashMap<String, String>): AccountActivationFragment {
            return AccountActivationFragment().apply { arguments = getBundle(authData) }
        }

        fun getBundle(authData: HashMap<String, String>) = Bundle().apply { putSerializable(KEY_USER_AUTH_DATA, authData) }
    }
}