package com.applicaster.camsample

import android.os.Bundle
import androidx.appcompat.app.AppCompatActivity
import com.applicaster.cam.ContentAccessManager
import com.applicaster.camsample.mock.MockCamContract
import kotlinx.android.synthetic.main.activity_main.*

class MainActivity : AppCompatActivity() {

    override fun onCreate(savedInstanceState: Bundle?) {
        super.onCreate(savedInstanceState)
        setContentView(R.layout.activity_main)

        btn_start.setOnClickListener { startCamFlow() }
    }

    private fun startCamFlow() {
        ContentAccessManager.onProcessStarted(MockCamContract(this), this)
    }
}
