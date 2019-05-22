package com.applicaster.cam.ui.base.view

import android.support.v7.app.AppCompatActivity
import android.widget.Toast
import com.applicaster.cam.ui.base.BaseNavigationRouter

abstract class BaseActivity : AppCompatActivity() {
    abstract fun getFragmentContainerType(): ContainerType
    abstract fun getFragmentContainerId(): Int
    abstract fun getNavigationRouter(): BaseNavigationRouter?
}
