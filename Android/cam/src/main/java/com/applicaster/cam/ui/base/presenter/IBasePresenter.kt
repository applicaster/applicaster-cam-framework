package com.applicaster.cam.ui.base.presenter

interface IBasePresenter {
    fun onViewCreated()
    fun onViewPaused()
    fun onViewStopped()
    fun onViewResumed()
    fun onViewDestroyed()
    fun onToolbarBackClicked()
    fun onToolbarCloseClicked()
    fun onLastFragmentClosed()
}