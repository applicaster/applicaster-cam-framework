package com.applicaster.cam.ui.billing

import android.os.Bundle
import android.support.v7.widget.DefaultItemAnimator
import android.support.v7.widget.LinearLayoutManager
import android.view.LayoutInflater
import android.view.View
import android.view.ViewGroup
import com.applicaster.cam.R
import com.applicaster.cam.config.ui.UIKey
import com.applicaster.cam.config.ui.UIMapper
import com.applicaster.cam.ui.CamNavigationRouter
import com.applicaster.cam.ui.base.view.BaseFragment
import com.applicaster.cam.ui.base.view.ContainerType
import com.applicaster.cam.ui.billing.adapter.PurchaseInteractionListener
import com.applicaster.cam.ui.billing.adapter.PurchaseItem
import com.applicaster.cam.ui.billing.adapter.pager.PagerBillingAdapter
import com.applicaster.cam.ui.billing.adapter.recycler.RecyclerBillingAdapter
import kotlinx.android.synthetic.main.fragment_billing.*

class BillingFragment : BaseFragment(), IBillingView {

    private var presenter: IBillingPresenter? = null
    private var recyclerBillingAdapter: RecyclerBillingAdapter? = null
    private var pagerBillingAdapter: PagerBillingAdapter? = null
    private lateinit var purchaseListener: PurchaseInteractionListener


    override fun onCreateView(
        inflater: LayoutInflater,
        container: ViewGroup?,
        savedInstanceState: Bundle?
    ): View? {
        val navigationManager = if (baseActivity.getNavigationRouter() is CamNavigationRouter)
            baseActivity.getNavigationRouter() as CamNavigationRouter
        else
            CamNavigationRouter(baseActivity)

        presenter = BillingPresenter(this, navigationManager)
        setPresenter(presenter)
        return inflater.inflate(R.layout.fragment_billing, container, false)
    }

    override fun setListeners() {
        purchaseListener = object : PurchaseInteractionListener {
            override fun onPurchaseButtonClicked(skuId: String) {
                presenter?.onPurchaseButtonClicked(skuId)
            }
        }
    }

    override fun initViewComponents(containerType: ContainerType) {
        // init toolbar here
        when (containerType) {
            ContainerType.PHONE -> {
                recyclerBillingAdapter = RecyclerBillingAdapter(purchaseListener)
                val layoutManager = LinearLayoutManager(context, LinearLayoutManager.VERTICAL, false)
                rv_billing_items?.apply {
                    this.layoutManager = layoutManager
                    this.itemAnimator = DefaultItemAnimator()
                    this.adapter = recyclerBillingAdapter
                }
            }

            ContainerType.TABLET -> {
                pagerBillingAdapter = PagerBillingAdapter(purchaseListener)
                vp_billing_items?.apply {
                    this.adapter = pagerBillingAdapter
                }
            }
        }
    }

    override fun customize() {
        UIMapper.apply {
            map(layout_billing, UIKey.BILLING_LAYOUT)
            map(tv_billing_title_text, UIKey.BILLING_TITLE)
//            map(tv_billing_prompt_text, UIKey.BILLING_PROMPT)
//            map(tv_billing_link_text, UIKey.BILLING_LINK)
        }
    }

    override fun populateBillingContainer(purchaseItems: List<PurchaseItem>) {
        recyclerBillingAdapter?.apply { addPurchaseItems(purchaseItems) }
        pagerBillingAdapter?.apply { addPurchaseItems(purchaseItems) }
    }

    override fun clearBillingContainer() {
        recyclerBillingAdapter?.apply { removeAllPurchaseItems() }
        pagerBillingAdapter?.apply { removeAllPurchaseItems() }
    }
}