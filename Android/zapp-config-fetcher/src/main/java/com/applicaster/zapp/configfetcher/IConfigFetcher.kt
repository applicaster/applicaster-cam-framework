package com.applicaster.zapp.configfetcher

import android.content.Context
import org.json.JSONObject

interface IConfigFetcher {

    suspend fun loadFullConfig(
            context: Context? = null,
            showLoadingUI: Boolean = false,
            hook: HashMap<String, String?>? = null
    ): Map<String, String>

    suspend fun MutableMap<String, String>.loadAuthConfigJson(
            context: Context? = null,
            showLoadingUI: Boolean = false
    )

    suspend fun getPluginConfigurationFromHook(
            context: Context? = null,
            showLoadingUI: Boolean = false,
            hook: HashMap<String, String?>
    ): Map<String, String>?

    suspend fun MutableMap<String, String>.loadCustomConfigField(
            context: Context? = null,
            showLoadingUI: Boolean = false,
            key: String
    )

    suspend fun loadAWSCustomAuthConfig(
            context: Context? = null,
            showLoadingUI: Boolean = false,
            pluginConfig: Map<String, String>?
    ): JSONObject
}