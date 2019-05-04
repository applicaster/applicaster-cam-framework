package com.applicaster.cam.ui.billing

import android.content.Context
import com.android.billingclient.api.Purchase
import com.android.billingclient.api.SkuDetails
import com.applicaster.cam.ui.CamNavigationRouter
import com.applicaster.cam.ui.base.presenter.BasePresenter
import com.applicaster.cam.ui.base.view.BaseActivity
import com.applicaster.iap.BillingListener
import com.applicaster.iap.GoogleBillingHelper

class BillingPresenter(
    private val view: IBillingView,
    private val navigationRouter: CamNavigationRouter
) : BasePresenter(view),
    IBillingPresenter,
    BillingListener{

    private val skuDetailsList: ArrayList<SkuDetails> = arrayListOf()

    override fun onViewCreated() {
        super.onViewCreated()
        GoogleBillingHelper.init(getBaseActivity().applicationContext,this)
        view.setListeners()

        view.initViewComponents(getBaseActivity().getFragmentContainerType())
//        GoogleBillingHelper.loadSkuDetails()
    }

    override fun onPurchaseButtonClicked(skuId: String) {
        skuDetailsList.find {skuDetails ->
            skuDetails.sku == skuId
        }?.also { skuDetails ->
            GoogleBillingHelper.purchase(getBaseActivity(), skuDetails)
        }
    }

    override fun onPurchaseConsumed(purchaseToken: String) {
        TODO("not implemented") //To change body of created functions use File | Settings | File Templates.
    }

    override fun onPurchaseConsumptionFailed(statusCode: Int, description: String) {
        TODO("not implemented") //To change body of created functions use File | Settings | File Templates.
    }

    override fun onPurchaseLoaded(purchases: List<Purchase>) {
        TODO("not implemented") //To change body of created functions use File | Settings | File Templates.
    }

    override fun onPurchaseLoadingFailed(statusCode: Int, description: String) {
        TODO("not implemented") //To change body of created functions use File | Settings | File Templates.
    }

    override fun onSkuDetailsLoaded(skuDetails: List<SkuDetails>) {
        skuDetailsList.addAll(skuDetails)
    }

    override fun onSkuDetailsLoadingFailed(statusCode: Int, description: String) {
        TODO("not implemented") //To change body of created functions use File | Settings | File Templates.
    }

    private fun getViewContext(): Context = view.getViewContext() ?: throw RuntimeException("Context should not be null")

    private fun getBaseActivity(): BaseActivity = getViewContext() as BaseActivity

}