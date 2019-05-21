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
import kotlinx.android.synthetic.main.fragment_auth.*
import kotlinx.android.synthetic.main.fragment_billing.*
import kotlinx.android.synthetic.main.layout_text_with_action.*
import kotlinx.android.synthetic.main.layout_toolbar_template.*

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
        customize()
    }

    override fun customize() {
        UIMapper.apply {
            map(toolbar_back_button, UIKey.TOOLBAR_BACK_BUTTON)
            map(toolbar_close_button, UIKey.TOOLBAR_CLOSE_BUTTON)
            map(app_logo, UIKey.TOOLBAR_HEADER_LOGO)
            map(layout_billing, UIKey.BACKGROUND_IMAGE)
            map(tv_billing_title_text, UIKey.BILLING_TITLE)
            map(tv_hint_desc, UIKey.BILLING_RESTORE_HINT_DESC)
            map(tv_hint_action, UIKey.BILLING_RESTORE_ACTION)
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

    override fun showToastMessage(msg: String) {
        super.showToastMessage(msg)
    }

    override fun showLoadingIndicator() {
        super.showLoadingIndicator()
    }

    override fun hideLoadingIndicator() {
        super.hideLoadingIndicator()
    }
}