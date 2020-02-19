package com.applicaster.zapp.configfetcher.screenmetadata.service

import com.applicaster.zapp.configfetcher.screenmetadata.model.ScreenData
import retrofit2.Response
import retrofit2.http.GET
import retrofit2.http.Url

interface ScreenMetaDataService {
    @GET
    suspend fun loadScreensJson(@Url url: String): Response<List<ScreenData>>
}
