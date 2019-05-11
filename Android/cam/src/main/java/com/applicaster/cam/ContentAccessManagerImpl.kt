package com.applicaster.cam

import android.content.Context
import android.content.Intent
import com.applicaster.cam.params.AuthFieldConfig
import com.applicaster.cam.params.AuthFieldsConverter
import com.applicaster.cam.params.AuthScreenType
import com.applicaster.cam.ui.CamActivity

object ContentAccessManagerImpl : ContentAccessManager {
    private lateinit var contract: CamContract
    private lateinit var configurationProvider: CamConfigurationProvider

    override fun onProcessStarted(contract: CamContract, configurationProvider: CamConfigurationProvider, context: Context) {
        this.contract = contract
        this.configurationProvider = configurationProvider

        startCamActivity(context)
    }

    fun getSignInAuthFields(): AuthFieldConfig {
        val jsonConfig = configurationProvider.getAuthFieldsConfig()
        return AuthFieldsConverter.getFromJsonString(jsonConfig, AuthScreenType.SIGNUP)
    }

    fun getLoginAuthFields(): AuthFieldConfig {
        val jsonConfig = configurationProvider.getAuthFieldsConfig()
        return AuthFieldsConverter.getFromJsonString(jsonConfig, AuthScreenType.LOGIN)
    }

    fun getContract(): CamContract = this.contract

    private fun startCamActivity(context: Context) {
        val intent = Intent(context, CamActivity::class.java).apply { flags = Intent.FLAG_ACTIVITY_NEW_TASK }
        context.startActivity(intent)
    }
}
