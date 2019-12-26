package com.applicaster.cam

import com.applicaster.cam.analytics.PurchaseType

enum class Trigger(val value: String) {
    // @formatter:off
    TAP_SELL  ("Tap Cell"),
    APP_LAUNCH("App Launch"),
    UAC       ("User Accounts Component"),
    OTHER     ("Other")
    // @formatter:on
}

interface IAnalyticsDataProvider {
    var entityType: String
    var entityName: String
    var trigger: Trigger
    val isUserSubscribed: Boolean
    var purchaseData: MutableList<PurchaseData>
}

data class PurchaseData(
    val title: String,
    val price: String,
    val description: String,
    val androidProductId: String,
    val subscriptionDuration: String,
    val purchaseType: PurchaseType,
    val trialPeriod: String,
    val purchaseEntityType: String
)