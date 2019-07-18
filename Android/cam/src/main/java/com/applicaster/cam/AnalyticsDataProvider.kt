package com.applicaster.cam

enum class Trigger {

}

interface AnalyticsDataProvider {
    fun getEntityType(): String
    fun getEntityName(): String
    fun getTrigger(): Trigger
}