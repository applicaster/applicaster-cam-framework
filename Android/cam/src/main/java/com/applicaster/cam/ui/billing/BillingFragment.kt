package com.applicaster.cam.ui.billing

import android.os.Bundle
import android.view.LayoutInflater
import android.view.View
import android.view.ViewGroup
import com.applicaster.cam.R
import com.applicaster.cam.ui.CamNavigationRouter
import com.applicaster.cam.ui.base.view.BaseFragment

class BillingFragment : BaseFragment(), IBillingView {

    private var presenter: IBillingPresenter? = null


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
        TODO("not implemented") //To change body of created functions use File | Settings | File Templates.
    }
}