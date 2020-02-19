package com.applicaster.cam.ui

import android.content.Context
import android.os.Bundle
import androidx.appcompat.app.AppCompatActivity
import android.util.Log
import android.view.View
import com.applicaster.cam.CamFlow
import com.applicaster.cam.ContentAccessManager
import com.applicaster.cam.R
import com.applicaster.cam.analytics.Action
import com.applicaster.cam.analytics.AnalyticsGatewaySession
import com.applicaster.cam.analytics.AnalyticsUtil
import com.applicaster.cam.analytics.TimedEvent
import com.applicaster.cam.ui.base.view.ContainerType
import com.applicaster.cam.ui.base.view.IBaseActivity
import kotlinx.android.synthetic.main.activity_cam.*

class CamActivity : AppCompatActivity(), IBaseActivity {

    private lateinit var fragmentsContainer: View
    private lateinit var navigationRouter: CamNavigationRouter

    @Suppress("PLUGIN_WARNING")
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
            ContentAccessManager.camFlow
        )
    }

    override fun getFragmentContainerType(): ContainerType {
        return when {
            fragments_container_phone != null -> ContainerType.PHONE
            else -> ContainerType.TABLET
        }
    }

    override fun getContext() = this

    override fun getFragmentContainerId() = fragmentsContainer.id

    override fun getNavigationRouter() = navigationRouter

    override fun goBack() {
        onBackPressed()
    }

    override fun close() {
        ContentAccessManager.contract.onCamFinished()
        finish()
    }

    override fun onBackPressed() {
        navigationRouter.callFragmentBackPressed()
        super.onBackPressed()
    }

    override fun onPause() {
        // Analytics event
        AnalyticsGatewaySession.sessionData.add(Action.SEND_APP_TO_BACKGROUND)
        super.onPause()
    }

    override fun onDestroy() {
        // Analytics event
        AnalyticsUtil.logContentGatewaySession(
                TimedEvent.END,
                ContentAccessManager.contract.getAnalyticsDataProvider().trigger.value,
                AnalyticsGatewaySession.sessionData
        )
        super.onDestroy()
    }
}
