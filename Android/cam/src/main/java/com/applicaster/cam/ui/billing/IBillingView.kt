package com.applicaster.cam.ui.billing

import com.applicaster.cam.ui.base.view.ContainerType
import com.applicaster.cam.ui.base.view.IBaseView
import com.applicaster.cam.ui.billing.adapter.recycler.AdapterPurchaseData
import com.applicaster.cam.ui.billing.adapter.recycler.BillingItemType

interface IBillingView : IBaseView {
    fun setListeners()
    fun initViewComponents(containerType: ContainerType, billingItemType: BillingItemType)
    fun populateBillingContainer(purchaseItems: List<AdapterPurchaseData>)
    fun clearBillingContainer()
    fun calculateRecyclerContainerPadding(itemsCount: Int) {}
    fun initBackButton(enable: Boolean)
    fun populateCustomLinksContainer()
    fun hideCustomLinksContainer()
}