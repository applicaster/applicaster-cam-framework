package com.applicaster.cam.ui

import android.support.v4.app.DialogFragment
import android.support.v4.app.Fragment
import android.support.v4.app.FragmentManager
import android.support.v4.app.FragmentTransaction
import com.applicaster.cam.params.auth.AuthScreenType
import com.applicaster.cam.ui.auth.user.login.LoginFragment
import com.applicaster.cam.ui.auth.user.signup.SignUpFragment
import com.applicaster.cam.ui.base.BaseNavigationRouter
import com.applicaster.cam.ui.confirmation.AlertDialogType
import com.applicaster.cam.ui.base.view.IBaseActivity
import com.applicaster.cam.ui.confirmation.ConfirmationDialog
import com.applicaster.cam.ui.billing.BillingFragment
import com.applicaster.cam.ui.auth.password.reset.PasswordResetFragment

class CamNavigationRouter(baseActivity: IBaseActivity) : BaseNavigationRouter(baseActivity) {

    private val confirmationDialogPrefix: String = "ConfirmationDialog-"

    fun attachSignUpFragment(initialLoad: Boolean = false) {
        val tag = SignUpFragment::class.java.canonicalName
        val fragment: Fragment = fragmentManager.findFragmentByTag(tag) ?: SignUpFragment()
        val fragmentTransaction: FragmentTransaction? = fragmentManager.beginTransaction()
        if (!initialLoad) {
            fragmentTransaction?.addToBackStack(tag)
        }
        fragmentTransaction?.replace(fragmentContainer!!, fragment, tag)
        fragmentTransaction?.commit()
    }

    fun attachLoginFragment(initialLoad: Boolean = false) {
        val tag = LoginFragment::class.java.canonicalName
        val fragment: Fragment = fragmentManager.findFragmentByTag(tag) ?: LoginFragment()
        val fragmentTransaction: FragmentTransaction? = fragmentManager.beginTransaction()
        if (!initialLoad) {
            fragmentTransaction?.addToBackStack(tag)
        }
        fragmentTransaction?.replace(fragmentContainer!!, fragment, tag)
        fragmentTransaction?.commit()
    }

    fun attachPasswordResetFragment() {
        val tag = PasswordResetFragment::class.java.canonicalName
        val fragment: Fragment = fragmentManager.findFragmentByTag(tag) ?: PasswordResetFragment()
        val fragmentTransaction: FragmentTransaction? = fragmentManager.beginTransaction()
        fragmentTransaction?.addToBackStack(tag)
        fragmentTransaction?.replace(fragmentContainer!!, fragment, tag)
        fragmentTransaction?.commit()
    }

    fun attachBillingFragment() {
        val tag = BillingFragment::class.java.canonicalName
        val fragment: Fragment = fragmentManager.findFragmentByTag(tag) ?: BillingFragment()
        val fragmentTransaction: FragmentTransaction? = fragmentManager.beginTransaction()

        //clearing back stack
        fragmentManager.popBackStack(null, FragmentManager.POP_BACK_STACK_INCLUSIVE)

        fragmentTransaction?.replace(fragmentContainer!!, fragment, tag)
        fragmentTransaction?.commit()
    }

    fun showConfirmationDialog(dialogType: AlertDialogType) {
        val tag = "$confirmationDialogPrefix${dialogType.name}"
        val dialog: DialogFragment? = fragmentManager.findFragmentByTag(tag) as? DialogFragment
        if (dialog == null) {
            ConfirmationDialog.newInstance(dialogType).show(fragmentManager, tag)
        } else {
            dialog.show(fragmentManager, tag)
        }
    }

    fun attachLastFragment(authScreenType: AuthScreenType) {
        val fragmentTransaction: FragmentTransaction? = fragmentManager.beginTransaction()
        val fragmentList = fragmentManager.fragments
        if (fragmentList.size != 0) {
            val lastFragment = fragmentList.last().takeIf {
                it.tag?.contains(confirmationDialogPrefix) ?: false
            }
            if (lastFragment != null) {
                val fragment = fragmentList[fragmentList.size - 2]
                fragment?.apply {
                    val tag = this.javaClass.canonicalName
                    fragmentTransaction?.replace(fragmentContainer!!, fragment, tag)
                    fragmentTransaction?.commit()
                }
            } else {
                val fragment = fragmentList.last()
                fragment?.apply {
                    val tag = this.javaClass.canonicalName
                    fragmentTransaction?.replace(fragmentContainer!!, fragment, tag)
                    fragmentTransaction?.commit()
                }
            }
        } else {
            when (authScreenType) {
                AuthScreenType.LOGIN -> attachLoginFragment(true)
                AuthScreenType.SIGNUP -> attachSignUpFragment(true)
            }
        }
    }
}