package com.applicaster.cam.params.auth

enum class AuthScreenType {
    LOGIN,
    SIGNUP,
    PASSWORD_RESET,
    UNDEFINED;

    fun getKey(): String {
        return when (this) {
            LOGIN -> "Login"
            SIGNUP -> "Sign-up"
            PASSWORD_RESET -> "Password-reset"
            else -> "undefined"
        }
    }

    companion object {
        fun fromKey(key: String): AuthScreenType {
            return when (key) {
                "login" -> LOGIN
                "Login" -> LOGIN
                "signup" -> SIGNUP
                "Sign-up" -> SIGNUP
                "Password-reset" -> PASSWORD_RESET
                else -> UNDEFINED
            }
        }
    }
}
