package com.applicaster.cam.ui.billing

import android.app.Activity
import com.applicaster.cam.ui.base.presenter.IBasePresenter

interface IBillingPresenter : IBasePresenter {
    fun onPurchaseButtonClicked(activity: Activity?, skuId: String)
    fun onRestoreClicked()
}