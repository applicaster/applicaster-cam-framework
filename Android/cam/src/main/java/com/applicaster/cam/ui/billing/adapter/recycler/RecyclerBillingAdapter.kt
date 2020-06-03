package com.applicaster.cam.ui.billing.adapter.recycler

import androidx.recyclerview.widget.RecyclerView
import android.view.LayoutInflater
import android.view.View
import android.view.ViewGroup
import com.applicaster.cam.R
import com.applicaster.cam.config.ui.UIKey
import com.applicaster.cam.config.ui.UIMapper
import com.applicaster.cam.ui.base.custom.CustomLinkViewCustomizationHelper
import com.applicaster.cam.ui.base.presenter.ICustomLinkActionHandler
import com.applicaster.cam.ui.billing.adapter.IBillingAdapter
import com.applicaster.cam.ui.billing.adapter.PurchaseInteractionListener
import com.applicaster.cam.ui.billing.adapter.PurchaseItem
import kotlinx.android.synthetic.main.billing_item.view.*

enum class BillingItemType {
    REDEEM,
    NO_REDEEM,
}

sealed class AdapterPurchaseData {
    class PurchaseItemData : AdapterPurchaseData() {
        private lateinit var purchaseItem: PurchaseItem
        fun setItem(purchaseItem: PurchaseItem) {
            this.purchaseItem = purchaseItem
        }

        override fun getItem() = purchaseItem
        override fun getIntViewType() = 1
    }

    class CustomLinksFooter : AdapterPurchaseData() {
        override fun getItem() = null
        override fun getIntViewType() = 0
    }

    abstract fun getItem(): PurchaseItem?
    abstract fun getIntViewType(): Int

    companion object {
        fun fromInt(value: Int): AdapterPurchaseData = when (value) {
            1 -> PurchaseItemData()
            0 -> CustomLinksFooter()
            else -> CustomLinksFooter()
        }
    }
}

class RecyclerBillingAdapter(
        private val purchaseListener: PurchaseInteractionListener,
        private val customLinksListener: ICustomLinkActionHandler?,
        private val itemType: BillingItemType
) : RecyclerView.Adapter<RecyclerView.ViewHolder>(),
        IBillingAdapter {

    private val purchaseItemsList: ArrayList<AdapterPurchaseData> = arrayListOf()

    override fun onCreateViewHolder(parent: ViewGroup, viewType: Int): RecyclerView.ViewHolder {
        return when (AdapterPurchaseData.fromInt(viewType)) {
            is AdapterPurchaseData.PurchaseItemData -> {
                when (itemType) {
                    BillingItemType.REDEEM -> {
                        val itemView = LayoutInflater.from(parent.context).inflate(R.layout.billing_item, parent, false)
                        BillingItemRedeemViewHolder(itemView)
                    }
                    BillingItemType.NO_REDEEM -> {
                        val itemView =
                                LayoutInflater.from(parent.context).inflate(R.layout.billing_item_no_redeem, parent, false)
                        BillingItemViewHolder(itemView)
                    }
                }
            }
            is AdapterPurchaseData.CustomLinksFooter -> {
                val itemView =
                        LayoutInflater.from(parent.context).inflate(R.layout.layout_bottom_links, parent, false)
                CustomLinksViewHolder(itemView)
            }
        }
    }

    override fun getItemViewType(position: Int) = purchaseItemsList[position].getIntViewType()

    override fun getItemCount() = purchaseItemsList.size

    override fun onBindViewHolder(holder: RecyclerView.ViewHolder
                                  , position: Int
    ) {
        when (holder) {
            is BillingItemViewHolder -> {
                // customize views
                val billingItem = purchaseItemsList[holder.adapterPosition]
                customize(holder.itemView, itemType)
                // update item title, description and price info that was obtained from store
                updateStoreInfo(holder)
                // init listeners
                holder.btnSubscribe.setOnClickListener {
                    purchaseListener.onPurchaseButtonClicked(billingItem.getItem()?.productId.orEmpty())
                }
            }
            is BillingItemRedeemViewHolder -> {
                // customize views
                customize(holder.itemView, itemType)
                // update item title, description and price info that was obtained from store
                updateStoreInfo(holder)
                // init listeners
                holder.tvRedeem.setOnClickListener { purchaseListener.onRedeemClicked() }
            }
            is CustomLinksViewHolder -> {
                customLinksListener?.let { customizeFooter(holder, it) }
            }
        }
    }

    override fun customize(itemView: View, itemType: BillingItemType) {
        when (itemType) {
            BillingItemType.REDEEM -> {
                UIMapper.apply {
                    map(itemView.layout_billing_item, UIKey.BILLING_ITEM_PARENT)
                    map(itemView.tv_billing_item_title, UIKey.BILLING_ITEM_TITLE)
                    map(itemView.tv_billing_item_details, UIKey.BILLING_ITEM_DETAILS_TEXT)
                    map(itemView.tv_billing_item_redeem, UIKey.BILLING_ITEM_REDEEM_TEXT)
                    map(itemView.btn_billing_item_subscribe, UIKey.BILLING_ITEM_SUBS_BUTTON)
                }
            }
            BillingItemType.NO_REDEEM -> {
                UIMapper.apply {
                    map(itemView.layout_billing_item, UIKey.BILLING_ITEM_PARENT)
                    map(itemView.tv_billing_item_title, UIKey.BILLING_ITEM_TITLE)
                    map(itemView.tv_billing_item_details, UIKey.BILLING_ITEM_DETAILS_TEXT)
                    map(itemView.btn_billing_item_subscribe, UIKey.BILLING_ITEM_SUBS_BUTTON)
                }
            }
        }
    }

    private fun customizeFooter(holder: CustomLinksViewHolder, customLinksListener: ICustomLinkActionHandler) {
        UIMapper.apply {
            map(holder.tvLeftLink, UIKey.STOREFRONT_LINK_1_TEXT, customLinksListener)
            map(holder.tvRightLink, UIKey.STOREFRONT_LINK_2_TEXT, customLinksListener)
        }
        CustomLinkViewCustomizationHelper().customize(holder.tvLeftLink, holder.tvRightLink, holder.parentLayout)
    }

    override fun addPurchaseItems(items: List<AdapterPurchaseData>
    ) {
        purchaseItemsList.addAll(items)
        notifyDataSetChanged()
    }

    override fun removeAllPurchaseItems() {
        purchaseItemsList.clear()
        notifyDataSetChanged()
    }

    private fun updateStoreInfo(holder: BillingItemViewHolder) {
        val skuTitleAppNameRegex = """(?> \(.+?\))$""".toRegex()
        val productTitle = purchaseItemsList[holder.adapterPosition].getItem()?.productTitle
        val titleWithoutAppName = productTitle?.replace(skuTitleAppNameRegex, "")
        holder.tvTitle.text = titleWithoutAppName
        holder.tvDetails.text = purchaseItemsList[holder.adapterPosition].getItem()?.productDescription
        val btnSubscribeText = holder.btnSubscribe.text
        holder.btnSubscribe.text = updateItemPrice(
                btnSubscribeText.toString(),
                purchaseItemsList[holder.adapterPosition].getItem()?.productPrice.orEmpty()
        )
    }

    private fun updateItemPrice(subsBtnText: String, productPrice: String) =
            "$subsBtnText $productPrice"
}