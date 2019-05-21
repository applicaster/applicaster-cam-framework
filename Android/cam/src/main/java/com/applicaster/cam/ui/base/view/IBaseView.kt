package com.applicaster.cam.ui.base.view

import android.content.Context

interface IBaseView {
    fun customize()
    fun getViewContext(): Context?
    fun goBack()
    fun close()
    fun showToastMessage(msg: String)
}