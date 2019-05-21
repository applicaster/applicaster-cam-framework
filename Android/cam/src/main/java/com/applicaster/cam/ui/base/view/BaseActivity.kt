package com.applicaster.cam.ui.base.view

import android.annotation.SuppressLint
import android.content.Context
import android.support.v7.app.AppCompatActivity
import android.widget.Toast
import com.applicaster.cam.ui.base.BaseNavigationRouter
import com.applicaster.cam.ui.base.presenter.IBasePresenter

abstract class BaseActivity : AppCompatActivity(), IBaseView {
    private var basePresenter: IBasePresenter? = null
    private var toast: Toast? = null

    protected fun setPresenter(presenter: IBasePresenter?) {
        basePresenter = presenter
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

    override fun getViewContext(): Context {
        return this
    }

    override fun goBack() {
        onBackPressed()
    }

    override fun close() {
        finish()
    }

    override fun customize() {

    }

    @SuppressLint("ShowToast")
    override fun showToastMessage(message: String) {
        if (!isFinishing) {
            if (toast == null) {
                toast = Toast.makeText(this, message, Toast.LENGTH_SHORT)
            } else {
                toast?.setText(message)
                toast?.duration = Toast.LENGTH_SHORT
            }
            toast?.show()
        }
    }

    abstract fun getFragmentContainerType(): ContainerType
    abstract fun getFragmentContainerId(): Int
    abstract fun getNavigationRouter(): BaseNavigationRouter?
}
