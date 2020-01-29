package com.applicaster.cam.ui

import android.support.v4.app.DialogFragment
import android.support.v4.app.Fragment
import android.support.v4.app.FragmentManager
import android.support.v4.app.FragmentTransaction
import android.util.Log
import com.applicaster.cam.CamFlow
import com.applicaster.cam.params.auth.AuthScreenType
import com.applicaster.cam.ui.auth.user.login.LoginFragment
import com.applicaster.cam.ui.auth.user.signup.SignUpFragment
import com.applicaster.cam.ui.base.BaseNavigationRouter
import com.applicaster.cam.ui.confirmation.AlertDialogType
import com.applicaster.cam.ui.base.view.IBaseActivity
import com.applicaster.cam.ui.confirmation.ConfirmationDialog
import com.applicaster.cam.ui.billing.BillingFragment
import com.applicaster.cam.ui.auth.password.reset.PasswordResetFragment
import com.applicaster.cam.ui.auth.password.update.PasswordUpdateFragment
import com.applicaster.cam.ui.auth.user.activation.AccountActivationFragment
import com.applicaster.cam.ui.base.view.BaseFragment
import java.util.HashMap

class CamNavigationRouter(private val baseActivity: IBaseActivity) : BaseNavigationRouter(baseActivity) {

    private val TAG = CamNavigationRouter::class.java.canonicalName
    private val confirmationDialogPrefix: String = "ConfirmationDialog-"

    fun attachSignUpFragment(initialLoad: Boolean = false) {
        val tag = SignUpFragment::class.java.canonicalName
        val isAddedToBackStack: Boolean = fragmentManager?.findFragmentByTag(tag) != null
        val fragment: Fragment = fragmentManager?.findFragmentByTag(tag) ?: SignUpFragment()
        val fragmentTransaction: FragmentTransaction? = fragmentManager?.beginTransaction()
        if (fragmentManager?.backStackEntryCount == 1) {
            fragmentManager?.popBackStackImmediate()
            fragmentManager?.executePendingTransactions()
        }
        if (!initialLoad && !isAddedToBackStack) {
            fragmentTransaction?.addToBackStack(tag)
        }
        fragmentTransaction?.replace(fragmentContainer!!, fragment, tag)
        fragmentTransaction?.commit()
    }

    fun attachLoginFragment(initialLoad: Boolean = false) {
        val tag = LoginFragment::class.java.canonicalName
        val isAddedToBackStack: Boolean = fragmentManager?.findFragmentByTag(tag) != null
        val fragment: Fragment = fragmentManager?.findFragmentByTag(tag) ?: LoginFragment()
        val fragmentTransaction: FragmentTransaction? = fragmentManager?.beginTransaction()
        if (fragmentManager?.backStackEntryCount == 1) {
            fragmentManager?.popBackStackImmediate()
            fragmentManager?.executePendingTransactions()
        }
        if (!initialLoad && !isAddedToBackStack) {
            fragmentTransaction?.addToBackStack(tag)
        }
        fragmentTransaction?.replace(fragmentContainer!!, fragment, tag)
        fragmentTransaction?.commit()
    }

    fun attachPasswordResetFragment() {
        val tag = PasswordResetFragment::class.java.canonicalName
        val fragment: Fragment = fragmentManager?.findFragmentByTag(tag) ?: PasswordResetFragment()
        replaceWithBackStack(tag, fragment)
    }

    fun attachPasswordUpdateFragment() {
        val tag = PasswordUpdateFragment::class.java.canonicalName
        val fragment: Fragment = fragmentManager?.findFragmentByTag(tag) ?: PasswordUpdateFragment()
        replaceWithBackStack(tag, fragment)
    }

