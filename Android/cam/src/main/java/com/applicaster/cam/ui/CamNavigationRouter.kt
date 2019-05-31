package com.applicaster.cam.ui

import android.support.v4.app.DialogFragment
import android.support.v4.app.Fragment
import android.support.v4.app.FragmentTransaction
import com.applicaster.cam.ui.auth.login.LoginFragment
import com.applicaster.cam.ui.auth.signup.SignUpFragment
import com.applicaster.cam.ui.base.BaseNavigationRouter
import com.applicaster.cam.ui.confirmation.AlertDialogType
import com.applicaster.cam.ui.base.view.IBaseActivity
import com.applicaster.cam.ui.confirmation.ConfirmationDialog
import com.applicaster.cam.ui.billing.BillingFragment
import com.applicaster.cam.ui.auth.password.reset.PasswordResetFragment

class CamNavigationRouter(baseActivity: IBaseActivity) : BaseNavigationRouter(baseActivity) {

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
        fragmentTransaction?.addToBackStack(tag)
        fragmentTransaction?.replace(fragmentContainer!!, fragment, tag)
        fragmentTransaction?.commit()
    }

    fun showConfirmationDialog(dialogType: AlertDialogType) {
        val tag = "ConfirmationDialog-${dialogType.name}"
        val dialog: DialogFragment? = fragmentManager.findFragmentByTag(tag) as? DialogFragment
        if (dialog == null) {
            ConfirmationDialog.newInstance(dialogType).show(fragmentManager, tag)
        } else {
            dialog.show(fragmentManager, tag)
        }
    }
}