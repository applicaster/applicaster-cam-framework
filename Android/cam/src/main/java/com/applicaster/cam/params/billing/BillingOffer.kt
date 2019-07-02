package com.applicaster.cam.params.billing

enum class ProductType {
    SUBS,
    INAPP
}

data class BillingOffer(
    var authId: String,
    var productId: String,
    var productType: ProductType
)