package com.applicaster.cam.params.auth

enum class AuthScreenType {
    LOGIN,
    SIGNUP,
    ACCOUNT_ACTIVATION,
    PASSWORD_RESET,
    PASSWORD_UPDATE,
    UNDEFINED;

    fun getKey(): String {
        return when (this) {
            LOGIN -> "Login"
            SIGNUP -> "Sign-up"
            ACCOUNT_ACTIVATION -> "Account-activation"
            PASSWORD_RESET -> "Password-reset"
            PASSWORD_UPDATE -> "Password-update"
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
                "Account-activation" -> ACCOUNT_ACTIVATION
                "Password-reset" -> PASSWORD_RESET
                "Password-update" -> PASSWORD_UPDATE
                else -> UNDEFINED
            }
        }
    }
}
