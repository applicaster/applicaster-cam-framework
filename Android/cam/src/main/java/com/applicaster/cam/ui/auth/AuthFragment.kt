package com.applicaster.cam.ui.auth

import android.os.Bundle
import android.view.Gravity
import android.view.LayoutInflater
import android.view.View
import android.view.ViewGroup
import android.widget.PopupWindow
import android.widget.TextView
import com.applicaster.cam.ContentAccessManager
import com.applicaster.cam.R
import com.applicaster.cam.config.ui.UIKey
import com.applicaster.cam.config.ui.UIMapper
import com.applicaster.cam.params.auth.AuthField
import com.applicaster.cam.params.auth.AuthFieldConfig
import com.applicaster.cam.ui.CamNavigationRouter
import com.applicaster.cam.ui.base.custom.AuthInputFieldView
import com.applicaster.cam.ui.base.custom.InputFieldViewListener
import com.applicaster.cam.ui.base.view.BaseFragment
import kotlinx.android.synthetic.main.fragment_auth.*
import kotlinx.android.synthetic.main.layout_additional_auth.*
import kotlinx.android.synthetic.main.layout_auth_input.*
import kotlinx.android.synthetic.main.layout_bottom_bar.*
import kotlinx.android.synthetic.main.layout_text_with_action.*
import kotlinx.android.synthetic.main.layout_toolbar_template.*

abstract class AuthFragment : BaseFragment(), IAuthView, InputFieldViewListener {
    private var presenter: IAuthPresenter? = null

    override fun onCreateView(
        inflater: LayoutInflater, container: ViewGroup?,
        savedInstanceState: Bundle?
    ): View? {
        val rootView = inflater.inflate(R.layout.fragment_auth, container, false)
        baseActivity?.apply {
            val navigationManager = if (getNavigationRouter() is CamNavigationRouter)
                getNavigationRouter() as CamNavigationRouter
            else
                CamNavigationRouter(this)
            presenter = initPresenter(navigationManager)
        }

        return rootView
    }

    override fun onViewCreated(view: View, savedInstanceState: Bundle?) {
        super.onViewCreated(view, savedInstanceState)
        setListeners()
    }

    override fun setListeners() {
        btn_input_action.setOnClickListener { presenter?.onAuthActionButtonClicked(getInputFieldsValues()) }
        tv_hint_desc.setOnClickListener { presenter?.onAuthHintClicked() }
        tv_hint_action.setOnClickListener { presenter?.onAuthHintClicked() }
        tv_bottom_bar_desc.setOnClickListener { presenter?.onRestoreClicked() }
        tv_bottom_bar_action.setOnClickListener { presenter?.onRestoreClicked() }
        toolbar_back_button.setOnClickListener { presenter?.onToolbarBackClicked() }
        toolbar_close_button.setOnClickListener { presenter?.onToolbarCloseClicked() }
        iv_facebook_auth.setOnClickListener { presenter?.onFacebookButtonClicked(activity) }
    }

    override fun customize() {
        super.customize()

        container_additional_auth?.apply {
            visibility =
                if (ContentAccessManager.pluginConfigurator.isFacebookLoginRequired()) View.VISIBLE else View.GONE
        }
        container_bottom_bar?.apply {
            visibility =
                if (ContentAccessManager.pluginConfigurator.isAuthRestoreRequired()) View.VISIBLE else View.GONE
        }

        UIMapper.apply {
            map(toolbar_back_button, UIKey.TOOLBAR_BACK_BUTTON)
            map(app_logo, UIKey.TOOLBAR_HEADER_LOGO_IMAGE)
            map(container_parent_auth, UIKey.BACKGROUND_IMAGE)
            map(iv_facebook_auth, UIKey.AUTH_FACEBOOK_IMAGE)
            map(iv_left_divider, UIKey.AUTH_LEFT_DIVIDER_IMAGE)
            map(iv_right_divider, UIKey.AUTH_RIGHT_DIVIDER_IMAGE)
        }
    }

    override fun getParentView() = container_parent_auth

    override fun populateAuthFieldsViews(authFieldConfig: AuthFieldConfig) {
        context?.apply {
            InputFieldViewCustomizer.populateAuthFields(
                this,
                linearParent = container_linear_input,
                scrollableParent = container_scrollable_input,
                authFieldConfig = authFieldConfig,
                listener = this@AuthFragment
            )
        }
    }

    fun showPopupMenu(anchorView: View, msg: String) {
        val popupView = layoutInflater.inflate(R.layout.layout_input_validation_popup, null)
        val tvValidationMessage = popupView.findViewById<TextView>(R.id.tv_validation_msg)
        tvValidationMessage.text = msg
        val popupWindow = PopupWindow(
            popupView,
            resources.getDimensionPixelSize(R.dimen.auth_error_popup_width),
            resources.getDimensionPixelSize(R.dimen.auth_error_popup_height)
        )
        popupWindow.isFocusable = true
        val location = IntArray(2)
        anchorView.getLocationOnScreen(location)
        popupWindow.showAtLocation(
            anchorView, Gravity.NO_GRAVITY, location[0] -
                    (resources.getDimensionPixelSize(R.dimen.auth_error_popup_width)
                            - resources.getDimensionPixelSize(R.dimen.auth_error_text_width)) / 2,
            location[1] + anchorView.height
        )
    }

    private fun getInputFieldsValues(): HashMap<AuthField, String> {
        val inputValues = HashMap<AuthField, String>()
        for (i in 0 until container_linear_input.childCount) {
            val child = container_linear_input.getChildAt(i) as? AuthInputFieldView
            if (child != null)
                inputValues[child.authField] = child.text.toString()
        }
        return inputValues
    }

    override fun showAuthInputFieldErrorIcons(inputFieldValidationErrors: HashMap<AuthField, String>) {
        for (i in 0 until container_linear_input.childCount) {
            val child = container_linear_input.getChildAt(i) as? AuthInputFieldView
            for (error in inputFieldValidationErrors) {
                if (child != null && child.authField.key == error.key.key) {
                    child.showError(errorMsg = error.value)
                    break
                }
            }
        }
    }

    override fun onErrorIconClicked(rootView: View, errorMsg: String) {
        showPopupMenu(rootView, errorMsg)
    }

    abstract fun initPresenter(navigationManager: CamNavigationRouter): IAuthPresenter
}