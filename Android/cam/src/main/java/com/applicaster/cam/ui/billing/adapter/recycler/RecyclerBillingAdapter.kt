package com.applicaster.cam.ui.billing.adapter.recycler

import android.support.v7.widget.RecyclerView
import android.view.LayoutInflater
import android.view.View
import android.view.ViewGroup
import com.applicaster.cam.R
import com.applicaster.cam.ui.billing.adapter.PurchaseItem
import com.applicaster.cam.ui.billing.adapter.IBillingAdapter
import com.applicaster.cam.ui.billing.adapter.PurchaseInteractionListener

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
            holder.tvTitle.text = billingItem.productTitle
            holder.tvDetails.text = billingItem.productDescription
            holder.btnSubscribe.text = billingItem.productPrice

            setItemListener(billingItem, holder.btnSubscribe)
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