package com.applicaster.cam.ui.billing.adapter.recycler

import android.view.View
import com.applicaster.util.ui.CustomTextView
import kotlinx.android.synthetic.main.billing_item.view.*

class BillingItemRedeemViewHolder(itemView: View) : BillingItemViewHolder(itemView) {
    var tvRedeem: CustomTextView = itemView.tv_billing_item_redeem
    var ivLabel: CustomTextView = itemView.tv_billing_item_label
}