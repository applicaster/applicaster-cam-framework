package com.applicaster.cam.ui.billing

import android.content.Context
import android.util.Log
import com.android.billingclient.api.BillingClient
import com.android.billingclient.api.Purchase
import com.android.billingclient.api.SkuDetails
import com.applicaster.cam.*
import com.applicaster.cam.params.billing.Offer
import com.applicaster.cam.params.billing.ProductType
import com.applicaster.cam.ui.CamNavigationRouter
import com.applicaster.cam.ui.base.presenter.BasePresenter
import com.applicaster.cam.ui.base.view.AlertDialogType
import com.applicaster.cam.ui.base.view.BaseActivity
import com.applicaster.cam.ui.billing.adapter.PurchaseItem
import com.applicaster.iap.BillingListener
import com.applicaster.iap.GoogleBillingHelper

class BillingPresenter(
    private val view: IBillingView,
    private val navigationRouter: CamNavigationRouter
) : BasePresenter(view),
    IBillingPresenter,
    BillingListener {

    private val TAG = BillingPresenter::class.java.canonicalName

    private val skuDetailsList: ArrayList<SkuDetails> = arrayListOf()
    private val camContract: ICamContract = ContentAccessManager.contract

    override fun onViewCreated() {
        super.onViewCreated()
        GoogleBillingHelper.init(getBaseActivity().applicationContext,this)
        view.setListeners()

        view.initViewComponents(getBaseActivity().getFragmentContainerType())
        view.customize()

        //load entitlements
        camContract.loadEntitlements(object : EntitlementsLoadCallback {
            override fun onFailure(msg: String) {
                Log.e(TAG, msg)
            }

            override fun onSuccess(offers: List<Offer>) {
                fetchSkuDetailsByType(offers)
            }
        })
    }

    override fun onPurchaseButtonClicked(skuId: String) {
        skuDetailsList.find { skuDetails ->
            skuDetails.sku == skuId
        }?.also { skuDetails ->
            GoogleBillingHelper.purchase(getBaseActivity(), skuDetails)
        }
        view.showToastMessage("Subscribe button clicked")
        if (ContentAccessManager.pluginConfigurator.isShowConfirmationPayment())
            navigationRouter.showConfirmationDialog(AlertDialogType.BILLING)
    }

    override fun onPurchaseConsumed(purchaseToken: String) {
        TODO("not implemented") //To change body of created functions use File | Settings | File Templates.
    }

    override fun onPurchaseConsumptionFailed(statusCode: Int, description: String) {
        TODO("not implemented") //To change body of created functions use File | Settings | File Templates.
    }

    override fun onPurchaseLoaded(purchases: List<Purchase>) {
        if (ContentAccessManager.pluginConfigurator.isShowConfirmationPayment())
            navigationRouter.showConfirmationDialog(AlertDialogType.BILLING )
    }

    override fun onPurchaseLoadingFailed(statusCode: Int, description: String) {
        TODO("not implemented") //To change body of created functions use File | Settings | File Templates.
    }

    override fun onSkuDetailsLoaded(skuDetails: List<SkuDetails>) {
        skuDetailsList.addAll(skuDetails)
        view.populateBillingContainer(skuDetails.map {
            PurchaseItem(
                it.sku,
                it.title,
                it.description,
                it.price,
                ""
            )
        })
    }

    override fun onSkuDetailsLoadingFailed(statusCode: Int, description: String) {
        TODO("not implemented") //To change body of created functions use File | Settings | File Templates.
    }

    private fun fetchSkuDetailsByType(offers: List<Offer>) {
        offers.apply {
            //filter offers by SkuType.SUBS and map result to list of products IDs
            val subs: List<String> = filter { offer: Offer ->
                offer.productType == ProductType.SUBS
            }.map { offer: Offer -> offer.productId }
            // TODO: needs to implement this line later
//            GoogleBillingHelper.loadSkuDetails(BillingClient.SkuType.SUBS, subs)

            //filter offers by SkuType.INAPP and map result to list of products IDs
            val inapps: List<String> = filter { offer: Offer ->
                offer.productType == ProductType.INAPP
            }.map { offer: Offer -> offer.productId }
            // TODO: needs to implement this line later
//            GoogleBillingHelper.loadSkuDetails(BillingClient.SkuType.INAPP, inapps)
            val purchaseItem = PurchaseItem(
                "Test sku",
                "Test title",
                "Test description",
                "5$",
                ""
            )
            view.populateBillingContainer(arrayListOf(purchaseItem, purchaseItem, purchaseItem))
        }
    }

    override fun onRestoreClicked() {
        view.showToastMessage("Restore clicked")
    }

    private fun getViewContext(): Context = view.getViewContext() ?: throw RuntimeException("Context should not be null")

    private fun getBaseActivity(): BaseActivity = getViewContext() as BaseActivity

}