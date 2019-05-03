package com.applicaster.cam.ui.billing.adapter

import android.view.View

interface IBillingAdapter {

    fun addPurchaseItems(items: List<BillingItem>)

    fun removeAllPurchaseItems()

    fun setItemListener(item: BillingItem, holderView: View)
}