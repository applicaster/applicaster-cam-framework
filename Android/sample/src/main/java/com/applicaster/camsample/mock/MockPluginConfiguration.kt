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

    fun getConfig(): String =
        "{\"default_auth_screen\": \"login\", \"back_button\": \"back_button\",\"close_button\": \"close_button\",\"header_logo\": \"header_logo\",\"background_image\": \"background_image\",\"separator_text\": \"Or\",\"networks_auth_action_text\": \"Login using social networks\",\"login_screen_title_text\": \"Login To Your Account\",\"reset_password_text\": \"Forgot Password?\",\"alternative_login_promt_text\": \"Dont have an account? Sign UP\",\"login_button_text\": \"Log In\",\"login_button_image\": \"login_button\",\"signup_screen_title_text\": \"Sign UP\",\"signup_button_text\": \"Sign Up\",\"signup_button_image\": \"signup_button\",\"alternative_signup_promt_text\": \"Have already an account? Log In\",\"password_reset_title_text\": \"Reset Password\",\"password_reset_info_text\": \"Type in you e-mail so we would send you the new password\",\"password_reset_button_text\": \"Reset Password\",\"password_reset_button_image\": \"password_reset_button\",\"alert_title_text\": \"Congratulations\",\"alert_info_text\": \"Success\",\"alert_button_text\": \"Ok\",\"alert_button_image\": \"alert_image\",\"auth_fields\": \"{ \"signup\": [{\"type\": \"TEXT\",\"key\": \"email\",\"title\": \"Email\",\"hint\": \"Email\",\"mandatory\": true },{\"type\": \"PASSWORD\",\"key\": \"password\",\"title\": \"Password\",\"hint\": \"Password\",\"mandatory\": true },{\"type\": \"NUMBER\",\"key\": \"Phone\",\"title\": \"Phone\",\"hint\": \"Phone\",\"mandatory\": true},{\"type\": \"TEXT\",\"key\": \"gender\",\"title\": \"Gender\",\"hint\": \"Gender\",\"mandatory\": false }],\"login\": [{\"type\": \"TEXT\",\"key\": \"email\",\"title\": \"Email\",\"hint\": \"Email\",\"mandatory\": true},{\"type\": \"PASSWORD\",\"key\": \"password\",\"title\": \"Password\",\"hint\": \"Password\",\"mandatory\": true},{\"type\": \"NUMBER\",\"key\": \"birthdate\",\"title\": \"Birth Date\",\"hint\": \"Birth Date\",\"mandatory\": true},{\"type\": \"NUMBER\",\"key\": \"birthdate\",\"title\": \"Birth Date\",\"hint\": \"Birth Date\",\"mandatory\": true}, {\"type\": \"NUMBER\",\"key\": \"birthdate\",\"title\": \"Birth Date\",\"hint\": \"Birth Date\",\"mandatory\": true}]}}"
}