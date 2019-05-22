package com.applicaster.cam.ui

import android.os.Bundle
import android.view.View
import com.applicaster.cam.ContentAccessManager
import com.applicaster.cam.R
import com.applicaster.cam.params.auth.AuthScreenType
import com.applicaster.cam.ui.base.view.BaseActivity
import com.applicaster.cam.ui.base.view.ContainerType
import kotlinx.android.synthetic.main.activity_cam.*

class CamActivity : BaseActivity() {

    private lateinit var fragmentsContainer: View
    private lateinit var navigationRouter: CamNavigationRouter

    override fun onCreate(savedInstanceState: Bundle?) {
        super.onCreate(savedInstanceState)
        setContentView(R.layout.activity_cam)

        when {
            fragments_container_phone != null -> fragmentsContainer = fragments_container_phone
            fragments_container_tablet != null -> fragmentsContainer = fragments_container_tablet
        }

        navigationRouter = CamNavigationRouter(this)


        when (ContentAccessManager.pluginConfigurator.getDefaultAuthScreen()) {
            AuthScreenType.LOGIN -> navigationRouter.attachLoginFragment()
            AuthScreenType.SIGNUP -> navigationRouter.attachSignUpFragment()
        }
    }

    override fun getFragmentContainerType(): ContainerType {
        return when {
            fragments_container_phone != null -> ContainerType.PHONE
            else -> ContainerType.TABLET
        }
    }

    override fun getFragmentContainerId() = fragmentsContainer.id

    override fun getNavigationRouter() = navigationRouter
}
