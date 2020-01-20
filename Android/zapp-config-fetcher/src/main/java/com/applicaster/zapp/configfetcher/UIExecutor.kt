package com.applicaster.zapp.configfetcher

import android.content.Context
import android.support.v4.app.FragmentActivity
import com.applicaster.zapp.configfetcher.ui.TransparentLoadingFragment

suspend fun <T> UIEnvironment.executeWithUIAndReturn(
        function: suspend () -> T
): T {
    context?.run { if (showLoadingUI) showLoading() }
    val data = function()
    context?.run { if (showLoadingUI) hideLoading() }
    return data
}

suspend fun UIEnvironment.executeWithUI(
        function: suspend () -> Unit
) {
    context?.run { if (showLoadingUI) showLoading() }
    function()
    context?.run { if (showLoadingUI) hideLoading() }
}

fun Context.showLoading() {
    if (this is FragmentActivity) {
        val fragment = supportFragmentManager
                .findFragmentByTag(TransparentLoadingFragment.TAG)
                ?: TransparentLoadingFragment.newInstance()
        if (!fragment.isAdded && !fragment.isVisible)
            supportFragmentManager.beginTransaction().add(
                    fragment,
                    TransparentLoadingFragment.TAG
            ).commit()
    }
}

fun Context.hideLoading() {
    if (this is FragmentActivity) {
        val fragment = supportFragmentManager
                .findFragmentByTag(TransparentLoadingFragment.TAG)
        if (fragment != null && fragment.isAdded)
            supportFragmentManager.beginTransaction().remove(
                    fragment
            ).commit()
    }
}

class UIEnvironment(val context: Context?, val showLoadingUI: Boolean)