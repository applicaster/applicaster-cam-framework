package com.applicaster.camsample.mock

import com.applicaster.cam.IAnalyticsDataProvider
import com.applicaster.cam.PurchaseData
import com.applicaster.cam.Trigger

class AnalyticsDataProviderMock : IAnalyticsDataProvider {
    override fun getEntityType(): String {
        TODO("not implemented") //To change body of created functions use File | Settings | File Templates.
    }

    override fun getEntityName(): String {
        TODO("not implemented") //To change body of created functions use File | Settings | File Templates.
    }

    override fun getTrigger(): Trigger {
        TODO("not implemented") //To change body of created functions use File | Settings | File Templates.
    }

    override fun isUserSubscribed(): Boolean {
        TODO("not implemented") //To change body of created functions use File | Settings | File Templates.
    }

    override fun getPurchaseData(): List<PurchaseData> {
        TODO("not implemented") //To change body of created functions use File | Settings | File Templates.
    }
}