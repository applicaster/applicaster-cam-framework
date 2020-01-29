package com.applicaster.cam.ui.auth.password.update

import com.applicaster.cam.config.ui.UIKey
import com.applicaster.cam.config.ui.UIMapper
import com.applicaster.cam.ui.CamNavigationRouter
import com.applicaster.cam.ui.auth.base.IBaseInputPresenter
import com.applicaster.cam.ui.auth.base.IBaseInputView
import com.applicaster.cam.ui.auth.password.BasePasswordFragment
import kotlinx.android.synthetic.main.fragment_password_reset.*

class PasswordUpdateFragment : BasePasswordFragment(), IBaseInputView {

    override fun initPresenter(navigationManager: CamNavigationRouter): IBaseInputPresenter {
        presenter = PasswordUpdatePresenter(this, navigationManager)
        setPresenter(presenter)
        return presenter as PasswordUpdatePresenter
    }

    override fun customize() {
        super.customize()

        UIMapper.apply {
            map(tv_reset_title, UIKey.PASSWORD_UPDATE_TITLE_TEXT)
            map(tv_reset_title_desc, UIKey.PASSWORD_UPDATE_DESC_TEXT)
            map(btn_reset, UIKey.PASSWORD_UPDATE_ACTION_BUTTON)
        }
    }
}