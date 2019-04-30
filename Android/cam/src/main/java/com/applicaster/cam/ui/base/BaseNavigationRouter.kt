package com.applicaster.cam.ui.base

import android.content.Context
import android.support.v4.app.FragmentManager

import com.applicaster.cam.ui.base.view.BaseActivity

open class BaseNavigationRouter() {
    protected lateinit var appContext: Context
    protected lateinit var context: Context
    protected lateinit var fragmentManager: FragmentManager
    protected var fragmentContainer: Int? = null

    constructor(baseActivity: BaseActivity) : this() {
        this.appContext = baseActivity.applicationContext
        this.fragmentManager = baseActivity.supportFragmentManager
        this.fragmentContainer = baseActivity.getFragmentContainerId()
    }
}