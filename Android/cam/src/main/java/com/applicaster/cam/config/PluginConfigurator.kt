package com.applicaster.cam.config

import com.applicaster.cam.params.auth.AuthFieldConfig
import com.applicaster.cam.params.auth.AuthFieldsConverter
import com.applicaster.cam.params.auth.AuthScreenType

class PluginConfigurator(private val pluginConfig: Map<String, String>) : Configurator {

    //dummy
    override fun getDefaultAuthScreen() = AuthScreenType.UNDEFINED

    override fun isFacebookLoginRequired() =
        pluginConfig.getValue(KEY_FACEBOOK_LOGIN_REQ).toBoolean()

    override fun isPasswordResetRequired() =
        pluginConfig.getValue(KEY_PASSWORD_RESET_REQ).toBoolean()

    override fun getSignInAuthFields(): AuthFieldConfig {
        val jsonConfig = pluginConfig.getValue(KEY_AUTH_FIELDS)
        return AuthFieldsConverter.getFromJsonString(jsonConfig, AuthScreenType.SIGNUP)
    }

    override fun getLoginAuthFields(): AuthFieldConfig {
        val jsonConfig = pluginConfig.getValue(KEY_AUTH_FIELDS)
        return AuthFieldsConverter.getFromJsonString(jsonConfig, AuthScreenType.LOGIN)
    }
}

const val KEY_AUTH_FIELDS = "auth_fields"
const val KEY_PASSWORD_RESET_REQ = "pwd_reset_required"
const val KEY_FACEBOOK_LOGIN_REQ = "facebook_login_required"