package com.applicaster.cam

import com.applicaster.cam.params.AuthField
import com.applicaster.cam.params.AuthFieldsConverter

class ContentAccessManagerImpl : ContentAccessManager {
    private lateinit var contract: CamContract
    private lateinit var configurationProvider: CamConfigurationProvider

    override fun onProcessStarted(contract: CamContract, configurationProvider: CamConfigurationProvider) {
        this.contract = contract
        this.configurationProvider = configurationProvider
    }

    private fun getSignInAuthFields(): List<AuthField> {
        val jsonConfig = configurationProvider.getAuthFieldsConfig()
        return AuthFieldsConverter.getFromJsonString(jsonConfig)
    }
}
