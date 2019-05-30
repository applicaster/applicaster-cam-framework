package com.applicaster.cam.ui.confirmation

import android.app.Activity
import android.app.Dialog
import android.content.Context
import android.os.Bundle
import android.support.v4.app.DialogFragment
import android.support.v7.app.AlertDialog
import android.view.View
import com.applicaster.cam.R
import com.applicaster.cam.config.ui.UIKey
import com.applicaster.cam.config.ui.UIMapper
import com.applicaster.cam.ui.base.view.IBaseActivity
import kotlinx.android.synthetic.main.layout_confirmation.view.*

enum class AlertDialogType {
    BILLING,
    RESET_PASSWORD,
    RESTORE,
    UNDEFINED
}

class ConfirmationDialog : DialogFragment() {

    private var baseActivity: IBaseActivity? = null
    private var dialogView: View? = null
    private lateinit var dialogType: AlertDialogType

    override fun onCreateDialog(savedInstanceState: Bundle?): Dialog {
        dialogType = AlertDialogType.valueOf(arguments?.getString(KEY_TYPE) ?: AlertDialogType.UNDEFINED.name)
        return activity?.let {
            setUpDialogView(it)
            setUpListeners()
            customize()
            // Use the Builder class for convenient dialog construction
            with(AlertDialog.Builder(it)) {
                setView(dialogView)
            }.create()
        } ?: throw IllegalStateException("Activity cannot be null")
    }

    private fun setUpDialogView(activity: Activity) {
        val view = activity.layoutInflater.inflate(R.layout.layout_confirmation, null)
        this.dialogView = view
    }

    private fun setUpListeners() {
        dialogView?.btn_confirmation_ok?.setOnClickListener {
            dismiss()
            baseActivity?.goBack()
        }
    }

    fun customize() {
        when (dialogType) {
            AlertDialogType.BILLING -> {
                UIMapper.apply {
                    map(dialogView?.layout_confirmation_background!!, UIKey.BILLING_CONFIRMATION_IMAGE)
                    map(dialogView?.tv_confirmation_title!!, UIKey.BILLING_CONFIRMATION_TITLE_TEXT)
                    map(dialogView?.tv_confirmation_desc!!, UIKey.BILLING_CONFIRMATION_DESC_TEXT)
                    map(dialogView?.btn_confirmation_ok!!, UIKey.BILLING_CONFIRMATION_BUTTON_TEXT)
                }
            }
            AlertDialogType.RESET_PASSWORD -> {
                UIMapper.apply {
                    map(dialogView?.layout_confirmation_background!!, UIKey.BILLING_CONFIRMATION_IMAGE)
                    map(dialogView?.tv_confirmation_title!!, UIKey.RESET_PWD_CONFIRMATION_TITLE_TEXT)
                    map(dialogView?.tv_confirmation_desc!!, UIKey.RESET_PWD_CONFIRMATION_DESC_TEXT)
                    map(dialogView?.btn_confirmation_ok!!, UIKey.RESET_PWD_CONFIRMATION_BUTTON_TEXT)
                }
            }
            AlertDialogType.RESTORE -> {
                UIMapper.apply {
                    map(dialogView?.layout_confirmation_background!!, UIKey.BILLING_CONFIRMATION_IMAGE)
                    map(dialogView?.tv_confirmation_title!!, UIKey.RESTORE_CONFIRMATION_TITLE_TEXT)
                    map(dialogView?.tv_confirmation_desc!!, UIKey.RESTORE_CONFIRMATION_DESC_TEXT)
                    map(dialogView?.btn_confirmation_ok!!, UIKey.RESTORE_CONFIRMATION_BUTTON_TEXT)
                }
            }
            AlertDialogType.UNDEFINED -> {
            }
        }
    }

    override fun onAttach(context: Context?) {
        super.onAttach(context)
        baseActivity = context as? IBaseActivity
    }

    override fun onDetach() {
        super.onDetach()
        baseActivity = null
    }

    companion object {
        const val KEY_TYPE = "key_dialog_type"

        fun newInstance(dialogType: AlertDialogType): ConfirmationDialog {
            return ConfirmationDialog().apply {
                val extras = Bundle()
                extras.putString(KEY_TYPE, dialogType.name)
                arguments = extras
            }
        }
    }
}