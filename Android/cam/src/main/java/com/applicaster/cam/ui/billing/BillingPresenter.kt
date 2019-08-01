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
        view?.hideLoadingIndicator()
        ContentAccessManager.contract.onPurchasesRestored(purchases, this)
        if (!handleRestoringPurchasesError(purchases)) {
            if (ContentAccessManager.pluginConfigurator.isShowConfirmationRestorePurchases()) {
                navigationRouter.showConfirmationDialog(AlertDialogType.RESTORE)
            } else {
                view?.goBack()
            }
        }
    }

    private fun handleRestoringPurchasesError(purchases: List<Purchase>): Boolean {
        var result = false
        if (purchases.isEmpty()) {
            handleErrorMessage(ContentAccessManager.pluginConfigurator.getNoPurchasesToRestoreText())
            result = true
        } else {
            val isNonMatchingRestoredPurchasesExists = skuDetailsList.none { details ->
                purchases.find { purchase -> details.sku == purchase.sku } != null
            }
            if (isNonMatchingRestoredPurchasesExists) {
                handleErrorMessage(ContentAccessManager.pluginConfigurator.getNonMatchingRestoredPurchasesText())
                result = true
            }
        }
        return result
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
            //add billingOffers to skus map and call function for obtaining SkuDetails for these offers
            val skusMap = hashMapOf<String, String>()
            billingOffers.forEach {
                skusMap[it.productId] =
                    if (it.productType == ProductType.INAPP)
                        BillingClient.SkuType.INAPP
                    else
                        BillingClient.SkuType.SUBS
            }

            GoogleBillingHelper.loadSkuDetailsForAllTypes(skusMap)
    }

    private fun handleErrorMessage(msg: String) {
        if (msg.isEmpty())
            view?.showAlert(ContentAccessManager.pluginConfigurator.getDefaultAlertText())
        else
            view?.showAlert(msg)
    }

    override fun onFailure(msg: String) {
        view?.hideLoadingIndicator()
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
        view?.showLoadingIndicator()
        GoogleBillingHelper.restorePurchasesForAllTypes()
    }
}