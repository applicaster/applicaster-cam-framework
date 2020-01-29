package com.applicaster.cam.ui.auth.password.reset

import com.applicaster.cam.ContentAccessManager
import com.applicaster.cam.config.ui.UIKey
import com.applicaster.cam.config.ui.UIMapper
import com.applicaster.cam.ui.CamNavigationRouter
import com.applicaster.cam.ui.auth.base.IBaseInputPresenter
import com.applicaster.cam.ui.auth.base.IBaseInputView
import com.applicaster.cam.ui.auth.password.BasePasswordFragment
import kotlinx.android.synthetic.main.fragment_password_reset.*

class PasswordResetFragment : BasePasswordFragment(), IBaseInputView {

    override fun initPresenter(navigationManager: CamNavigationRouter): IBaseInputPresenter {
        presenter = PasswordResetPresenter(this, navigationManager)
        setPresenter(presenter)
        return presenter as PasswordResetPresenter
    }

    override fun customize() {
        super.customize()

        UIMapper.apply {
            map(tv_reset_title, UIKey.PASSWORD_RESET_TITLE_TEXT)
            map(tv_reset_title_desc, UIKey.PASSWORD_RESET_DESC_TEXT)

            if (ContentAccessManager.pluginConfigurator.isPasswordUpdateRequired())
                map(btn_reset, UIKey.PWD_ACTIVATION_CODE_BUTTON_TEXT)
            else
                map(btn_reset, UIKey.PASSWORD_RESET_ACTION_BUTTON)
        }
    }
}

