package com.applicaster.cam.ui.base

import android.content.Context
import android.content.Intent
import android.net.Uri
import android.support.v4.app.FragmentManager
import com.applicaster.cam.ui.base.view.IBaseActivity
import java.lang.ref.WeakReference

open class BaseNavigationRouter() {
    protected var context: WeakReference<Context>? = null
    protected var fragmentManager: FragmentManager? = null
    protected var fragmentContainer: Int? = null

    constructor(baseActivity: IBaseActivity) : this() {
        this.context = WeakReference(baseActivity.getContext())
        this.fragmentManager = baseActivity.getSupportFragmentManager()
        this.fragmentContainer = baseActivity.getFragmentContainerId()
    }

    fun navigateFragmentBackTwice() {
        fragmentManager?.apply {
            repeat(2) { popBackStackImmediate() }
            executePendingTransactions()
        }
    }

    fun openBrowserWithUrl(url: String) {
        val browserIntent = Intent(Intent.ACTION_VIEW, Uri.parse(url)).apply { flags = Intent.FLAG_ACTIVITY_NEW_TASK }
        context?.get()?.startActivity(browserIntent)
    }
}