package com.applicaster.cam.ui.base.view

import android.support.v4.app.FragmentManager
import com.applicaster.cam.ui.base.BaseNavigationRouter

interface IBaseActivity {
    fun getFragmentContainerType(): ContainerType
    fun getFragmentContainerId(): Int
    fun getNavigationRouter(): BaseNavigationRouter?
    fun getSupportFragmentManager(): FragmentManager
    fun goBack()
    fun close()
}