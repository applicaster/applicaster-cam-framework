package com.applicaster.zapp.configfetcher.screenmetadata.service

import com.applicaster.zapp.configfetcher.screenmetadata.model.ScreenData
import kotlinx.coroutines.experimental.Deferred
import retrofit2.Response
import retrofit2.http.GET
import retrofit2.http.Url

interface ScreenMetaDataService {
    @GET
    fun loadScreensJson(@Url url: String): Deferred<Response<List<ScreenData>>>
}
