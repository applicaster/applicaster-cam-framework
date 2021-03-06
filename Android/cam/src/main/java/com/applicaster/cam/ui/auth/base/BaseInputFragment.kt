package com.applicaster.cam.ui.auth.base

import android.os.Bundle
import android.view.LayoutInflater
import android.view.View
import android.view.ViewGroup
import android.widget.LinearLayout
import android.widget.ScrollView
import com.applicaster.cam.params.auth.AuthField
import com.applicaster.cam.params.auth.AuthFieldConfig
import com.applicaster.cam.ui.CamNavigationRouter
import com.applicaster.cam.ui.base.custom.AuthInputFieldView
import com.applicaster.cam.ui.base.custom.ErrorPopupViewBuilder
import com.applicaster.cam.ui.base.custom.InputFieldViewListener
import com.applicaster.cam.ui.base.view.BaseFragment

abstract class BaseInputFragment : BaseFragment(), IBaseInputView {
    protected var presenter: IBaseInputPresenter? = null

    override fun onCreateView(
        inflater: LayoutInflater, container: ViewGroup?,
        savedInstanceState: Bundle?
    ): View? {
        val rootView = inflater.inflate(getLayoutId(), container, false)
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

    override fun populateAuthFieldsViews(authFieldConfig: AuthFieldConfig) {
        val context = this@BaseInputFragment.context
        val inputViewsParent = getAuthInputLinearParent()
        val listener : InputFieldViewListener? = presenter
        if (context != null && inputViewsParent != null && listener != null) {
            InputFieldViewCustomizer.populateAuthFields(
                context = context,
                linearParent = inputViewsParent,
                scrollableParent = getAuthInputScrollableParent(),
                authFieldConfig = authFieldConfig,
                listener = listener
            )
        }
    }

    override fun getInputFieldsValues(): HashMap<AuthField, String> {
        val inputValues = HashMap<AuthField, String>()
        val numberOfChildViews = getAuthInputLinearParent()?.childCount ?: 0
        if (numberOfChildViews > 0) {
            for (i in 0 until numberOfChildViews) {
                val child = getAuthInputLinearParent()?.getChildAt(i) as? AuthInputFieldView
                if (child != null)
                    inputValues[child.authField] = child.text.toString()
            }
        }
        return inputValues
    }

    override fun showAuthInputFieldErrorIcons(inputFieldValidationErrors: HashMap<AuthField, String>) {
        val numberOfChildViews = getAuthInputLinearParent()?.childCount ?: 0
        if (numberOfChildViews > 0)
            for (i in 0 until numberOfChildViews) {
                getAuthInputLinearParent()?.let {
                    val child = it.getChildAt(i) as? AuthInputFieldView
                    for (error in inputFieldValidationErrors) {
                        if (child != null && child.authField.key == error.key.key) {
                            child.showError(errorMsg = error.value)
                            break
                        }
                    }
                }
            }
    }

    override fun showErrorPopup(rootView: View, errorMsg: String) {
        ErrorPopupViewBuilder(context, layoutInflater).build(rootView, errorMsg)
    }

    abstract fun getLayoutId(): Int
    abstract fun getAuthInputLinearParent(): LinearLayout?
    abstract fun getAuthInputScrollableParent(): ScrollView?
    abstract fun initPresenter(navigationManager: CamNavigationRouter): IBaseInputPresenter
}