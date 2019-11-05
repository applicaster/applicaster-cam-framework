package com.applicaster.cam.ui.confirmation

import android.content.Context
import android.os.Bundle
import android.support.v4.app.DialogFragment
import android.view.LayoutInflater
import android.view.View
import android.view.ViewGroup
import com.applicaster.cam.ContentAccessManager
import com.applicaster.cam.R
import com.applicaster.cam.analytics.AnalyticsUtil
import com.applicaster.cam.analytics.ConfirmationAlertData
import com.applicaster.cam.analytics.ConfirmationCause
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

    override fun onCreate(savedInstanceState: Bundle?) {
        super.onCreate(savedInstanceState)
        dialogType = AlertDialogType.valueOf(arguments?.getString(KEY_TYPE)
                ?: AlertDialogType.UNDEFINED.name)
    }

    override fun onCreateView(inflater: LayoutInflater, container: ViewGroup?, savedInstanceState: Bundle?): View? {
        dialogView = layoutInflater.inflate(R.layout.layout_confirmation, container, false)
        setUpListeners()
        customize()
        return dialogView
    }

    override fun onResume() {
        super.onResume()
        dialog?.let {
            val dialogWidth = resources.getDimension(R.dimen.confirmation_layout_width).toInt()
            val dialogHeight = resources.getDimension(R.dimen.confirmation_layout_height).toInt()
            it.window?.setLayout(dialogWidth, dialogHeight)
            it.setCancelable(false)
        }
    }

    private fun setUpListeners() {
        dialogView?.btn_confirmation_ok?.setOnClickListener {
            dismiss()
            when (dialogType) {
                AlertDialogType.BILLING, AlertDialogType.RESTORE -> baseActivity?.close()
                AlertDialogType.RESET_PASSWORD -> baseActivity?.goBack()
                else -> baseActivity?.goBack()
            }
        }
    }

    private fun customize() {
        when (dialogType) {
            AlertDialogType.BILLING -> {
                UIMapper.apply {
                    map(dialogView?.layout_confirmation_background!!, UIKey.CONFIRMATION_DIALOG_IMAGE)
                    map(dialogView?.tv_confirmation_title!!, UIKey.BILLING_CONFIRMATION_TITLE_TEXT)
                    map(dialogView?.tv_confirmation_desc!!, UIKey.BILLING_CONFIRMATION_DESC_TEXT)
                    map(dialogView?.btn_confirmation_ok!!, UIKey.BILLING_CONFIRMATION_BUTTON_TEXT)
                }
                //Analytics
                AnalyticsUtil.logViewAlert(
                    ConfirmationAlertData(
                        true,
                        ConfirmationCause.PURCHASE,
                        ContentAccessManager.pluginConfigurator.getAlertDialogFields().billingConfirmationTitle,
                        ContentAccessManager.pluginConfigurator.getAlertDialogFields().billingConfirmationDescription,
                        AnalyticsUtil.KEY_NONE_PROVIDED
                    )
                )
                //
            }
            AlertDialogType.RESET_PASSWORD -> {
                UIMapper.apply {
                    map(dialogView?.layout_confirmation_background!!, UIKey.CONFIRMATION_DIALOG_IMAGE)
                    map(dialogView?.tv_confirmation_title!!, UIKey.RESET_PWD_CONFIRMATION_TITLE_TEXT)
                    map(dialogView?.tv_confirmation_desc!!, UIKey.RESET_PWD_CONFIRMATION_DESC_TEXT)
                    map(dialogView?.btn_confirmation_ok!!, UIKey.RESET_PWD_CONFIRMATION_BUTTON_TEXT)
                }
                //Analytics
                AnalyticsUtil.logViewAlert(
                    ConfirmationAlertData(
                        true,
                        ConfirmationCause.PASSWORD_RESET,
                        ContentAccessManager.pluginConfigurator.getAlertDialogFields().pwdResetTitle,
                        ContentAccessManager.pluginConfigurator.getAlertDialogFields().pwdResetDescription,
                        AnalyticsUtil.KEY_NONE_PROVIDED
                    )
                )
                //
            }
            AlertDialogType.RESTORE -> {
                UIMapper.apply {
                    map(dialogView?.layout_confirmation_background!!, UIKey.CONFIRMATION_DIALOG_IMAGE)
                    map(dialogView?.tv_confirmation_title!!, UIKey.RESTORE_CONFIRMATION_TITLE_TEXT)
                    map(dialogView?.tv_confirmation_desc!!, UIKey.RESTORE_CONFIRMATION_DESC_TEXT)
                    map(dialogView?.btn_confirmation_ok!!, UIKey.RESTORE_CONFIRMATION_BUTTON_TEXT)
                }
                //Analytics
                AnalyticsUtil.logViewAlert(
                    ConfirmationAlertData(
                        true,
                        ConfirmationCause.RESTORE_PURCHASE,
                        ContentAccessManager.pluginConfigurator.getAlertDialogFields().restoreConfirmationTitle,
                        ContentAccessManager.pluginConfigurator.getAlertDialogFields().restoreConfirmationDescription,
                        AnalyticsUtil.KEY_NONE_PROVIDED
                    )
                )
                //
            }
            AlertDialogType.UNDEFINED -> Unit
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