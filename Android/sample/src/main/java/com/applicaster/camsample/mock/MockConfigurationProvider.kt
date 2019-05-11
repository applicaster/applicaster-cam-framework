package com.applicaster.camsample.mock

import com.applicaster.cam.CamConfigurationProvider
import com.applicaster.cam.params.AuthScreenType

class MockConfigurationProvider : CamConfigurationProvider {
    override fun isTriggerOnAppLaunch(): Boolean = false

    override fun isUserLogged(): Boolean = false

    override fun getDefaultAuthScreen(): AuthScreenType = AuthScreenType.SIGNUP

    override fun isConfirmationScreenRequired(): Boolean = true

    override fun isPasswordResetRequired(): Boolean = true

    override fun isFacebookLoginRequired(): Boolean = true

    override fun getAuthFieldsConfig(): String {
        return "[{\"type\":\"TEXT\",\"key\":\"email\",\"title\":\"Email\",\"hint\":\"Email\",\"mandatory\":true},{\"type\":\"PASSWORD\",\"key\":\"password\",\"title\":\"Password\",\"hint\":\"Password\",\"mandatory\":true},{\"type\":\"NUMBER\",\"key\":\"phone\",\"title\":\"Phone\",\"hint\":\"Phone\",\"mandatory\":true},{\"type\":\"TEXT\",\"key\":\"gender\",\"title\":\"Gender\",\"hint\":\"Gender\",\"mandatory\":false}]"

        /**
         * raw formatted:
         *
         * [
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
        ]
         *
         */
    }

    override fun isEntitlementsValid() {
        TODO("not implemented") //To change body of created functions use File | Settings | File Templates.
    }

    override fun getUIConfig(): Map<String, String> {
        TODO("not implemented") //To change body of created functions use File | Settings | File Templates.
    }
}