package com.applicaster.cam


enum class ProductType {
    SUBS,
    INAPP
}

data class Offer(
    var productId: String,
    var productType: ProductType
)