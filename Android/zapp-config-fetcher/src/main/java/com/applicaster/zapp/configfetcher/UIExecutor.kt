package com.applicaster.zapp.configfetcher

import android.content.Context
import androidx.fragment.app.FragmentActivity
import com.applicaster.zapp.configfetcher.ui.TransparentLoadingFragment

suspend fun <T> UIEnvironment.executeWithResult(
        function: suspend () -> T
): T {
    context?.run { if (showLoadingUI) showLoading() }
    val data = function()
    context?.run { if (showLoadingUI) hideLoading() }
    return data
}

suspend fun UIEnvironment.execute(
        function: suspend () -> Unit
) {
    context?.run { if (showLoadingUI) showLoading() }
    function()
    context?.run { if (showLoadingUI) hideLoading() }
}

fun Context.showLoading() {
    if (this is androidx.fragment.app.FragmentActivity) {
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
    if (this is androidx.fragment.app.FragmentActivity) {
        val fragment = supportFragmentManager
                .findFragmentByTag(TransparentLoadingFragment.TAG)
        if (fragment != null && fragment.isAdded)
            supportFragmentManager.beginTransaction().remove(
                    fragment
            ).commit()
    }
}

class UIEnvironment(val context: Context?, val showLoadingUI: Boolean)