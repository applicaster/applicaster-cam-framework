package com.applicaster.cam.params.auth

enum class AuthScreenType {
    LOGIN,
    SIGNUP,
    PASSWORD_RESET,
    UNDEFINED;

    fun getKey(): String {
        return when (this) {
            LOGIN -> "login"
            SIGNUP -> "signup"
            PASSWORD_RESET -> "password_reset"
            else -> "undefined"
        }
    }

    companion object {
        fun fromKey(key: String): AuthScreenType {
            return when (key) {
                "login" -> LOGIN
                "signup" -> SIGNUP
                "password_reset" -> PASSWORD_RESET
                else -> UNDEFINED
            }
        }
    }
}
