package com.applicaster.cam.ui.billing

import android.os.Bundle
import android.support.v7.widget.DefaultItemAnimator
import android.support.v7.widget.LinearLayoutManager
import android.support.v7.widget.PagerSnapHelper
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
import com.applicaster.cam.ui.billing.adapter.recycler.RecyclerBillingAdapter
import kotlinx.android.synthetic.main.fragment_billing.*
import kotlinx.android.synthetic.main.layout_text_with_action.*
import kotlinx.android.synthetic.main.layout_toolbar_template.*
import com.applicaster.cam.ui.billing.adapter.recycler.SpaceItemDecoration


class BillingFragment : BaseFragment(), IBillingView {

    private var presenter: IBillingPresenter? = null
    private var recyclerBillingAdapter: RecyclerBillingAdapter? = null
    private var pagerBillingAdapter: RecyclerBillingAdapter? = null
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
        toolbar_back_button.setOnClickListener { presenter?.onToolbarBackClicked() }
        toolbar_close_button.setOnClickListener { presenter?.onToolbarCloseClicked() }
        container_restore.setOnClickListener { presenter?.onRestoreClicked() }
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
                pagerBillingAdapter = RecyclerBillingAdapter(purchaseListener)
                val layoutManager = LinearLayoutManager(context, LinearLayoutManager.HORIZONTAL, false)
                val snapHelper = PagerSnapHelper()
                val itemDecoration = SpaceItemDecoration(horizontalSpaceHeight = 20)
                rv_billing_items?.apply {
                    this.layoutManager = layoutManager
                    snapHelper.attachToRecyclerView(this)
                    this.itemAnimator = DefaultItemAnimator()
                    addItemDecoration(itemDecoration)
                    this.adapter = pagerBillingAdapter
                }
            }
        }
        customize()
    }

    override fun customize() {
        super.customize()
        UIMapper.apply {
            map(toolbar_back_button, UIKey.TOOLBAR_BACK_BUTTON)
            map(toolbar_close_button, UIKey.TOOLBAR_CLOSE_BUTTON)
            map(app_logo, UIKey.TOOLBAR_HEADER_LOGO_IMAGE)
            map(layout_billing, UIKey.BACKGROUND_IMAGE)
            map(tv_billing_title_text, UIKey.BILLING_TITLE)
            map(tv_hint_desc, UIKey.BILLING_RESTORE_HINT_DESC_TEXT)
            map(tv_hint_action, UIKey.BILLING_RESTORE_ACTION_TEXT)
        }
    }

    override fun getParentView() = layout_billing

    override fun populateBillingContainer(purchaseItems: List<PurchaseItem>) {
        recyclerBillingAdapter?.apply { addPurchaseItems(purchaseItems) }
        pagerBillingAdapter?.apply { addPurchaseItems(purchaseItems) }
    }

    override fun clearBillingContainer() {
        recyclerBillingAdapter?.apply { removeAllPurchaseItems() }
        pagerBillingAdapter?.apply { removeAllPurchaseItems() }
    }
}