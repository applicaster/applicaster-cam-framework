package com.applicaster.cam.params

class AuthField {
    var key: String? = null
    var title: String? = null
    var hint: String? = null
    var type: Type = Type.UNDEFINED
    var mandatory: Boolean? = null

    enum class Type{
        TEXT,
        PASSWORD,
        NUMBER,
        UNDEFINED
    }
}