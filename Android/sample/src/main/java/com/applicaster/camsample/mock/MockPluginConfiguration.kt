package com.applicaster.camsample.mock

import com.applicaster.cam.config.KEY_AUTH_FIELDS
import com.applicaster.cam.config.KEY_FACEBOOK_LOGIN_REQ
import com.applicaster.cam.config.KEY_PASSWORD_RESET_REQ

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

}