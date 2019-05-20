package com.applicaster.cam.params.billing

enum class ProductType {
    SUBS,
    INAPP
}

data class Offer(
    var productId: String,
    var productType: ProductType
)