package com.applicaster.cam.ui.billing.adapter.recycler

import android.support.v7.widget.RecyclerView
import android.view.View
import android.widget.Button
import com.applicaster.util.ui.CustomTextView
import kotlinx.android.synthetic.main.billing_item.view.*

open class BillingItemViewHolder(itemView: View) : RecyclerView.ViewHolder(itemView) {
    var cardLayout: View = itemView.layout_billing_item
    var tvTitle: CustomTextView = itemView.tv_billing_item_title
    var tvDetails: CustomTextView = itemView.tv_billing_item_details
    var btnSubscribe: Button = itemView.btn_billing_item_subscribe
}