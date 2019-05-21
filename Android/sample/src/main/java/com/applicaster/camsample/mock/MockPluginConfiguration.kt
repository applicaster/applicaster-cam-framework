package com.applicaster.camsample.mock

import android.content.Context
import com.applicaster.cam.config.KEY_AUTH_FIELDS
import com.applicaster.cam.config.KEY_FACEBOOK_LOGIN_REQ
import com.applicaster.cam.config.KEY_PASSWORD_RESET_REQ
import org.json.JSONObject
import java.io.IOException
import java.nio.charset.Charset


object MockPluginConfiguration {

    fun getPluginConfiguration(context: Context): Map<String, String> =
        Gson().fromJson(getConfigFromAssets(context), Map::class.java) as Map<String, String>


    private fun getConfigFromAssets(context: Context): String {
        val inputStream =
            context.resources.openRawResource(R.raw.mock_config)
        val size = inputStream.available()

        val json: String?

        try {
            val buffer = ByteArray(size)
            inputStream.read(buffer)
            inputStream.close()

            json = String(buffer, Charset.forName("UTF-8"))
        } catch (e: IOException) {
            e.printStackTrace()
            return ""
        }

        return json
    }

    /**
     * raw formatted auth config
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