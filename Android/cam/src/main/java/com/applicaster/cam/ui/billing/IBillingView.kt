package com.applicaster.cam.ui.billing

import android.content.Context
import com.applicaster.cam.ui.base.view.ContainerType
import com.applicaster.cam.ui.base.view.IBaseView
import com.applicaster.cam.ui.billing.adapter.PurchaseItem

interface IBillingView : IBaseView {

    override fun getViewContext(): Context?
    fun setListeners()
    fun initViewComponents(containerType: ContainerType)
    fun populateBillingContainer(purchaseItems: List<PurchaseItem>)
    fun clearBillingContainer()
}