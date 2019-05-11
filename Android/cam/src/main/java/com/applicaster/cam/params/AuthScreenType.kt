package com.applicaster.cam.params

enum class AuthScreenType {
    LOGIN,
    SIGNUP,
    UNDEFINED;

    fun getKey(): String {
        return when (this) {
            AuthScreenType.LOGIN -> "login"
            AuthScreenType.SIGNUP -> "signup"
            else -> "undefined"
        }
    }
}
