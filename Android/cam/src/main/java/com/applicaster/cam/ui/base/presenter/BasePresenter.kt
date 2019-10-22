package com.applicaster.cam.ui.base.presenter

import android.support.annotation.StringRes
import com.applicaster.cam.ui.base.view.IBaseView

open class BasePresenter(private var view: IBaseView?) : IBasePresenter {

    override fun onViewCreated() {
    }

    override fun onViewPaused() {
    }

    override fun onViewStopped() {
    }

    override fun onViewResumed() {
    }

    override fun onViewDestroyed() {
    }

    override fun onToolbarBackClicked() {
        view?.goBack()
    }

    override fun onToolbarCloseClicked() {
        view?.close()
    }

    override fun onLastFragmentClosed() {
        view?.onLastFragmentClosed()
    }

    protected val context = view?.getViewContext()

    fun getString(@StringRes resId: Int) = context?.run { getString(resId) } ?: ""

    fun getString(@StringRes resId: Int, vararg formatArgs: Any) =
        context?.run { getString(resId, *formatArgs) } ?: ""
}