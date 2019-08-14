package com.applicaster.camsample.mock

import com.applicaster.cam.IAnalyticsDataProvider
import com.applicaster.cam.PurchaseData
import com.applicaster.cam.Trigger

class AnalyticsDataProviderMock : IAnalyticsDataProvider {
    override fun getEntityType(): String = ""

    override fun getEntityName(): String = ""

    override fun getTrigger(): Trigger = Trigger.OTHER

    override fun isUserSubscribed(): Boolean = false

    override fun getPurchaseData(): List<PurchaseData> = listOf()
}