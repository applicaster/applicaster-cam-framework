package com.applicaster.zapp.configfetcher.screenmetadata.model


import com.google.gson.annotations.SerializedName

data class ScreenData(
    @SerializedName("general")
    val general: Any?,

    @SerializedName("type")
    val type: String?
)