package com.applicaster.cam.ui.billing

import com.applicaster.cam.ui.base.presenter.IBasePresenter

interface IBillingPresenter : IBasePresenter {
    fun onPurchaseButtonClicked(skuId: String)
    fun onRestoreClicked()
}