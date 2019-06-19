package com.applicaster.cam.params.auth

class AuthField {
    var key: String? = null
    var title: String? = null
    var hint: String? = null
    var type: Type =
        Type.UNDEFINED
    var mandatory: Boolean? = null

    enum class Type{
        EMAIL,
        TEXT,
        PASSWORD,
        NUMBER,
        UNDEFINED
    }
}