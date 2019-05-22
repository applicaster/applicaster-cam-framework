package com.applicaster.cam.ui.auth

import android.os.Bundle
import android.text.InputType
import android.view.LayoutInflater
import android.view.View
import android.view.ViewGroup
import android.widget.EditText
import android.widget.LinearLayout
import com.applicaster.cam.ContentAccessManager
import com.applicaster.cam.R
import com.applicaster.cam.config.ui.UIKey
import com.applicaster.cam.config.ui.UIMapper
import com.applicaster.cam.params.auth.AuthField
import com.applicaster.cam.params.auth.AuthFieldConfig
import com.applicaster.cam.ui.CamNavigationRouter
import com.applicaster.cam.ui.base.view.BaseFragment
import kotlinx.android.synthetic.main.fragment_auth.*
import kotlinx.android.synthetic.main.layout_additional_auth.*
import kotlinx.android.synthetic.main.layout_auth_input.*
import kotlinx.android.synthetic.main.layout_bottom_bar.*
import kotlinx.android.synthetic.main.layout_text_with_action.*
import kotlinx.android.synthetic.main.layout_toolbar_template.*

abstract class AuthFragment : BaseFragment(), IAuthView {
    private var presenter: IAuthPresenter? = null

    override fun onCreateView(
        inflater: LayoutInflater, container: ViewGroup?,
        savedInstanceState: Bundle?
    ): View? {
        val rootView = inflater.inflate(R.layout.fragment_auth, container, false)

        val navigationManager = if (baseActivity.getNavigationRouter() is CamNavigationRouter)
            baseActivity.getNavigationRouter() as CamNavigationRouter
        else
            CamNavigationRouter(baseActivity)
        presenter = initPresenter(navigationManager)

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
            map(toolbar_close_button, UIKey.TOOLBAR_CLOSE_BUTTON)
            map(app_logo, UIKey.TOOLBAR_HEADER_LOGO)
            map(container_parent_auth, UIKey.BACKGROUND_IMAGE)
            map(iv_facebook_auth, UIKey.AUTH_FACEBOOK_IMAGE)
        }
    }

    override fun getParentView() = container_parent_auth

    override fun populateAuthFieldsViews(authFieldConfig: AuthFieldConfig) {
        val etWidth = resources.getDimensionPixelSize(R.dimen.auth_et_width)
        val etHeight = resources.getDimensionPixelSize(R.dimen.auth_et_height)
        val etMarginTop = resources.getDimensionPixelSize(R.dimen.auth_et_margin_top)

        for (field in authFieldConfig.authFields) {
            val editText = EditText(context)
            editText.applyCustomizations(etWidth, etHeight, etMarginTop, field)
            container_linear_input.addView(editText)
        }
        val visibleViewsCount =
            if (authFieldConfig.authFields.size < MAX_NON_SCROLLABLE_AUTH_FIELDS)
                authFieldConfig.authFields.size else MAX_NON_SCROLLABLE_AUTH_FIELDS
        val parentMaxHeight = (etHeight + etMarginTop) * visibleViewsCount

        //recalculating scroll view height to match design spec
        container_scrollable_input.layoutParams = container_scrollable_input.layoutParams.apply {
            height = parentMaxHeight
        }
    }

    private fun getInputFieldsValues(): HashMap<String, String> {
        val inputValues = HashMap<String, String>()
        for (i in 0 until container_linear_input.childCount) {
            val child = container_linear_input.getChildAt(i) as? EditText
            if (child != null)
                inputValues[(child.tag as AuthField).key!!] = child.text.toString()
        }
        return inputValues
    }

    abstract fun initPresenter(navigationManager: CamNavigationRouter): IAuthPresenter

    companion object {
        const val MAX_NON_SCROLLABLE_AUTH_FIELDS = 4
    }
}

private fun EditText.applyCustomizations(
    etWidth: Int,
    etHeight: Int,
    etMarginTop: Int,
    field: AuthField
) {
    layoutParams = LinearLayout.LayoutParams(
        etWidth,
        etHeight
    ).apply {
        topMargin = etMarginTop

    }
    tag = field
    val paddingHorizontal = resources.getDimensionPixelSize(R.dimen.auth_et_padding_horizontal)
    setPadding(paddingHorizontal, 0, paddingHorizontal, 0)
    UIMapper.map(this, UIKey.AUTH_INPUT_FIELD)
    inputType = when (field.type) {
        AuthField.Type.TEXT -> InputType.TYPE_CLASS_TEXT
        AuthField.Type.PASSWORD -> (InputType.TYPE_CLASS_TEXT or InputType.TYPE_TEXT_VARIATION_PASSWORD)
        AuthField.Type.NUMBER -> InputType.TYPE_CLASS_NUMBER
        else -> InputType.TYPE_CLASS_TEXT
    }
    hint = field.hint
}