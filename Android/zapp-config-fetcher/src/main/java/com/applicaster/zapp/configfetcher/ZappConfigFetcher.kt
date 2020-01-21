package com.applicaster.zapp.configfetcher

import android.content.Context
import android.util.Log
import com.applicaster.plugin_manager.Plugin
import com.applicaster.plugin_manager.PluginManager
import com.applicaster.zapp.configfetcher.screenmetadata.ScreensDataLoader
import com.google.gson.Gson
import org.json.JSONObject

class ZappConfigFetcher(private val pluginIdentifier: String? = null) : IConfigFetcher {
    private val screenLoader: ScreensDataLoader by lazy { ScreensDataLoader(getPluginIdentifier()) }

    override suspend fun loadFullConfig(
            context: Context?,
            showLoadingUI: Boolean,
            hook: HashMap<String, String?>?
    ): Map<String, String> {
        return UIEnvironment(context, showLoadingUI).executeWithResult {
            var screenData = hook?.let { getPluginConfigurationFromHook(hook = it)?.toMutableMap() }
            if (screenData == null || screenData.isEmpty())
                screenData = screenLoader.loadScreensData()?.toMutableMap()
            screenData?.loadAuthConfigJson()
            screenData
        } ?: mapOf()
    }

    override suspend fun MutableMap<String, String>.loadAuthConfigJson(
            context: Context?,
            showLoadingUI: Boolean
    ) {
        UIEnvironment(context, showLoadingUI).execute {
            loadCustomConfigField(key = AUTH_FIELDS_KEY)
        }
    }

    override suspend fun getPluginConfigurationFromHook(
            context: Context?,
            showLoadingUI: Boolean,
            hook: HashMap<String, String?>
    ): Map<String, String>? {
        return UIEnvironment(context, showLoadingUI).executeWithResult {
            val fullPluginConfig =
                    Gson().fromJson(hook["screenMap"].orEmpty(), Map::class.java) as? Map<String, Any>
            val generalConfig: MutableMap<Any?, Any?>? =
                    fullPluginConfig?.get("general") as? MutableMap<Any?, Any?>
            //transform MutableMap<Any?, Any?>? to Map<String, String>?
            generalConfig?.entries?.associate { entry ->
                entry.key.toString() to entry.value.toString()
            }
        }
    }

    override suspend fun MutableMap<String, String>.loadCustomConfigField(
            context: Context?,
            showLoadingUI: Boolean,
            key: String
    ) {
        UIEnvironment(context, showLoadingUI).execute {
            Log.d(this.javaClass.simpleName, "loading plugin config: $this")
            if (this.containsKey(key)) {
                val authConfigLink = this[key]
                authConfigLink?.let {
                    val authFields = screenLoader.loadCustomFieldsJson(it)
                    this[key] = authFields
                }
            }
        }
    }

    override suspend fun loadAWSCustomAuthConfig(
            context: Context?,
            showLoadingUI: Boolean,
            pluginConfig: Map<String, String>?
    ): JSONObject {
        return UIEnvironment(context, showLoadingUI).executeWithResult {
            var result: JSONObject? = null
            if (pluginConfig?.containsKey(AWS_CONFIG_FIELDS_KEY) == true) {
                val configurationString =
                        screenLoader.loadCustomFieldsJson(pluginConfig[AWS_CONFIG_FIELDS_KEY] ?: "")
                result = JSONObject(configurationString)
            }
            result ?: JSONObject()
        }
    }

    /**
     * Return plugin identifier from constructor if it exists, default login plugin identifier otherwise
     */
    private fun getPluginIdentifier(): String {
        return if (pluginIdentifier != null && pluginIdentifier.isNotEmpty())
            pluginIdentifier
        else getLoginPluginIdentifier()
    }

    private fun getLoginPluginIdentifier() =
        PluginManager.getInstance().getInitiatedPlugin(Plugin.Type.LOGIN)?.plugin?.identifier
            ?: throw RuntimeException(
                "Unable to fetch login plugin identifier. " +
                        "Possibly login plugin not initialized or added multiple login plugins."
            )

    companion object {
        private const val AUTH_FIELDS_KEY = "authentication_input_fields"
        private const val AWS_CONFIG_FIELDS_KEY = "aws_configuration_json"
    }
}

