package com.applicaster.cam.params.auth

enum class AuthScreenType {
    LOGIN,
    SIGNUP,
    UNDEFINED;

    fun getKey(): String {
        return when (this) {
            LOGIN -> "login"
            SIGNUP -> "signup"
            else -> "undefined"
        }
    }

    companion object {
        fun fromKey(key: String): AuthScreenType {
            return when (key) {
                "login" -> LOGIN
                "signup" -> SIGNUP
                else -> UNDEFINED
            }
        }
    }
}
