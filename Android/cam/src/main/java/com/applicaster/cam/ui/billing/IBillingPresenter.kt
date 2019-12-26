package com.applicaster.cam.ui.billing

import android.app.Activity
import com.applicaster.cam.ui.base.presenter.IBasePresenter
import com.applicaster.cam.ui.base.presenter.ICustomLinkActionHandler

interface IBillingPresenter : IBasePresenter, ICustomLinkActionHandler {
    fun onPurchaseButtonClicked(activity: Activity?, skuId: String)
    fun onRestoreClicked()
}