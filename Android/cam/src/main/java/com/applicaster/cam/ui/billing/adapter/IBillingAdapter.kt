package com.applicaster.cam.ui.billing.adapter

import android.view.View

interface IBillingAdapter {

    fun addPurchaseItems(items: List<PurchaseItem>)

    fun removeAllPurchaseItems()

    fun setItemListener(item: PurchaseItem, holderView: View)
}