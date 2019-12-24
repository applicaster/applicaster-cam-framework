package com.applicaster.cam.ui.billing.adapter

import android.view.View
import com.applicaster.cam.ui.billing.adapter.recycler.AdapterPurchaseData
import com.applicaster.cam.ui.billing.adapter.recycler.BillingItemType

interface IBillingAdapter {

    fun addPurchaseItems(items: List<AdapterPurchaseData>)

    fun removeAllPurchaseItems()

    fun customize(itemView: View, itemType: BillingItemType)
}