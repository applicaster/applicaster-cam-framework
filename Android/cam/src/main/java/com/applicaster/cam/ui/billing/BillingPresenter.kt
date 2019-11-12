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
						ConfirmationCause.NONE,
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
		//Analytics call
		AnalyticsUtil.collectPurchaseData(camContract.getAnalyticsDataProvider().purchaseData, purchases).forEach {
			AnalyticsUtil.logCompletePurchase(it)
		}
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
		sendPurchaseLoadingFailureAnalytics(statusCode, description)
	}

	private fun sendPurchaseLoadingFailureAnalytics(statusCode: Int, description: String) {
		AnalyticsUtil.logViewAlert(
				ConfirmationAlertData(
						false,
						ConfirmationCause.NONE,
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

	private fun showHandledError(description: String = "", apiMsg: String = "") {
		view?.showAlert(
				if (apiMsg.isEmpty())
					ContentAccessManager.pluginConfigurator.getDefaultAlertText()
				else
					apiMsg
		)
		// Analytics events
		AnalyticsUtil.logViewAlert(ConfirmationAlertData(
				false,
				ConfirmationCause.NONE,
				AnalyticsUtil.KEY_NONE_PROVIDED,
				if (description.isNotEmpty()) description else AnalyticsUtil.KEY_NONE_PROVIDED,
				if (apiMsg.isNotEmpty()) apiMsg else AnalyticsUtil.KEY_NONE_PROVIDED
		))
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
		sendPurchasesRestoredAnalytics()
		if (ContentAccessManager.pluginConfigurator.isShowConfirmationRestorePurchases()) {
			navigationRouter.showConfirmationDialog(AlertDialogType.RESTORE)
			// Analytics events
			AnalyticsUtil.logUserProperties(
					AnalyticsUtil.collectPurchaseData(
							ContentAccessManager.contract.getAnalyticsDataProvider().purchaseData
					))

			AnalyticsUtil.logViewAlert(
					ConfirmationAlertData(
							true,
							ConfirmationCause.RESTORE_PURCHASE,
							ContentAccessManager.pluginConfigurator.getPaymentConfirmationTitle(),
							ContentAccessManager.pluginConfigurator.getPaymentConfirmationDescription(),
							AnalyticsUtil.KEY_NONE_PROVIDED
					)
			)
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
}