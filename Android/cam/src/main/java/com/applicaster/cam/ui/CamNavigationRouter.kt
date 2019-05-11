package com.applicaster.cam.ui

import android.support.v4.app.Fragment
import android.support.v4.app.FragmentTransaction
import com.applicaster.cam.ui.base.BaseNavigationRouter
import com.applicaster.cam.ui.base.view.BaseActivity
import com.applicaster.cam.ui.signup.SignUpFragment

class CamNavigationRouter(baseActivity: BaseActivity) : BaseNavigationRouter(baseActivity) {

    fun attachSignUpFragment() {
        val tag = SignUpFragment::class.java.canonicalName
        val fragment: Fragment = fragmentManager.findFragmentByTag(tag) ?: SignUpFragment()
        val fragmentTransaction: FragmentTransaction? = fragmentManager.beginTransaction()
        fragmentTransaction?.replace(fragmentContainer!!, fragment, tag)
        fragmentTransaction?.commit()
    }

}