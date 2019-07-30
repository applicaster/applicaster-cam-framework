package com.applicaster.cam.ui.billing

import android.app.Activity
import android.util.Log
import com.android.billingclient.api.BillingClient
import com.android.billingclient.api.Purchase
import com.android.billingclient.api.SkuDetails
import com.applicaster.cam.*
import com.applicaster.cam.params.billing.BillingOffer
import com.applicaster.cam.params.billing.ProductType
import com.applicaster.cam.ui.CamNavigationRouter
import com.applicaster.cam.ui.base.presenter.BasePresenter
import com.applicaster.cam.ui.billing.adapter.PurchaseItem
import com.applicaster.cam.ui.billing.adapter.recycler.BillingItemType
import com.applicaster.cam.ui.confirmation.AlertDialogType
import com.applicaster.iap.BillingListener
import com.applicaster.iap.GoogleBillingHelper

class BillingPresenter(
    private val view: IBillingView?,
    private val navigationRouter: CamNavigationRouter
) : BasePresenter(view),
    IBillingPresenter,
    BillingListener, RestoreCallback {

    private val TAG = BillingPresenter::class.java.canonicalName

    private val skuDetailsList: ArrayList<SkuDetails> = arrayListOf()
    private val camContract: ICamContract = ContentAccessManager.contract

    override fun onViewCreated() {
        super.onViewCreated()
        view?.getViewContext()?.applicationContext?.apply {
            GoogleBillingHelper.init(this, this@BillingPresenter)
        }
        view?.setListeners()

        // obtain redeem code and set billing item type which depends on redeem code availability
        val billingItemType: BillingItemType = {
            if (camContract.isRedeemActivated())
                BillingItemType.REDEEM
            else
                BillingItemType.NO_REDEEM
        }.invoke()

        view?.initViewComponents(view.getFragmentContainerType(), billingItemType)
        view?.customize()

        //load entitlements
        camContract.loadEntitlements(object : EntitlementsLoadCallback {
            override fun onFailure(msg: String) {
                view?.hideLoadingIndicator()
                handleErrorMessage(msg)
            }

            override fun onSuccess(billingOffers: List<BillingOffer>) {
                fetchSkuDetailsByType(billingOffers)
            }
        })
        view?.showLoadingIndicator()
    }

    override fun onPurchaseButtonClicked(activity: Activity?, skuId: String) {
        skuDetailsList.find { skuDetails ->
            skuDetails.sku == skuId
        }?.also { skuDetails ->
            if (activity != null) GoogleBillingHelper.purchase(activity, skuDetails)
        }
    }

    override fun onPurchaseConsumed(purchaseToken: String) {
        Log.i(TAG, "PurchaseConsumed")
    }

    override fun onPurchaseConsumptionFailed(statusCode: Int, description: String) {
        Log.e(TAG, "PurchaseConsumptionFailed: $description")
    }

    override fun onPurchaseLoaded(purchases: List<Purchase>) {
        camContract.onItemPurchased(purchases, object : PurchaseCallback {
            override fun onFailure(msg: String) {
                view?.hideLoadingIndicator()
                handleErrorMessage(msg)
            }

            override fun onSuccess() {
                if (ContentAccessManager.pluginConfigurator.isShowConfirmationPayment())
                    navigationRouter.showConfirmationDialog(AlertDialogType.BILLING)
            }
        })
    }

    override fun onPurchasesRestored(purchases: List<Purchase>) {
        ContentAccessManager.contract.onPurchasesRestored(purchases, this)
        if (ContentAccessManager.pluginConfigurator.isShowConfirmationRestorePurchases()) {
            navigationRouter.showConfirmationDialog(AlertDialogType.RESTORE)
        } else {
            view?.goBack()
        }
    }

    override fun onPurchaseLoadingFailed(statusCode: Int, description: String) {
        view?.showAlert(ContentAccessManager.pluginConfigurator.getDefaultAlertText())
    }

    override fun onSkuDetailsLoaded(skuDetails: List<SkuDetails>) {
        skuDetailsList.addAll(skuDetails)
        view?.populateBillingContainer(skuDetails.map {
            PurchaseItem(
                it.sku,
                it.title,
                it.description,
                it.price,
                ""
            )
        })
        view?.hideLoadingIndicator()
    }

    override fun onSkuDetailsLoadingFailed(statusCode: Int, description: String) {
        view?.hideLoadingIndicator()
        view?.showAlert(ContentAccessManager.pluginConfigurator.getDefaultAlertText())
    }

    private fun fetchSkuDetailsByType(billingOffers: List<BillingOffer>) {
        billingOffers.apply {
            //filter billingOffers by SkuType.SUBS and map result to list of products IDs
            val subs: List<String> = filter { billingOffer: BillingOffer ->
                billingOffer.productType == ProductType.SUBS
            }.map { billingOffer: BillingOffer -> billingOffer.productId }
            GoogleBillingHelper.loadSkuDetails(BillingClient.SkuType.SUBS, subs)

            //filter billingOffers by SkuType.INAPP and map result to list of products IDs
            val inapps: List<String> = filter { billingOffer: BillingOffer ->
                billingOffer.productType == ProductType.INAPP
            }.map { billingOffer: BillingOffer -> billingOffer.productId }
            GoogleBillingHelper.loadSkuDetails(BillingClient.SkuType.INAPP, inapps)
        }
    }

    private fun handleErrorMessage(msg: String) {
        if (msg.isEmpty())
            view?.showAlert(ContentAccessManager.pluginConfigurator.getDefaultAlertText())
        else
            view?.showAlert(msg)
    }

    // restore purchases callback
    override fun onNoPurchasesRestored() {
        view?.showAlert(ContentAccessManager.pluginConfigurator.getNoPurchasesToRestoreText())
    }

    override fun onNonMatchingPurchasesRestored() {
        view?.showAlert(ContentAccessManager.pluginConfigurator.getNonMatchingRestoredPurchasesText())
    }

    override fun onSuccess() {
        view?.hideLoadingIndicator()
        if (ContentAccessManager.pluginConfigurator.isShowConfirmationRestorePurchases())
            navigationRouter.showConfirmationDialog(AlertDialogType.RESTORE)
        else
            view?.goBack()
    }
    //

    override fun onRestoreClicked() {
        GoogleBillingHelper.apply {
            loadPurchases(BillingClient.SkuType.SUBS)
            loadPurchases(BillingClient.SkuType.INAPP)
        }
        view?.showLoadingIndicator()
    }
}