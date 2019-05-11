package com.applicaster.camsample

import android.os.Bundle
import android.support.v7.app.AppCompatActivity
import com.applicaster.cam.ContentAccessManagerImpl
import com.applicaster.camsample.mock.MockCamContract
import com.applicaster.camsample.mock.MockConfigurationProvider
import kotlinx.android.synthetic.main.activity_main.*

class MainActivity : AppCompatActivity() {

    override fun onCreate(savedInstanceState: Bundle?) {
        super.onCreate(savedInstanceState)
        setContentView(R.layout.activity_main)

        btn_start.setOnClickListener { startCamFlow() }
    }

    private fun startCamFlow() {
        val cam = ContentAccessManagerImpl
        cam.onProcessStarted(MockCamContract(), MockConfigurationProvider(), this)
    }
}
