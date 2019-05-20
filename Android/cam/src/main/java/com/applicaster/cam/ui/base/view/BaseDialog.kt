package com.applicaster.cam.ui.base.view

import android.app.Dialog
import android.os.Bundle
import android.support.v4.app.DialogFragment
import android.support.v7.app.AlertDialog
import android.view.View

class BaseDialog : DialogFragment() {

    private var dialogView: View? = null

    fun newInstance(args: Bundle? = null): BaseDialog {
        val dialog = BaseDialog()
        args?.let {
            dialog.arguments = it
        }
        return dialog
    }

    override fun onCreateDialog(savedInstanceState: Bundle?): Dialog {
        return activity?.let {
            // Use the Builder class for convenient dialog construction
            with(AlertDialog.Builder(it)) {
                setView(dialogView)
                setPositiveButton("") { _, _ -> dismiss() }
            }.create()
        } ?: throw IllegalStateException("Activity cannot be null")
    }

    fun show(tag: String? = null) {
        super.show(activity?.supportFragmentManager, tag)
    }

    fun bindView(view: View) {
        this.dialogView = view
    }
}