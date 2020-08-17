package com.applicaster.zapp.configfetcher

import android.content.Context
import androidx.fragment.app.FragmentActivity
import com.applicaster.zapp.configfetcher.ui.TransparentLoadingFragment

fun FragmentActivity.showLoading() {
    val fragment = supportFragmentManager
            .findFragmentByTag(TransparentLoadingFragment.TAG)
            ?: TransparentLoadingFragment.newInstance()
    if (!fragment.isAdded && !fragment.isVisible)
        supportFragmentManager.beginTransaction().add(
                fragment,
                TransparentLoadingFragment.TAG
        ).commit()
}

fun FragmentActivity.hideLoading() {
    val fragment = supportFragmentManager
            .findFragmentByTag(TransparentLoadingFragment.TAG)
    if (fragment != null && fragment.isAdded)
        supportFragmentManager.beginTransaction().remove(
                fragment
        ).commit()
}

class UIEnvironment(context: Context?, showLoadingUI: Boolean){

    private val activity: FragmentActivity? = if (showLoadingUI) context as? FragmentActivity? else null

    suspend fun <T> executeWithResult(
            function: suspend () -> T
    ): T {
        activity?.run { if(!activity.isFinishing) showLoading() }
        val data = function()
        activity?.run { if(!activity.isFinishing) hideLoading() }
        return data
    }

    suspend fun execute(
            function: suspend () -> Unit
    ) = executeWithResult(function)

}