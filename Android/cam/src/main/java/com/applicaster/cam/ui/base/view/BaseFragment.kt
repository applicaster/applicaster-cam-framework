package com.applicaster.cam.ui.base.view

import android.annotation.SuppressLint
import android.content.Context
import android.graphics.Color
import android.graphics.drawable.ColorDrawable
import android.os.Bundle
import android.support.v4.app.Fragment
import android.support.v4.content.ContextCompat.getSystemService
import android.support.v7.app.AlertDialog
import android.view.View
import android.view.ViewGroup
import android.view.inputmethod.InputMethodManager
import android.widget.Toast
import com.applicaster.cam.R
import com.applicaster.cam.ui.base.presenter.IBasePresenter

abstract class BaseFragment : Fragment(), IBaseView {

    protected var baseActivity: IBaseActivity? = null
    private var basePresenter: IBasePresenter? = null
    private var toast: Toast? = null
    private var progressDialog: AlertDialog? = null

    protected fun setPresenter(presenter: IBasePresenter?) {
        basePresenter = presenter
    }

    override fun onAttach(context: Context?) {
        super.onAttach(context)
        baseActivity = context as? IBaseActivity
    }

    override fun onDetach() {
        super.onDetach()
        baseActivity = null
    }

    override fun onViewCreated(view: View, savedInstanceState: Bundle?) {
        super.onViewCreated(view, savedInstanceState)
        basePresenter?.onViewCreated()
    }

    override fun onPause() {
        super.onPause()
        basePresenter?.onViewPaused()
    }

    override fun onStop() {
        super.onStop()
        basePresenter?.onViewStopped()
    }

    override fun onResume() {
        super.onResume()
        basePresenter?.onViewResumed()
    }

    override fun onDestroy() {
        basePresenter?.onViewDestroyed()
        super.onDestroy()
    }

    override fun getViewContext(): Context? {
        return context
    }

    override fun customize() {
        makeFullscreen(getParentView())
    }

    @SuppressLint("ShowToast")
    override fun showToastMessage(msg: String) {
        if (isAdded && context != null && !activity?.isFinishing!!) {
            if (toast == null) {
                toast = Toast.makeText(context, msg, Toast.LENGTH_SHORT)
            } else {
                toast?.setText(msg)
                toast?.duration = Toast.LENGTH_SHORT
            }
            toast?.show()
        }
    }

    override fun showAlert(msg: String) {
        context?.apply {
            val builder = AlertDialog.Builder(this)
            builder
                .setMessage(msg)
                .setPositiveButton(getString(R.string.lbl_okay)) { dialog, _ -> dialog.dismiss() }
                .create().apply {
                    show()
                }
        }
    }

    override fun showLoadingIndicator() {
        context?.apply {
            if (progressDialog == null) {
                val builder = AlertDialog.Builder(this)
                builder.setView(R.layout.layout_progress)
                progressDialog = builder.create()
                progressDialog?.window?.setBackgroundDrawable(ColorDrawable(Color.TRANSPARENT))
            }
            progressDialog?.show()
        }
    }

    override fun hideLoadingIndicator() {
        progressDialog?.dismiss()
    }

    override fun getFragmentContainerType() = baseActivity?.getFragmentContainerType() ?: ContainerType.PHONE

    override fun goBack() {
        baseActivity?.goBack()
    }

    override fun close() {
        baseActivity?.close()
    }

    private fun makeFullscreen(rootLayout: View?) {
        rootLayout?.apply {
            fitsSystemWindows = true
            parent?.requestFitSystemWindows()
        }
    }

    override fun hideKeyboard() {
        // Check if no view has focus:
        view?.rootView?.windowToken?.let {
            val imm = activity?.getSystemService(Context.INPUT_METHOD_SERVICE) as? InputMethodManager
            imm?.hideSoftInputFromWindow( it, 0)
        }
    }

    protected abstract fun setListeners()
    protected abstract fun getParentView(): ViewGroup?
}