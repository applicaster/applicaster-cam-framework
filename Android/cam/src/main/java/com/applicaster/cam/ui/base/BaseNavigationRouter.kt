package com.applicaster.cam.ui.base

import android.content.Context
import android.content.Intent
import android.net.Uri
import android.support.v4.app.FragmentManager
import android.support.v4.content.ContextCompat

import com.applicaster.cam.ui.base.view.IBaseActivity

open class BaseNavigationRouter() {
    protected lateinit var context: Context
    protected lateinit var fragmentManager: FragmentManager
    protected var fragmentContainer: Int? = null

    constructor(baseActivity: IBaseActivity) : this() {
        this.fragmentManager = baseActivity.getSupportFragmentManager()
        this.fragmentContainer = baseActivity.getFragmentContainerId()
    }

    fun openBrowserWithUrl(url: String) {
        val browserIntent = Intent(Intent.ACTION_VIEW, Uri.parse(url))
        context.startActivity(browserIntent)
    }
}