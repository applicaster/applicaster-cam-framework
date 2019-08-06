package com.applicaster.cam

import android.content.Context
import android.content.Intent
import com.applicaster.cam.analytics.AnalyticsUtil
import com.applicaster.cam.config.Configurator
import com.applicaster.cam.config.PluginConfigurator
import com.applicaster.cam.config.flow.CamFlowResolver
import com.applicaster.cam.config.ui.PluginUIProvider
import com.applicaster.cam.config.ui.UIProvider
import com.applicaster.cam.ui.CamActivity
import kotlin.properties.Delegates

object ContentAccessManager : IContentAccessManager {
    var contract: ICamContract by Delegates.notNull()
    var pluginConfigurator: Configurator  by Delegates.notNull()
    var pluginUIProvider: UIProvider by Delegates.notNull()
    var camFlow: CamFlow by Delegates.notNull()

    override fun onProcessStarted(contract: ICamContract, context: Context) {
        this.contract = contract
        pluginConfigurator = PluginConfigurator(contract.getPluginConfig())
        pluginUIProvider = PluginUIProvider(
            contract.getPluginConfig(),
            context.applicationContext
        )
        setCamFlow(contract)
        startCamActivity(context)

        AnalyticsUtil.logLaunchContentGatwayPlugin(this.contract.getAnalyticsDataProvider().getTrigger().value)
    }

    private fun setCamFlow(contract: ICamContract) {
        val originalCamFlow = contract.getCamFlow()
        camFlow = CamFlowResolver.updateFlowByConfig(originalCamFlow, pluginConfigurator)
    }

    private fun startCamActivity(context: Context) {
        val intent =
            Intent(context, CamActivity::class.java).apply { flags = Intent.FLAG_ACTIVITY_NEW_TASK }
        context.startActivity(intent)
    }
}