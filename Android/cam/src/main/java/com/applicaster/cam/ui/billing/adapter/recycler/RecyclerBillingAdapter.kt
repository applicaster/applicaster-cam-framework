package com.applicaster.cam.ui.billing.adapter.recycler

import android.support.v7.widget.RecyclerView
import android.view.LayoutInflater
import android.view.View
import android.view.ViewGroup
import com.applicaster.cam.R
import com.applicaster.cam.config.ui.UIKey
import com.applicaster.cam.config.ui.UIMapper
import com.applicaster.cam.ui.billing.adapter.PurchaseItem
import com.applicaster.cam.ui.billing.adapter.IBillingAdapter
import com.applicaster.cam.ui.billing.adapter.PurchaseInteractionListener
import kotlinx.android.synthetic.main.billing_item.view.*

class RecyclerBillingAdapter(
    private val purchaseListener: PurchaseInteractionListener
) : RecyclerView.Adapter<RecyclerView.ViewHolder>(),
    IBillingAdapter {

    private val purchaseItemsList: ArrayList<PurchaseItem> = arrayListOf()

    override fun onCreateViewHolder(parent: ViewGroup, viewType: Int): RecyclerView.ViewHolder {
        val itemView = LayoutInflater.from(parent.context).inflate(R.layout.billing_item, parent, false)
        return BillingItemViewHolder(itemView)
    }

    override fun getItemCount(): Int = purchaseItemsList.size

    override fun onBindViewHolder(holder: RecyclerView.ViewHolder, position: Int) {
        if (holder is BillingItemViewHolder) {
            val billingItem = purchaseItemsList[holder.adapterPosition]
            customize(holder.itemView)

            setItemListener(billingItem, holder.btnSubscribe)
        }
    }

    override fun customize(itemView: View) {
        UIMapper.apply {
            map(itemView.layout_billing_item, UIKey.BILLING_ITEM_PARENT)
            map(itemView.tv_billing_item_title, UIKey.BILLING_ITEM_TITLE)
            map(itemView.tv_billing_item_details, UIKey.BILLING_ITEM_DETAILS_TEXT)
            map(itemView.tv_billing_item_redeem, UIKey.BILLING_ITEM_REDEEM_TEXT)
            map(itemView.btn_billing_item_subscribe, UIKey.BILLING_ITEM_SUBS_BUTTON)
        }
    }

    override fun addPurchaseItems(items: List<PurchaseItem>) {
        purchaseItemsList.addAll(items)
        notifyDataSetChanged()
    }

    override fun removeAllPurchaseItems() {
        purchaseItemsList.clear()
        notifyDataSetChanged()
    }

    override fun setItemListener(item: PurchaseItem, holderView: View) {
        holderView.setOnClickListener { purchaseListener.onPurchaseButtonClicked(item.productId) }
    }
}