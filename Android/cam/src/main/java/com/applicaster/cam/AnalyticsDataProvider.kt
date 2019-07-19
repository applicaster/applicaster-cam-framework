package com.applicaster.cam

import com.applicaster.cam.analytics.PurchaseType

enum class Trigger(val value: String) {
    TAP_SELL("Tap Cell"),
    APP_LAUNCH("App Launch"),
    OTHER("Other")
}

interface AnalyticsDataProvider {
    fun getEntityType(): String
    fun getEntityName(): String
    fun getTrigger(): Trigger
    fun isUserSubscribed(): Boolean
    fun getPurchaseData(): List<PurchaseData>
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