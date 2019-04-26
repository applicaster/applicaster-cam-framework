package com.applicaster.cam

class ContentAccessManagerImpl : ContentAccessManager {
    private var contract: CamContract? = null
    private var configurationProvider: CamConfigurationProvider? = null

    override fun onProcessStarted(contract: CamContract, configurationProvider: CamConfigurationProvider) {
        this.contract = contract
        this.configurationProvider = configurationProvider
    }
}