    fun attachBillingFragment() {
        val tag = BillingFragment::class.java.canonicalName
        val fragment: Fragment = fragmentManager?.findFragmentByTag(tag) ?: BillingFragment()
        val fragmentTransaction: FragmentTransaction? = fragmentManager?.beginTransaction()

        //clearing back stack
        fragmentManager?.popBackStack(null, FragmentManager.POP_BACK_STACK_INCLUSIVE)

        fragmentTransaction?.replace(fragmentContainer!!, fragment, tag)
        fragmentTransaction?.commit()
    }

    fun attachAccountActivation(userInput: HashMap<String, String>) {
        val tag = AccountActivationFragment::class.java.canonicalName
        var fragment: Fragment? = fragmentManager?.findFragmentByTag(tag)
        if (fragment != null) {
            fragment.arguments = AccountActivationFragment.getBundle(userInput)
        } else {
            fragment = AccountActivationFragment.newInstance(userInput)
        }
        replaceWithBackStack(tag, fragment)
    }

    fun showConfirmationDialog(dialogType: AlertDialogType) {
        val tag = "$confirmationDialogPrefix${dialogType.name}"
        val dialog: DialogFragment? = fragmentManager?.findFragmentByTag(tag) as? DialogFragment
        if (dialog == null) {
            ConfirmationDialog.newInstance(dialogType).show(fragmentManager, tag)
        } else {
            if (!dialog.isAdded) {
                dialog.show(fragmentManager, tag)
            }
        }
    }

    fun attachLastFragment(authScreenType: AuthScreenType, camFlow: CamFlow) {
        val fragmentTransaction: FragmentTransaction? = fragmentManager?.beginTransaction()
        val fragmentList = fragmentManager?.fragments
        if (fragmentList?.size != 0) {
            val lastFragment = fragmentList?.last().takeIf {
                it?.tag?.contains(confirmationDialogPrefix) ?: false
            }
            if (lastFragment != null) {
                val fragment = fragmentList?.get(fragmentList.size - 2)
                fragment?.apply {
                    val tag = this.javaClass.canonicalName
                    fragmentTransaction?.replace(fragmentContainer!!, fragment, tag)
                    fragmentTransaction?.commit()
                }
            } else {
                val fragment = fragmentList?.last()
                fragment?.apply {
                    val tag = this.javaClass.canonicalName
                    fragmentTransaction?.replace(fragmentContainer!!, fragment, tag)
                    fragmentTransaction?.commit()
                }
            }
        } else {
            when (camFlow) {
                CamFlow.AUTHENTICATION -> attachByScreenType(authScreenType)
                CamFlow.AUTH_AND_STOREFRONT -> attachByScreenType(authScreenType)
                CamFlow.STOREFRONT -> attachBillingFragment()
                CamFlow.LOGOUT -> showConfirmationDialog(AlertDialogType.RESET_PASSWORD)
                else -> baseActivity.close()
            }
        }
    }

    private fun replaceWithBackStack(tag: String?, fragment: Fragment) {
        fragmentContainer?.let {
            val fragmentTransaction: FragmentTransaction? = fragmentManager?.beginTransaction()
            fragmentTransaction?.addToBackStack(tag)
            fragmentTransaction?.replace(it, fragment, tag)
            fragmentTransaction?.commit()
        }
    }

    fun callFragmentBackPressed() {
        if (isLastFragment())
            fragmentManager?.fragments?.forEach { (it as? BaseFragment)?.onLastFragmentClosed() }
    }

    private fun isLastFragment(): Boolean = fragmentManager?.backStackEntryCount == 0

    private fun attachByScreenType(authScreenType: AuthScreenType) {
        when (authScreenType) {
            AuthScreenType.LOGIN -> attachLoginFragment(true)
            AuthScreenType.SIGNUP -> attachSignUpFragment(true)
            else -> {
                Log.e(TAG, "Illegal AuthScreenType value: [${authScreenType.name}] was set as function parameter!")
                throw IllegalArgumentException("Illegal AuthScreenType value: [${authScreenType.name}] was set as function parameter!")
            }
        }
    }
}