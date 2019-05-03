package com.applicaster.cam.ui.billing.adapter.recycler

import android.support.v7.widget.RecyclerView
import android.view.LayoutInflater
import android.view.View
import android.view.ViewGroup
import com.applicaster.cam.R
import com.applicaster.cam.ui.billing.adapter.BillingItem
import com.applicaster.cam.ui.billing.adapter.IBillingAdapter
import com.applicaster.cam.ui.billing.adapter.PurchaseInteractionListener

class RecyclerBillingAdapter(
    private val purchaseListener: PurchaseInteractionListener
) : RecyclerView.Adapter<RecyclerView.ViewHolder>(),
    IBillingAdapter {

    private val billingItemsList: ArrayList<BillingItem> = arrayListOf()

    override fun onCreateViewHolder(parent: ViewGroup, viewType: Int): RecyclerView.ViewHolder {
        val itemView = LayoutInflater.from(parent.context).inflate(R.layout.billing_item, parent, false)
        return BillingItemViewHolder(itemView)
    }

    override fun getItemCount(): Int = billingItemsList.size

    override fun onBindViewHolder(holder: RecyclerView.ViewHolder, position: Int) {
        if (holder is BillingItemViewHolder) {
            val billingItem = billingItemsList[holder.adapterPosition]
            holder.tvTitle.text = billingItem.productTitle
            holder.tvDetails.text = billingItem.productDescription
            holder.btnSubscribe.text = billingItem.productPrice

            setItemListener(billingItem, holder.btnSubscribe)
        }
    }

    override fun addPurchaseItems(items: List<BillingItem>) {
        billingItemsList.addAll(items)
        notifyDataSetChanged()
    }

    override fun removeAllPurchaseItems() {
        billingItemsList.clear()
        notifyDataSetChanged()
    }

    override fun setItemListener(item: BillingItem, holderView: View) {
        holderView.setOnClickListener { purchaseListener.onPurchaseButtonClicked(item.productId) }
    }
}