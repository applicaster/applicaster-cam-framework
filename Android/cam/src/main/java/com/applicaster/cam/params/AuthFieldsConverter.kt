package com.applicaster.cam.params

import org.json.JSONObject

object AuthFieldsConverter {

    fun getFromJsonString(authDataJson: String, configType: AuthScreenType): AuthFieldConfig {
        val jsonArray = JSONObject(authDataJson).getJSONArray(configType.getKey())
        val authFields: MutableList<AuthField> = ArrayList()
        for (i in 0 until jsonArray.length()) {

            (jsonArray.get(i) as JSONObject).let {
                authFields.add(
                    AuthField().apply {
                        key = it.getString("key")
                        title = it.getString("title")
                        hint = it.getString("hint")
                        mandatory = it.getBoolean("mandatory")
                        type = enumValueOf(it.getString("type"))
                    })
            }
        }
        return AuthFieldConfig(authFields, configType)
    }
}