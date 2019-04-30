package com.applicaster.cam

import com.applicaster.cam.params.AuthScreenType

interface CamConfigurationProvider {

    fun isTriggerOnAppLaunch(): Boolean

    fun isUserLogged(): Boolean

    fun getDefaultAuthScreen(): AuthScreenType

    fun isConfirmationScreenRequired(): Boolean

    fun isPasswordResetRequired(): Boolean

    fun isFacebookLoginRequired(): Boolean

    fun getAuthFieldsConfig(): String //json with auth data

    fun getEntitlements() //get purchase id (and corresponding data)

    fun isEntitlementsValid() //discuss the differences on diagram

    fun getUIConfig(): Map<String, String>
}