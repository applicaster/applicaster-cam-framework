package com.applicaster.cam

import com.applicaster.cam.params.AuthField
import com.applicaster.cam.params.AuthFieldConfig
import com.applicaster.cam.params.AuthFieldsConverter
import com.applicaster.cam.params.AuthScreenType

object ContentAccessManagerImpl : ContentAccessManager {
    private lateinit var contract: CamContract
    private lateinit var configurationProvider: CamConfigurationProvider

    override fun onProcessStarted(contract: CamContract, configurationProvider: CamConfigurationProvider) {
        this.contract = contract
        this.configurationProvider = configurationProvider
    }

    fun getSignInAuthFields(): AuthFieldConfig {
        val jsonConfig = configurationProvider.getAuthFieldsConfig()
        return AuthFieldsConverter.getFromJsonString(jsonConfig, AuthScreenType.SIGNUP)
    }

    fun getLoginAuthFields(): AuthFieldConfig {
        val jsonConfig = configurationProvider.getAuthFieldsConfig()
        return AuthFieldsConverter.getFromJsonString(jsonConfig, AuthScreenType.LOGIN)
    }
}
