package com.applicaster.zapp.configfetcher.ui

import android.graphics.Color
import android.graphics.drawable.ColorDrawable
import android.os.Bundle
import android.support.v4.app.DialogFragment
import android.support.v4.app.Fragment
import android.view.LayoutInflater
import android.view.View
import android.view.ViewGroup
import com.applicaster.zapp.configfetcher.R


class TransparentLoadingFragment : DialogFragment() {

    override fun onCreateView(inflater: LayoutInflater, container: ViewGroup?, savedInstanceState: Bundle?): View? {
        dialog?.window?.setBackgroundDrawable(ColorDrawable(Color.TRANSPARENT))
        return layoutInflater.inflate(R.layout.fragment_layout_progress, container, false)
    }

    companion object {
        const val TAG = "LoadingFragment"
        fun newInstance(): TransparentLoadingFragment {
            return TransparentLoadingFragment()
        }
    }
}