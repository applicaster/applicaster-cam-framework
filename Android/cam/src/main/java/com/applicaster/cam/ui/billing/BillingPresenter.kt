package com.applicaster.cam.ui.billing

import com.applicaster.cam.ui.CamNavigationRouter
import com.applicaster.cam.ui.base.presenter.BasePresenter

class BillingPresenter(
    private val view: IBillingView,
    private val navigationRouter: CamNavigationRouter
) : BasePresenter(view),
    IBillingPresenter {

    override fun onViewCreated() {
        super.onViewCreated()
    }
}