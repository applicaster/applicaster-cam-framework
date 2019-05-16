package com.applicaster.cam.ui.base.view

import android.content.Context

interface IBaseView {
    fun getViewContext(): Context?
    fun goBack()
    fun close()
}