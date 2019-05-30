package com.applicaster.cam.ui.billing

import com.applicaster.cam.ui.base.view.ContainerType
import com.applicaster.cam.ui.base.view.IBaseView
import com.applicaster.cam.ui.billing.adapter.PurchaseItem
import com.applicaster.cam.ui.billing.adapter.recycler.BillingItemType

interface IBillingView : IBaseView {
    fun setListeners()
    fun initViewComponents(containerType: ContainerType, billingItemType: BillingItemType)
    fun populateBillingContainer(purchaseItems: List<PurchaseItem>)
    fun clearBillingContainer()
}