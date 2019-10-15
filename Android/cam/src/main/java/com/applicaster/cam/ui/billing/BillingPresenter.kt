package com.applicaster.cam.ui.billing

import android.app.Activity
import android.util.Log
import com.android.billingclient.api.BillingClient
import com.android.billingclient.api.Purchase
import com.android.billingclient.api.SkuDetails
import com.applicaster.cam.*
import com.applicaster.cam.analytics.*
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
        view?.initBackButton(!ContentAccessManager.pluginConfigurator.isTriggerOnAppLaunch())

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
                showHandledError(msg)
            }

            override fun onSuccess(billingOffers: List<BillingOffer>) {
                fetchSkuDetailsByType(billingOffers)
            }
        })
        view?.showLoadingIndicator()
        AnalyticsUtil.logUserProperties(
            collectPurchaseData(
                ContentAccessManager.contract.getAnalyticsDataProvider().purchaseData
            ))
    }

    override fun onBillingClientError(statusCode: Int, description: String) {
        view?.hideLoadingIndicator()
        view?.showAlert(ContentAccessManager.pluginConfigurator.getDefaultAlertText())
    }

    override fun onPurchaseButtonClicked(activity: Activity?, skuId: String) {
        skuDetailsList.find { skuDetails ->
            skuDetails.sku == skuId
        }?.also { skuDetails ->
            if (activity != null) GoogleBillingHelper.purchase(activity, skuDetails)
            // Analytics events
            collectPurchaseData(camContract.getAnalyticsDataProvider().purchaseData).forEach {
                AnalyticsUtil.logTapPurchaseButton(it)
            }
        }
    }

    override fun onPurchaseConsumed(purchaseToken: String) {
        Log.i(TAG, "PurchaseConsumed")
    }

    override fun onPurchaseConsumptionFailed(statusCode: Int, description: String) {
        Log.e(TAG, "PurchaseConsumptionFailed: $description")
        // Analytics events
        AnalyticsUtil.logViewAlert(
                ConfirmationAlertData(
                        false,
                        ConfirmationCause.NONE,
                        AnalyticsUtil.KEY_NON_PROVIDED,
                        ContentAccessManager.pluginConfigurator.getDefaultAlertText(),
                        description
                )
        )
    }

    override fun onPurchaseLoaded(purchases: List<Purchase>) {
        view?.showLoadingIndicator()
        camContract.onItemPurchased(purchases, object : PurchaseCallback {
            override fun onFailure(msg: String) {
                view?.hideLoadingIndicator()
                showHandledError(msg)
            }

            override fun onActionSuccess() {
                view?.hideLoadingIndicator()
                if (ContentAccessManager.pluginConfigurator.isShowConfirmationPayment()) {
                    navigationRouter.showConfirmationDialog(AlertDialogType.BILLING)
                } else {
                    view?.close()
                }
            }
        })
        collectPurchaseData(camContract.getAnalyticsDataProvider().purchaseData, purchases).forEach {
            AnalyticsUtil.logCompletePurchase(it)
        }
    }

    override fun onPurchasesRestored(purchases: List<Purchase>) {
        view?.hideLoadingIndicator()

        if (!handleRestoringPurchasesError(purchases)) { //purchase succeed
            view?.showLoadingIndicator()
            ContentAccessManager.contract.onPurchasesRestored(purchases, this)
        }

        // Analytics events
        if (purchases.isEmpty()) {
            collectPurchaseData(camContract.getAnalyticsDataProvider().purchaseData, purchases).forEach {
                AnalyticsUtil.logStoreRestorePurchaseError("Restore purchases error", it)
            }
        } else {
            collectPurchaseData(
                    camContract.getAnalyticsDataProvider().purchaseData,
                    purchases
            ).forEach {
                AnalyticsUtil.logCompleteRestorePurchase(it)
            }
        }
    }

    private fun handleRestoringPurchasesError(purchases: List<Purchase>): Boolean {
        var purchaseSucceed = false
        if (purchases.isEmpty()) {
            showHandledError(ContentAccessManager.pluginConfigurator.getNoPurchasesToRestoreText())
            purchaseSucceed = true
        } else {
            val isNonMatchingRestoredPurchasesExists = skuDetailsList.none { details ->
                purchases.find { purchase -> details.sku == purchase.sku } != null
            }
            if (isNonMatchingRestoredPurchasesExists) {
                showHandledError(ContentAccessManager.pluginConfigurator.getNonMatchingRestoredPurchasesText())
                purchaseSucceed = true
            }
        }
        return purchaseSucceed
    }

    override fun onPurchaseLoadingFailed(statusCode: Int, description: String) {
        view?.showAlert(ContentAccessManager.pluginConfigurator.getDefaultAlertText())

        // Analytics events
        AnalyticsUtil.logViewAlert(
                ConfirmationAlertData(
                        false,
                        ConfirmationCause.NONE,
                        AnalyticsUtil.KEY_NON_PROVIDED,
                        ContentAccessManager.pluginConfigurator.getDefaultAlertText(),
                        description
                )
        )
        if (statusCode == BillingClient.BillingResponse.USER_CANCELED) {
            collectPurchaseData(camContract.getAnalyticsDataProvider().purchaseData).forEach {
                AnalyticsUtil.logCancelPurchase(it)
            }
        } else {
            collectPurchaseData(camContract.getAnalyticsDataProvider().purchaseData).forEach {
                AnalyticsUtil.logStorePurchaseError(statusCode.toString(), description, it)
            }
        }
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

    private fun showHandledError(msg: String) {
        if (msg.isEmpty()) {
            view?.showAlert(ContentAccessManager.pluginConfigurator.getDefaultAlertText())

            // Analytics events
            AnalyticsUtil.logViewAlert(
                    ConfirmationAlertData(
                            false,
                            ConfirmationCause.NONE,
                            AnalyticsUtil.KEY_NON_PROVIDED,
                            ContentAccessManager.pluginConfigurator.getDefaultAlertText(),
                            msg
                    )
            )
        } else {
            view?.showAlert(msg)

            // Analytics events
            AnalyticsUtil.logViewAlert(
                    ConfirmationAlertData(
                            false,
                            ConfirmationCause.NONE,
                            AnalyticsUtil.KEY_NON_PROVIDED,
                            AnalyticsUtil.KEY_NON_PROVIDED,
                            msg
                    )
            )
        }
    }

    /**
     * Purchase verification failed on Cleeng side
     */
    override fun onFailure(msg: String) {
        view?.hideLoadingIndicator()
        view?.showAlert(msg)
    }

    /**
     * Purchase verification succeeded on Cleeng side
     */
    override fun onActionSuccess() {
        view?.hideLoadingIndicator()
        if (ContentAccessManager.pluginConfigurator.isShowConfirmationRestorePurchases()) {
            navigationRouter.showConfirmationDialog(AlertDialogType.RESTORE)
            // Analytics events
            AnalyticsUtil.logViewAlert(
                    ConfirmationAlertData(
                            true,
                            ConfirmationCause.RESTORE_PURCHASE,
                            ContentAccessManager.pluginConfigurator.getPaymentConfirmationTitle(),
                            ContentAccessManager.pluginConfigurator.getPaymentConfirmationDescription(),
                            AnalyticsUtil.KEY_NON_PROVIDED
                    )
            )
        } else {
            view?.goBack()
        }
    }
    //

    override fun onRestoreClicked() {
        view?.showLoadingIndicator()
        AnalyticsUtil.logTapRestorePurchaseLink()
        AnalyticsUtil.logContentGatewaySession(
            TimedEvent.START,
            Trigger.OTHER.value,
            Action.RESTORE_PURCHASE
        )
        GoogleBillingHelper.restorePurchasesForAllTypes()
    }

    // Analytics related function
    private fun collectPurchaseData(
            purchasesData: List<PurchaseData>,
            purchases: List<Purchase> = arrayListOf()
    ): List<PurchaseProductPropertiesData> {
        val result: ArrayList<PurchaseProductPropertiesData> = arrayListOf()
        purchasesData.forEach { data ->
            val productData = PurchaseProductPropertiesData(
                    camContract.getAnalyticsDataProvider().isUserSubscribed,
                    data.title,
                    data.price,
                    purchases.find { it.sku == data.androidProductId }?.orderId ?: AnalyticsUtil.KEY_NON_PROVIDED,
                    data.androidProductId,
                    data.purchaseType,
                    data.subscriptionDuration,
                    data.trialPeriod,
                    data.purchaseEntityType
            )
            result.add(productData)
        }
        return result
    }

    override fun onLastFragmentClosed() {
        when (ContentAccessManager.contract.getCamFlow()) {
            CamFlow.STOREFRONT -> {
                AnalyticsUtil.logContentGatewaySession(
                    TimedEvent.END,
                    ContentAccessManager.contract.getAnalyticsDataProvider().trigger.value,
                    Action.PURCHASE
                )
            }
            CamFlow.AUTH_AND_STOREFRONT -> {
                AnalyticsUtil.logContentGatewaySession(
                    TimedEvent.END,
                    ContentAccessManager.contract.getAnalyticsDataProvider().trigger.value,
                    Action.SIGNUP_AND_PURCHASE
                )
            }
            else -> {}
        }
    }
}