package com.applicaster.cam.ui.base.view

import android.content.Context
import android.support.v7.app.AppCompatActivity
import com.applicaster.cam.ui.base.BaseNavigationRouter
import com.applicaster.cam.ui.base.presenter.IBasePresenter

abstract class BaseActivity : AppCompatActivity(), IBaseView {
    private var basePresenter: IBasePresenter? = null

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

    abstract fun getFragmentContainerType(): ContainerType
    abstract fun getFragmentContainerId(): Int
    abstract fun getNavigationRouter(): BaseNavigationRouter?
}
