package com.applicaster.cam.ui

import android.os.Bundle
import android.support.v7.app.AppCompatActivity
import android.view.View
import com.applicaster.cam.ContentAccessManager
import com.applicaster.cam.R
import com.applicaster.cam.params.auth.AuthScreenType
import com.applicaster.cam.ui.base.view.ContainerType
import com.applicaster.cam.ui.base.view.IBaseActivity
import kotlinx.android.synthetic.main.activity_cam.*

class CamActivity : AppCompatActivity(), IBaseActivity {

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
        navigationRouter.attachLastFragment(
            ContentAccessManager.pluginConfigurator.getDefaultAuthScreen(),
            ContentAccessManager.contract.getCamFlow()
        )
    }

    override fun getFragmentContainerType(): ContainerType {
        return when {
            fragments_container_phone != null -> ContainerType.PHONE
            else -> ContainerType.TABLET
        }
    }

    override fun getFragmentContainerId() = fragmentsContainer.id

    override fun getNavigationRouter() = navigationRouter

    override fun goBack() {
        onBackPressed()
    }

    override fun close() {
        ContentAccessManager.contract.onCamFinished()
        finish()
    }
}
