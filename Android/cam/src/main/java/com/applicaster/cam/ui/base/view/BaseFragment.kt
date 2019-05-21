package com.applicaster.cam.ui.base.view

import android.annotation.SuppressLint
import android.content.Context
import android.os.Bundle
import android.support.v4.app.Fragment
import android.view.View
import android.view.ViewGroup
import android.widget.Toast
import com.applicaster.cam.ui.base.presenter.IBasePresenter

abstract class BaseFragment : Fragment(), IBaseView {

    protected lateinit var baseActivity: BaseActivity
    private var basePresenter: IBasePresenter? = null
    private var toast: Toast? = null

    protected fun setPresenter(presenter: IBasePresenter?) {
        basePresenter = presenter
    }

    override fun onAttach(context: Context?) {
        super.onAttach(context)
        baseActivity = context as BaseActivity
    }

    override fun onViewCreated(view: View, savedInstanceState: Bundle?) {
        super.onViewCreated(view, savedInstanceState)
        basePresenter?.onViewCreated()
    }

    override fun onPause() {
        super.onPause()
        basePresenter?.onViewPaused()
    }

    override fun onStop() {
        super.onStop()
        basePresenter?.onViewStopped()
    }

    override fun onResume() {
        super.onResume()
        basePresenter?.onViewResumed()
    }

    override fun onDestroy() {
        basePresenter?.onViewDestroyed()
        super.onDestroy()
    }

    override fun getViewContext(): Context? {
        return context
    }

    @SuppressLint("ShowToast")
    override fun showToastMessage(message: String) {
        if (isAdded && context != null && !activity?.isFinishing!!) {
            if (toast == null) {
                toast = Toast.makeText(context, message, Toast.LENGTH_SHORT)
            } else {
                toast?.setText(message)
                toast?.duration = Toast.LENGTH_SHORT
            }
            toast?.show()
        }
    }

    override fun customize() {
        makeFullscreen(getParentView())
    }

    open fun showLoadingIndicator() {
        TODO("not implemented") //To change body of created functions use File | Settings | File Templates.
    }

    open fun hideLoadingIndicator() {
        TODO("not implemented") //To change body of created functions use File | Settings | File Templates.
    }

    override fun goBack() {
        activity?.onBackPressed()
    }

    override fun close() {
        activity?.finish()
    }

    private fun makeFullscreen(rootLayout: View?) {
        rootLayout?.apply {
            fitsSystemWindows = true
            parent?.requestFitSystemWindows()
        }
    }

    protected abstract fun setListeners()
    protected abstract fun getParentView(): ViewGroup?
}