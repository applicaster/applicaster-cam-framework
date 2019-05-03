package com.applicaster.cam.ui.billing.adapter.pager

import android.support.v4.view.PagerAdapter
import android.view.LayoutInflater
import android.view.View
import android.view.ViewGroup
import com.applicaster.cam.R
import com.applicaster.cam.ui.billing.adapter.BillingItem
import com.applicaster.cam.ui.billing.adapter.IBillingAdapter
import com.applicaster.cam.ui.billing.adapter.PurchaseInteractionListener
import kotlinx.android.synthetic.main.billing_item.view.*

class PagerBillingAdapter(
    private val purchaseListener: PurchaseInteractionListener
) : PagerAdapter(),
    IBillingAdapter {

    private val billingItemsList: ArrayList<BillingItem> = arrayListOf()

    override fun isViewFromObject(view: View, obj: Any): Boolean = (view == obj)

    override fun instantiateItem(container: ViewGroup, position: Int): Any {
        val itemView = LayoutInflater.from(container.context).inflate(R.layout.billing_item, container, false)
        container.addView(itemView)
        bindView(billingItemsList[position], itemView)
        return itemView
    }

    override fun getCount(): Int = billingItemsList.size

    override fun getItemPosition(obj: Any): Int = POSITION_NONE

    private fun bindView(billingItem: BillingItem, view: View) {
        view.tv_billing_item_title.text = billingItem.productTitle
        view.tv_billing_item_details.text = billingItem.productDescription
        view.btn_billing_item_subscribe.text = billingItem.productPrice

        setItemListener(billingItem, view.btn_billing_item_subscribe)
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