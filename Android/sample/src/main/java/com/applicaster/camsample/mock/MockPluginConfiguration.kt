package com.applicaster.camsample.mock

import android.content.Context
import com.applicaster.cam.config.KEY_AUTH_FIELDS
import com.applicaster.cam.config.KEY_FACEBOOK_LOGIN_REQ
import com.applicaster.cam.config.KEY_PASSWORD_RESET_REQ
import org.json.JSONObject
import java.io.IOException
import java.nio.charset.Charset


object MockPluginConfiguration {

    fun getPluginConfiguration() = mapOf(
        KEY_AUTH_FIELDS to getAuthFieldsConfig(),
        KEY_PASSWORD_RESET_REQ to "true",
        KEY_FACEBOOK_LOGIN_REQ to "true"
    )

    fun getAuthFieldsConfig(): String {
        return "{\"signup\":[{\"type\":\"TEXT\",\"key\":\"email\",\"title\":\"Email\",\"hint\":\"Email\",\"mandatory\":true},{\"type\":\"PASSWORD\",\"key\":\"password\",\"title\":\"Password\",\"hint\":\"Password\",\"mandatory\":true},{\"type\":\"NUMBER\",\"key\":\"phone\",\"title\":\"Phone\",\"hint\":\"Phone\",\"mandatory\":true},{\"type\":\"TEXT\",\"key\":\"gender\",\"title\":\"Gender\",\"hint\":\"Gender\",\"mandatory\":false}],\"login\":[{\"type\":\"TEXT\",\"key\":\"email\",\"title\":\"Email\",\"hint\":\"Email\",\"mandatory\":true},{\"type\":\"PASSWORD\",\"key\":\"password\",\"title\":\"Password\",\"hint\":\"Password\",\"mandatory\":true}]}"
        /**
         * raw formatted:
         *
         *
        {
        "signup": [
        {
        "type": "TEXT",
        "key": "email",
        "title": "Email",
        "hint": "Email",
        "mandatory": true
        },
        {
        "type": "PASSWORD",
        "key": "password",
        "title": "Password",
        "hint": "Password",
        "mandatory": true
        },
        {
        "type": "NUMBER",
        "key": "phone",
        "title": "Phone",
        "hint": "Phone",
        "mandatory": true
        },
        {
        "type": "TEXT",
        "key": "gender",
        "title": "Gender",
        "hint": "Gender",
        "mandatory": false
        }
        ],
        "login": [
        {
        "type": "TEXT",
        "key": "email",
        "title": "Email",
        "hint": "Email",
        "mandatory": true
        },
        {
        "type": "PASSWORD",
        "key": "password",
        "title": "Password",
        "hint": "Password",
        "mandatory": true
        }
        ]
        }
         *
         */
    }

    fun getPluginConfig(context: Context): JSONObject {
        val inputStream = context.resources.openRawResource(com.applicaster.camsample.R.raw.mock_config)
        val size = inputStream.available()

        var json: String? = null

        try {
            val buffer = ByteArray(size)
            inputStream.read(buffer)
            inputStream.close()

            json = String(buffer, Charset.forName("UTF-8"))
        } catch (e: IOException) {
            e.printStackTrace()
        }
//        Toast.makeText(context, json, Toast.LENGTH_LONG).show()
        val obj = JSONObject(json)
        return obj
    }
}