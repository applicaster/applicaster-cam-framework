package com.applicaster.cam.ui.billing

import android.app.Activity
import android.content.ActivityNotFoundException
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
import com.applicaster.cam.ui.base.view.ContainerType
import com.applicaster.cam.ui.billing.adapter.PurchaseItem
import com.applicaster.cam.ui.billing.adapter.recycler.AdapterPurchaseData
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

    private val TAG = "BillingPresenter"

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
            // TODO: for current impl redeem feature is frozen. TBD: Add proper UI & logic, update contract
//			if (camContract.isRedeemActivated())
//				BillingItemType.REDEEM
//			else
            BillingItemType.NO_REDEEM
        }.invoke()

        view?.initViewComponents(view.getFragmentContainerType(), billingItemType)
        view?.customize()
        view?.populateCustomLinksContainer()

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
    }

    override fun onBillingClientError(statusCode: Int, description: String) {
        Log.e(TAG, "onBillingClientError: $statusCode $description")
        view?.hideLoadingIndicator()
        view?.showAlert(ContentAccessManager.pluginConfigurator.getDefaultAlertText())
    }

    override fun onPurchaseButtonClicked(activity: Activity?, skuId: String) {
        skuDetailsList.find { skuDetails ->
            skuDetails.sku == skuId
        }?.also { skuDetails ->
            if (activity != null) GoogleBillingHelper.purchase(activity, skuDetails)
            // Analytics events
            AnalyticsUtil.collectPurchaseData(camContract.getAnalyticsDataProvider().purchaseData).forEach {
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
                        AlertType.ERROR_ALERT,
                        AnalyticsUtil.KEY_NONE_PROVIDED,
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
                //Analytics
                AnalyticsGatewaySession.sessionData.add(Action.FAILED_ATTEMPT)
            }

            override fun onActionSuccess() {
                //Analytics call
                AnalyticsUtil.collectPurchaseData(camContract.getAnalyticsDataProvider().purchaseData, purchases).forEach {
                    AnalyticsUtil.logCompletePurchase(it)
                }
                AnalyticsUtil.logUserProperties(
                        AnalyticsUtil.collectPurchaseData(
                                ContentAccessManager.contract.getAnalyticsDataProvider().purchaseData
                        ))
                AnalyticsGatewaySession.sessionData.add(Action.PURCHASE)
                //
                view?.hideLoadingIndicator()
                if (ContentAccessManager.pluginConfigurator.isShowConfirmationPayment()) {
                    navigationRouter.showConfirmationDialog(AlertDialogType.BILLING)
                } else {
                    view?.close()
                }
            }
        })
    }

    override fun onPurchasesRestored(purchases: List<Purchase>) {
        view?.hideLoadingIndicator()

        AnalyticsGatewaySession.sessionData.add(Action.RESTORE_PURCHASE)

        if (!handleRestoringPurchasesError(purchases)) { //purchase succeed
            view?.showLoadingIndicator()
            ContentAccessManager.contract.onPurchasesRestored(purchases, this)
        }
    }

    private fun sendPurchasesRestoredAnalytics() {
        AnalyticsUtil.collectPurchaseData(
                camContract.getAnalyticsDataProvider().purchaseData
        ).forEach {
            AnalyticsUtil.logCompleteRestorePurchase(it)
        }
    }

    private fun sendRestoreFailureAnalytics(msg: String) {
        AnalyticsUtil.collectPurchaseData(
                camContract.getAnalyticsDataProvider().purchaseData
        ).forEach {
            AnalyticsUtil.logStoreRestorePurchaseError(msg, it)
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
                // not an error
                Log.i(TAG, "Restored legacy item")
            }
        }
        return purchaseSucceed
    }

    override fun onPurchaseLoadingFailed(statusCode: Int, description: String) {
        view?.showAlert(ContentAccessManager.pluginConfigurator.getDefaultAlertText())
        sendPurchaseLoadingFailureAnalytics(statusCode, description)
    }

    private fun sendPurchaseLoadingFailureAnalytics(statusCode: Int, description: String) {
        AnalyticsUtil.logViewAlert(
                ConfirmationAlertData(
                        false,
                        AlertType.ERROR_ALERT,
                        AnalyticsUtil.KEY_NONE_PROVIDED,
                        ContentAccessManager.pluginConfigurator.getDefaultAlertText(),
                        description
                )
        )
        //Analytics
        if (statusCode == BillingClient.BillingResponse.USER_CANCELED) {
            AnalyticsUtil.collectPurchaseData(camContract.getAnalyticsDataProvider().purchaseData).forEach {
                AnalyticsUtil.logCancelPurchase(it)
            }
        } else {
            AnalyticsUtil.collectPurchaseData(camContract.getAnalyticsDataProvider().purchaseData).forEach {
                AnalyticsUtil.logStorePurchaseError(statusCode.toString(), description, it)
            }
        }
    }

    override fun onSkuDetailsLoaded(skuDetails: List<SkuDetails>) {
        skuDetailsList.addAll(skuDetails)

        val purchaseItems = skuDetails.map {
            PurchaseItem(
                    it.sku,
                    it.title,
                    it.description,
                    it.price,
                    ""
            )
        }
        updateViewWithPurchasesData(purchaseItems)
        view?.hideLoadingIndicator()
    }

    private fun updateViewWithPurchasesData(purchaseItems: List<PurchaseItem>) {
        view?.calculateRecyclerContainerPadding(purchaseItems.size)
        val adapterPurchaseData = purchaseItems.toAdapterData()
        if (isNeedToShowCustomLinksFooter(purchaseItems)) {
            adapterPurchaseData.add(AdapterPurchaseData.CustomLinksFooter())
            view?.hideCustomLinksContainer()
        } else {
            view?.populateCustomLinksContainer()
        }
        view?.populateBillingContainer(adapterPurchaseData)
    }

    private fun List<PurchaseItem>.toAdapterData(): MutableList<AdapterPurchaseData> {
        val adapterData: MutableList<AdapterPurchaseData> = arrayListOf()
        return adapterData.apply {
            addAll(this@toAdapterData.map {
                AdapterPurchaseData.PurchaseItemData().apply { setItem(it) }
            })
        }
    }

    private fun isNeedToShowCustomLinksFooter(purchaseItems: List<PurchaseItem>) =
            purchaseItems.size > 1 && view?.getFragmentContainerType() == ContainerType.PHONE

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

    private fun showHandledError(description: String = "", apiMsg: String = "") {
        Log.e(TAG, "Handled error: $description  $apiMsg")
        view?.showAlert(
                if (description.isEmpty())
                    ContentAccessManager.pluginConfigurator.getDefaultAlertText()
                else
                    description
        )
        // Analytics events
        AnalyticsUtil.logViewAlert(ConfirmationAlertData(
                false,
                AlertType.ERROR_ALERT,
                AnalyticsUtil.KEY_NONE_PROVIDED,
                if (description.isNotEmpty()) description else AnalyticsUtil.KEY_NONE_PROVIDED,
                if (apiMsg.isNotEmpty()) apiMsg else AnalyticsUtil.KEY_NONE_PROVIDED
        ))
    }

    /**
     * Restore action failed on Cleeng side
     */
    override fun onFailure(msg: String) {
        Log.e(TAG, "onFailure: $msg")
        view?.hideLoadingIndicator()
        view?.showAlert(msg)
        sendRestoreFailureAnalytics(msg)
    }

    /**
     * Restore action succeeded on Cleeng side
     */
    override fun onActionSuccess() {
        view?.hideLoadingIndicator()
        sendPurchasesRestoredAnalytics()
        if (ContentAccessManager.pluginConfigurator.isShowConfirmationRestorePurchases()) {
            navigationRouter.showConfirmationDialog(AlertDialogType.RESTORE)
            // Analytics events
            AnalyticsUtil.logUserProperties(
                    AnalyticsUtil.collectPurchaseData(
                            ContentAccessManager.contract.getAnalyticsDataProvider().purchaseData
                    ))
        } else {
            view?.goBack()
        }
    }

    override fun onRestoreClicked() {
        view?.showLoadingIndicator()
        AnalyticsUtil.logTapRestorePurchaseLink()
        GoogleBillingHelper.restorePurchasesForAllTypes()
    }

    //Calls when user press system back button or toolbar back button
    override fun onLastFragmentClosed() {
        AnalyticsGatewaySession.sessionData.add(Action.CANCEL)
    }

    override fun onCustomLinkClicked(linkText: String, linkUrl: String) {
        AnalyticsUtil.logTapCustomLink(CustomLinkData(linkUrl, linkText, ScreenName.STOREFRONT))
        try {
            navigationRouter.openBrowserWithUrl(linkUrl)
        } catch (exception: ActivityNotFoundException) {
            view?.showAlert(ContentAccessManager.pluginConfigurator.getDefaultAlertText())
        } catch (exception: NullPointerException) {
            view?.showAlert(ContentAccessManager.pluginConfigurator.getDefaultAlertText())
        }
    }
}