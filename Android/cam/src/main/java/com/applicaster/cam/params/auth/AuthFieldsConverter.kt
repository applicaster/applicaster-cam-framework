package com.applicaster.cam.params.auth

import android.util.Log
import org.json.JSONException
import org.json.JSONObject

class AuthFieldsConverter {
    companion object {
        fun getFromJsonString(authDataJson: String, configType: AuthScreenType): AuthFieldConfig {
            val configJson = JSONObject(authDataJson)
            val authFields: MutableList<AuthField> = mutableListOf()
            if (configJson.has(configType.getKey())) {
                val jsonArray = JSONObject(authDataJson).getJSONArray(configType.getKey())
                for (i in 0 until jsonArray.length()) {
                    try {
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
                    } catch (parseException: JSONException) {
                        Log.d(
                            "AuthFieldsConverter",
                            "Failed to parse value from $configType. Original JSON: $authDataJson"
                        )
                    }
                }
            }
            return AuthFieldConfig(authFields)
        }
    }
}