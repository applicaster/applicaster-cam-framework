package com.applicaster.zapp.configfetcher.screenmetadata.service

import com.google.gson.JsonObject
import kotlinx.coroutines.experimental.Deferred
import retrofit2.Response
import retrofit2.http.GET
import retrofit2.http.Url

interface CustomConfigLoaderService {
    @GET
    fun loadCustomFieldsJson(@Url url: String): Deferred<Response<JsonObject>>
}
