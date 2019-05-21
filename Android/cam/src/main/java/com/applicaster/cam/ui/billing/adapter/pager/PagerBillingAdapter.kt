package com.applicaster.cam.ui.billing.adapter.pager

import android.support.v4.view.PagerAdapter
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

class PagerBillingAdapter(
    private val purchaseListener: PurchaseInteractionListener
) : PagerAdapter(),
    IBillingAdapter {

    private val purchaseItemsList: ArrayList<PurchaseItem> = arrayListOf()

    override fun isViewFromObject(view: View, obj: Any): Boolean = (view == obj)

    override fun instantiateItem(container: ViewGroup, position: Int): Any {
        val itemView = LayoutInflater.from(container.context).inflate(R.layout.billing_item, container, false)
        container.addView(itemView)
        bindView(purchaseItemsList[position], itemView)
        customize(itemView)
        return itemView
    }

    override fun getCount(): Int = purchaseItemsList.size

    override fun getItemPosition(obj: Any): Int = POSITION_NONE

    private fun bindView(purchaseItem: PurchaseItem, view: View) {
        view.tv_billing_item_title.text = purchaseItem.productTitle
        view.tv_billing_item_details.text = purchaseItem.productDescription
        view.btn_billing_item_subscribe.text = purchaseItem.productPrice

        setItemListener(purchaseItem, view.btn_billing_item_subscribe)
    }

    override fun customize(itemView: View) {
        UIMapper.apply {
            map(itemView.layout_billing_item, UIKey.BILLING_ITEM_PARENT)
            map(itemView.tv_billing_item_title, UIKey.BILLING_ITEM_TITLE)
            map(itemView.tv_billing_item_details, UIKey.BILLING_ITEM_DETAILS)
            map(itemView.tv_billing_item_redeem, UIKey.BILLING_ITEM_REDEEM)
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