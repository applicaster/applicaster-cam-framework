package com.applicaster.cam.ui.billing.adapter.recycler

import android.support.v7.widget.RecyclerView
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

data class AdapterPurchaseData(val value: PurchaseItem?) {
    fun isEmptyFooterItem() = value == null
}

class RecyclerBillingAdapter(
        private val purchaseListener: PurchaseInteractionListener,
        private val customLinksListener: ICustomLinkActionHandler?,
        private val itemType: BillingItemType
) : RecyclerView.Adapter<RecyclerView.ViewHolder>(),
        IBillingAdapter {

    enum class BillingViewType(val value: Int) {
        BILLING_VIEW(0),
        FOOTER_VIEW(1);

        companion object {
            fun fromInt(value: Int) = values().first { it.value == value }
        }
    }

    private val purchaseItemsList: ArrayList<AdapterPurchaseData> = arrayListOf()

    override fun onCreateViewHolder(parent: ViewGroup, viewType: Int): RecyclerView.ViewHolder {
        return when (BillingViewType.fromInt(viewType)) {
            BillingViewType.BILLING_VIEW -> {
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
            BillingViewType.FOOTER_VIEW -> {
                val itemView =
                        LayoutInflater.from(parent.context).inflate(R.layout.layout_bottom_links, parent, false)
                CustomLinksViewHolder(itemView)
            }
        }
    }

    override fun getItemViewType(position: Int)
            : Int {
        return if (position < purchaseItemsList.size && !purchaseItemsList[position].isEmptyFooterItem()) BillingViewType.BILLING_VIEW.ordinal else BillingViewType.FOOTER_VIEW.ordinal
    }

    override fun getItemCount()
            : Int = purchaseItemsList.size

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
                    purchaseListener.onPurchaseButtonClicked(billingItem.value?.productId.orEmpty())
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
        holder.tvTitle.text = purchaseItemsList[holder.adapterPosition].value?.productTitle
        holder.tvDetails.text = purchaseItemsList[holder.adapterPosition].value?.productDescription
        val btnSubscribeText = holder.btnSubscribe.text
        holder.btnSubscribe.text = updateItemPrice(
                btnSubscribeText.toString(),
                purchaseItemsList[holder.adapterPosition].value?.productPrice.orEmpty()
        )
    }

    private fun updateItemPrice(subsBtnText: String, productPrice: String) =
            "$subsBtnText $productPrice"
}