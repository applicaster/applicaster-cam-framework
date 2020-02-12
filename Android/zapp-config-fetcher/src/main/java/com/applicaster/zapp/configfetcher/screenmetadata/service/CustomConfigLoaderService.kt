package com.applicaster.zapp.configfetcher.screenmetadata.service

import com.google.gson.JsonObject
import retrofit2.Response
import retrofit2.http.GET
import retrofit2.http.Url

interface CustomConfigLoaderService {
    @GET
    suspend fun loadCustomFieldsJson(@Url url: String): Response<JsonObject>
}
