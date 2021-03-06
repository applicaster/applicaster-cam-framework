package com.applicaster.cam.ui.billing

import android.app.Activity
import android.content.res.Resources
import android.os.Bundle
import androidx.recyclerview.widget.DefaultItemAnimator
import androidx.recyclerview.widget.LinearLayoutManager
import android.util.Log
import android.view.LayoutInflater
import android.view.View
import android.view.ViewGroup
import com.applicaster.cam.R
import com.applicaster.cam.config.ui.UIKey
import com.applicaster.cam.config.ui.UIMapper
import com.applicaster.cam.ui.CamNavigationRouter
import com.applicaster.cam.ui.base.custom.CustomLinkViewCustomizationHelper
import com.applicaster.cam.ui.base.presenter.ICustomLinkActionHandler
import com.applicaster.cam.ui.base.view.BaseFragment
import com.applicaster.cam.ui.base.view.ContainerType
import com.applicaster.cam.ui.billing.adapter.PurchaseInteractionListener
import com.applicaster.cam.ui.billing.adapter.PurchaseItem
import com.applicaster.cam.ui.billing.adapter.recycler.AdapterPurchaseData
import com.applicaster.cam.ui.billing.adapter.recycler.BillingItemType
import com.applicaster.cam.ui.billing.adapter.recycler.RecyclerBillingAdapter
import com.applicaster.cam.ui.billing.adapter.recycler.SpaceItemDecoration
import kotlinx.android.synthetic.main.fragment_billing.*
import kotlinx.android.synthetic.main.layout_bottom_links.*
import kotlinx.android.synthetic.main.layout_toolbar_template.*


class BillingFragment : BaseFragment(), IBillingView {

    private var presenter: IBillingPresenter? = null
    private var recyclerBillingAdapter: RecyclerBillingAdapter? = null
    private var pagerBillingAdapter: RecyclerBillingAdapter? = null
    private lateinit var purchaseListener: PurchaseInteractionListener
    private lateinit var itemDecoration: SpaceItemDecoration
    private var containerType: ContainerType = ContainerType.PHONE

    override fun onCreateView(
            inflater: LayoutInflater,
            container: ViewGroup?,
            savedInstanceState: Bundle?
    ): View? {
        baseActivity?.apply {
            val navigationManager = if (getNavigationRouter() is CamNavigationRouter)
                getNavigationRouter() as CamNavigationRouter
            else
                CamNavigationRouter(this)

            presenter = BillingPresenter(this@BillingFragment, navigationManager)
            setPresenter(presenter)
        }
        return inflater.inflate(R.layout.fragment_billing, container, false)
    }

    override fun setListeners() {
        purchaseListener = object : PurchaseInteractionListener {
            override fun onPurchaseButtonClicked(skuId: String) {
                presenter?.onPurchaseButtonClicked(baseActivity as Activity, skuId)
            }

            override fun onRedeemClicked() {
                Log.e(BillingFragment::class.java.simpleName, "Redeem clicked")
            }
        }
    }

    override fun initBackButton(enable: Boolean) {
        if (enable) {
            toolbar_back_button.setOnClickListener { presenter?.onToolbarBackClicked() }
        } else {
            toolbar_back_button.visibility = View.GONE
        }
    }

    override fun initViewComponents(containerType: ContainerType, billingItemType: BillingItemType) {
        this.containerType = containerType
        // init toolbar here
        when (containerType) {
            ContainerType.PHONE -> {
                recyclerBillingAdapter = RecyclerBillingAdapter(purchaseListener, presenter, billingItemType)
                val layoutManager =
                    LinearLayoutManager(
                        context,
                        LinearLayoutManager.VERTICAL,
                        false
                    )
                rv_billing_items?.apply {
                    this.layoutManager = layoutManager
                    itemDecoration = SpaceItemDecoration(verticalSpaceHeight = resources.getDimensionPixelSize(R.dimen.billing_list_vertical_space))
                    addItemDecoration(itemDecoration)
                    this.itemAnimator =
                        DefaultItemAnimator()
                    this.adapter = recyclerBillingAdapter
                }
            }

            ContainerType.TABLET -> {
                pagerBillingAdapter = RecyclerBillingAdapter(purchaseListener, presenter, billingItemType)
                // add padding to the recycler view to set child to the center of the root container
                val layoutManager =
                    LinearLayoutManager(
                        context,
                        LinearLayoutManager.HORIZONTAL,
                        false
                    )
                // init custom snap helper
                val snapHelper = TabletSnapHelper()
                rv_billing_items?.apply {
                    snapHelper.attachToRecyclerView(this)
                    this.layoutManager = layoutManager
                    itemDecoration = SpaceItemDecoration(horizontalSpaceHeight = resources.getDimensionPixelSize(R.dimen.billing_list_horizontal_space))
                    addItemDecoration(itemDecoration)
                    this.itemAnimator =
                        DefaultItemAnimator()
                    this.adapter = pagerBillingAdapter
                }
            }
        }
    }

    override fun customize() {
        super.customize()
        UIMapper.apply {
            map(toolbar_back_button, UIKey.TOOLBAR_BACK_BUTTON)
            map(app_logo, UIKey.TOOLBAR_HEADER_LOGO_IMAGE)
            map(layout_billing, UIKey.BACKGROUND_IMAGE)
            map(tv_billing_title_text, UIKey.BILLING_TITLE)
            map(container_restore, UIKey.BILLING_RESTORE_HINT_DESC_TEXT) { presenter?.onRestoreClicked() }
        }
    }

    override fun getParentView() = layout_billing

    override fun populateBillingContainer(purchaseItems: List<AdapterPurchaseData>) {
        pagerBillingAdapter?.apply { addPurchaseItems(purchaseItems) }
        recyclerBillingAdapter?.apply { addPurchaseItems(purchaseItems) }
    }

    override fun populateCustomLinksContainer() {
        UIMapper.map(tv_bottom_link_1, UIKey.STOREFRONT_LINK_1_TEXT, presenter as ICustomLinkActionHandler)
        UIMapper.map(tv_bottom_link_2, UIKey.STOREFRONT_LINK_2_TEXT, presenter as ICustomLinkActionHandler)
        CustomLinkViewCustomizationHelper().customize(tv_bottom_link_1, tv_bottom_link_2, container_bottom_links)
    }

    override fun hideCustomLinksContainer() {
        container_bottom_links?.visibility = View.GONE
    }

    override fun clearBillingContainer() {
        recyclerBillingAdapter?.apply { removeAllPurchaseItems() }
        pagerBillingAdapter?.apply { removeAllPurchaseItems() }
    }

    override fun calculateRecyclerContainerPadding(itemsCount: Int) {
        if (containerType == ContainerType.TABLET) {
            val rootWidth = Resources.getSystem().displayMetrics.widthPixels
            val childWidth = resources.getDimension(R.dimen.layout_billing_item_width).toInt()
            val childrenWidth = (childWidth + (itemDecoration.horizontalSpaceHeight
                    ?: 0)) * itemsCount
            if (childrenWidth <= rootWidth) {
                val parentPadding = (rootWidth - childrenWidth) / 2
                rv_billing_items?.setPadding(parentPadding, 0, parentPadding, 0)
            } else {
                val parentPadding = (rootWidth - childWidth + (itemDecoration.horizontalSpaceHeight
                        ?: 0)) / 2
                rv_billing_items?.setPadding(parentPadding, 0, parentPadding, 0)
            }
        }
    }

    override fun onLastFragmentClosed() {
        presenter?.onLastFragmentClosed()
    }
}