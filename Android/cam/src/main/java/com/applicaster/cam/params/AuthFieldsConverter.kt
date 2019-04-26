package com.applicaster.cam.params

import org.json.JSONArray
import org.json.JSONObject

object AuthFieldsConverter {

    fun getFromJsonString(authDataJson: String): List<AuthField> {
        val jsonArray = JSONArray(authDataJson)
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
        return authFields
    }
}